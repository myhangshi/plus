/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    
    void kthSmallestImpl(TreeNode* root, int k, int &count, int &value) {
        if (root == NULL || count > k ) return; 
        
        kthSmallestImpl(root->left, k, count, value); 
        if (count > k) return; 
        
        count++; 
        if (count == k)  { 
            value = root->val; 
            return; 
        } 
    
        kthSmallestImpl(root->right, k, count, value);    
    }
    
    int kthSmallest(TreeNode* root, int k) {
        int ksmall = INT_MAX; 
        int count = 0;
        
        kthSmallestImpl(root, k, count, ksmall); 
        
        return ksmall;       
        
    }
};


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        int count = 0; 
        
        int ksmall = INT_MIN; 
        TreeNode *curr = root; 
        
        while (curr != NULL) { 
            if (curr->left == NULL) { 
                count++; 
                if (count == k) 
                    ksmall = curr->val; 
                curr = curr->right; 
            } else { 
                TreeNode *pre = curr->left; 
                //create links to Inorder successor and count using links 
                while (pre->right && pre->right != curr)
                    pre = pre->right; 
                
                // building links now 
                if (pre->right == NULL) { 
                    pre->right = curr; 
                    curr = curr->left; 
                } else { 
                    pre->right = NULL; 
                    count++; 
                    if (count == k) 
                        ksmall = curr->val; 
                    curr = curr->right; 
                }
            
            }
        
        }
        
        return ksmall;       
        
    }
};


