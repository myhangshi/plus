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
    
    bool findPath(TreeNode* root, vector<TreeNode*> &path, TreeNode* val) { 
        if (root == nullptr) return false; 
        
        path.push_back(root); 
        if (root == val) 
            return true; 
        
        if ((root->left && findPath(root->left, path, val)) || 
           (root->right && findPath(root->right, path, val)) )
            return true; 
        
        path.pop_back(); 
        return false; 
    }
    
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {   
        // can't handle multiple path issue 
        if (root == NULL) return NULL; 
        
        if (root == p || root == q) {
            return root;
        } 
        
        vector<TreeNode*> path1, path2; 
        
        if (!findPath(root, path1, p)) return NULL; 
        if (!findPath(root, path2, q)) return NULL; 
        
        int i; 
        for (i = 0; i < min(path1.size(), path2.size()); i++) 
            if (path1[i] != path2[i]) 
                break; 
        
        return path1[i-1]; 
    }
    
    TreeNode* lowestCommonAncestor2(TreeNode* root, TreeNode* p, TreeNode* q) {
       if (!root || p == root || q == root) return root;
       TreeNode *left = lowestCommonAncestor(root->left, p, q);
       TreeNode *right = lowestCommonAncestor(root->right, p , q);
       if (left && right) return root;
       return left ? left : right;
    }
    
    TreeNode* lowestCommonAncestor3(TreeNode* root, TreeNode* p, TreeNode* q) {
       if (!root || p == root || q == root) return root;
       TreeNode *left = lowestCommonAncestor(root->left, p, q);
       if (left && left != p && left != q) return left;
       TreeNode *right = lowestCommonAncestor(root->right, p , q);
       if (right && right != p && right != q) return right;
       if (left && right) return root;
       return left ? left : right;
    }
    
};


