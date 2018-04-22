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
    TreeNode* convertBST(TreeNode* root) {
        int sum = 0; 
        convertBSTHelper(root, sum); 
        return root; 
    }
    
    void convertBSTHelper(TreeNode* root, int &sum) {
        if (root == NULL) return; 
        convertBSTHelper(root->right, sum); 
        root->val += sum; 
        sum = root->val; 
        convertBSTHelper(root->left, sum); 
    }
    
    
};


