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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result; 
        
        traverse(root, 1, result); 
        
        return result; 
    }
    
    void traverse(TreeNode * root, int level, vector<vector<int>> &result) { 
        if (!root) return; 
        
        if (level > result.size())
            result.push_back(vector<int>()); 
        
        result[level-1].push_back(root->val); 
        traverse(root->left, level+1, result); 
        traverse(root->right, level+1, result); 
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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result; 
        queue<TreeNode *> current, next; 
        
        if (!root) return result; 
        current.push(root); 
        
        while (!current.empty()) { 
            vector<int> level; 
            while (!current.empty()) { 
                TreeNode * node = current.front(); 
                current.pop(); 
                level.push_back(node->val); 
                
                if (node->left) next.push(node->left); 
                if (node->right) next.push(node->right); 
            }
            result.push_back(level); 
            swap(next, current); 
        }
        return result; 
    }
    
  
};


