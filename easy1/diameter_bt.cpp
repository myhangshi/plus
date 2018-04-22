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
    int diameterOfBinaryTree1(TreeNode* root) {
        int result = 0; 
        diameterBT(root, result); 
        return result; 
    }
    
    
    int diameterBT(TreeNode* root, int &result) { 
        if (root == NULL) return 0; 
        int left = diameterBT(root->left, result); 
        int right = diameterBT(root->right, result); 
        
        result = max(result, left + right); 
        return max(left, right) + 1; 
    }
    
    int diameterOfBinaryTree(TreeNode* root) {
        if (!root) return 0;
        int res = getHeight(root->left) + getHeight(root->right);
        return max(res, max(diameterOfBinaryTree(root->left), diameterOfBinaryTree(root->right)));
    }
    
    int getHeight(TreeNode* node) {
        if (!node) return 0;
        if (m.count(node)) return m[node];
        int h = 1 + max(getHeight(node->left), getHeight(node->right));
        return m[node] = h;
    }

private:
    unordered_map<TreeNode*, int> m;
    
};


