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
    void flatten(TreeNode* root) {
         flattenImpl(root, nullptr); 
    }
    
    TreeNode *flattenImpl(TreeNode *root, TreeNode *tail) { 
        if (root == nullptr) return tail; 
        
        TreeNode *p = flattenImpl(root->right, tail); 
        root->right = flattenImpl(root->left, p); 
        root->left = nullptr; 
        return root; 
    }
};

