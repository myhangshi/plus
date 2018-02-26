
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
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result; 
        stack<const TreeNode *> s; 
        
        if (root) s.push(root); 
        
        while (!s.empty()) { 
            const TreeNode *p = s.top(); 
            s.pop(); 
            result.push_back(p->val); 
            
            if (p->right) s.push(p->right); 
            if (p->left) s.push(p->left); 
        }
    
        return result; 
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
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result; 
        TreeNode *cur = root, *prev = nullptr; 
        
        while (cur) { 
            if (!cur->left) { 
                result.push_back(cur->val); 
                prev = cur; 
                cur = cur->right; 
            } else { 
                TreeNode *node = cur->left; 
                while (node->right && node->right != cur) // ??? why second 
                   node = node->right; 
                
                if (!node->right) { 
                    result.push_back(cur->val); 
                    node->right = cur; 
                    prev = cur; 
                    cur = cur->left; 
                
                } else { 
                    node->right = nullptr; 
                    cur = cur->right; 
                }
            }
        }
    
        return result; 
    }
};


