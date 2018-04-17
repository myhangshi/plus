class Solution {
public:
    void combineSum3DFS(int k, int n, int level, vector<int> &out, vector<vector<int> > &res) { 
        if (n < 0 || out.size() > k) return; 
        if (n == 0 && out.size() == k) res.push_back(out); 
        
        for (int i = level; i <= 9; ++i) { 
            out.push_back(i); 
            combineSum3DFS(k, n - i, i + 1, out, res); 
            out.pop_back(); 
        
        }
    }
    
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> result; 
        vector<int> out; 
        
        combineSum3DFS(k, n, 1, out, result); 
        return result; 
    }
    
    
};

