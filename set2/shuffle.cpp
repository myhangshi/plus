class Solution {
public:
    Solution(vector<int> nums) {
        v = nums; 
    }
    
    /** Resets the array to its original configuration and return it. */
    vector<int> reset() {
        return v; 
    }
    
    /** Returns a random shuffling of the array. */
    vector<int> shuffle1() {
        vector<int> result = v; 
        
        for (int i = 0; i < result.size(); ++i) { 
            int t = random() % (i + 1);  
            swap(result[i], result[t]); 
        }
        return result; 
    }
    
     /** Returns a random shuffling of the array. */
    vector<int> shuffle() {
        vector<int> result = v; 
        
        for (int i = 0; i < result.size(); ++i) { 
            int t = i + rand() % (result.size() - i);  
            swap(result[i], result[t]); 
        }
        return result; 
    }
    
private: 
    vector<int> v; 
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(nums);
 * vector<int> param_1 = obj.reset();
 * vector<int> param_2 = obj.shuffle();
 */


