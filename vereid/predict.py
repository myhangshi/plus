# USAGE
# python predict.py --image images/dog.jpg --model output/simple_nn.model --label-bin output/simple_nn_lb.pickle --width 32 --height 32 --flatten 1
# python predict.py --image aic19-track2-reid/image_train/000001.jpg --model output/smallvggnet.model --label-bin output/smallvggnet_lb.pickle --width 64 --height 64

# import the necessary packages
from keras.models import load_model
from smallvggnet import SmallVGGNet
import argparse
import pickle
import cv2, os, time

root_dir = os.getcwd() + '/' #/media/f/2019AICity_carson/Track2/
train_xml = root_dir + 'aic19-track2-reid/train_label.xml'
train_img_path = root_dir + 'aic19-track2-reid/image_train/'
train_csv = root_dir + "aic19-track2-reid/train_label.csv"
train_feat = root_dir + "aic19-track2-reid/train_feat.csv"
train_feat_pkl = root_dir + "aic19-track2-reid/train_feat.pkl"
train_track = root_dir + "aic19-track2-reid/train_track.txt"
log_dir = root_dir + "log/000/"
label_bin = root_dir + "output/smallvggnet_lb.pickle"
#The following will be replaced by args
model_path = root_dir + "output/" + "smallvggnet.model"
plot_path = root_dir + "output/" + time.strftime("%H_%M_%S") + "_smallvggnet_plot.png"

# construct the argument parser and parse the arguments
ap = argparse.ArgumentParser()
ap.add_argument("-i", "--image", required=True,
	help="path to input image we are going to classify")
ap.add_argument("-m", "--model", required=True,
	help="path to trained Keras model")
ap.add_argument("-l", "--label-bin", required=True,
	help="path to label binarizer")
ap.add_argument("-w", "--width", type=int, default=28,
	help="target spatial dimension width")
ap.add_argument("-e", "--height", type=int, default=28,
	help="target spatial dimension height")
ap.add_argument("-f", "--flatten", type=int, default=-1,
	help="whether or not we should flatten the image")
args = vars(ap.parse_args())
SIZE = (64,64)

# load the input image and resize it to the target spatial dimensions
image = cv2.imread(args["image"])
output = image.copy()
image = cv2.resize(image, (args["width"], args["height"]))

# check to see if we should flatten the image and add a batch
# dimension
if args["flatten"] > 0:
	image = image.flatten()
	image = image.reshape((1, image.shape[0]))

# otherwise, we must be working with a CNN -- don't flatten the
# image, simply add the batch dimension
else:
	image = image.reshape((1, image.shape[0], image.shape[1],
		image.shape[2]))

# load the model and label binarizer
print("[INFO] loading network and label binarizer...")
lb = pickle.loads(open(args["label_bin"], "rb").read())
#lb = pickle.loads(open(label_bin, "rb").read())

#model = load_model(args["model"])
model = SmallVGGNet.build(width=SIZE[0], height=SIZE[1], depth=3,	classes=len(lb.classes_))
model.load_weights(args["model"], by_name=True, skip_mismatch=True)

print("labels", lb)
# make a prediction on the image
preds = model.predict(image)

# find the class label index with the largest corresponding
# probability
i = preds.argmax(axis=1)[0]
label = lb.classes_[i]

# draw the class label + probability on the output image
text = "{}: {:.2f}%".format(label, preds[0][i] * 100)
cv2.putText(output, text, (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.7,
	(0, 0, 255), 2)

# show the output image
cv2.imshow("Image", output)
cv2.waitKey(0)