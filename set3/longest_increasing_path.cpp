class Solution {
public:
    vector<vector<int>> dirs = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
    
    int longestIncreasingPath2(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return 0; 
        int result = 1; 
        int m = matrix.size(); 
        int n = matrix[0].size(); 
        vector<vector<int>> dp(m, vector<int>(n, 0)); 
        
        for (int i=0; i < m; ++i) { 
            for (int j=0; j < n;  ++j) { 
                result = max(result, dfs(matrix, dp, i, j)); 
            }
        }
        return result; 
    }
    
    int dfs(vector<vector<int>> & matrix, vector<vector<int>>&dp, int i, int j) { 
    
        if (dp[i][j] != 0) return dp[i][j]; 
        int mx = 1, m = matrix.size(), n = matrix[0].size(); 
        
        for (auto & a: dirs) { 
            int x = i + a[0]; 
            int y = j + a[1];
            
            if (x < 0 || x >= m || y < 0 || y >= n) continue; 
            if (matrix[x][y] <= matrix[i][j]) continue; 
            
            int len = 1 + dfs(matrix, dp, x, y); 
            mx = max(mx, len); 
        
        }
        dp[i][j] = mx; 
        return mx; 
    }
    
    
     int longestIncreasingPath(vector<vector<int>>& matrix) {
        
         if (matrix.empty() || matrix[0].empty()) return 0;
        
         int m = matrix.size(), n = matrix[0].size(), res = 1;
        
         vector<vector<int>> dirs{{0,-1},{-1,0},{0,1},{1,0}};
         vector<vector<int>> dp(m, vector<int>(n, 0));
        
         for (int i = 0; i < m; ++i) {
             for (int j = 0; j < n; ++j ) {
                 if (dp[i][j] > 0) continue;
                 queue<pair<int, int>> q{{{i, j}}};
                 int cnt = 1;
                 while (!q.empty()) {
                     ++cnt;
                     int len = q.size();
                     for (int k = 0; k < len; ++k) {
                         auto t = q.front(); q.pop();
                         for (auto dir : dirs) {
                             int x = t.first + dir[0], y = t.second + dir[1];
                             if (x < 0 || x >= m || y < 0 || y >= n || matrix[x][y] <= matrix[t.first][t.second] 
                                 || cnt <= dp[x][y]) continue;
                             dp[x][y] = cnt;
                             res = max(res, cnt);
                             q.push({x, y});
                         }
                    }
                }
            }
        }
        return res;
    }
    
};

