/
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
    bool isSymmetric(TreeNode* root) {
        if (!root) return true; 
        return isSymImpl(root->left, root->right); 
    }
    
    bool isSymImpl(TreeNode *p, TreeNode *q) { 
        if (!p && !q) return true; 
        if (!p || !q) return false; 
        
        return (p->val == q->val) && 
            isSymImpl(p->left, q->right) && 
            isSymImpl(q->left, p->right);  
    
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
    bool isSymmetric(TreeNode* root) {
        if (!root) return true; 
        
        stack<TreeNode*> s; 
        s.push(root->left); 
        s.push(root->right); 
        
        while (!s.empty()) { 
            auto p = s.top(); s.pop(); 
            auto q = s.top(); s.pop(); 
            
            if (!p && !q) continue; 
            if (!p || !q) return false; 
            
            if (p->val != q->val) return false; 
            
            s.push(p->left); 
            s.push(q->right); 
            
            s.push(p->right); 
            s.push(q->left); 
        
        }
        
        return true; 
        
        
    }
    
    
};
