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
    
    TreeNode* lcaImpl(TreeNode* root, TreeNode* p, TreeNode* q) {  
        TreeNode* result; 
        
        if (root == NULL )  return NULL;  
        
        if (root->val == p->val || root->val == q->val) {
            return NULL;
        }
        
        if (root->val > p->val && root->val > q->val) { 
            result = lowestCommonAncestor(root->left, p, q); 
            return result ? result : root; 
            //return result; 
        }
        
        if (root->val < p->val && root->val < q->val) { 
            result = lowestCommonAncestor(root->right, p, q); 
            return result ? result : root; 
            //return result; 
        }
        
        return root; 
    }
    
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {   
        if (root == NULL) return NULL; 
        
        if (root->val == p->val || root->val == q->val) {
            return root;
        }
        return lcaImpl(root, p, q); 
    }
};

