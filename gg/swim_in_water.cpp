class Solution {
public:
    
    int  dir[4][2] = { {-1, 0}, {0, 1}, {0, -1}, {1, 0}}; 
    int N = 0; 
    
    int swimInWater(vector<vector<int>>& grid) {
        N = grid.size(); 
        int lf = 0; 
        int rt = N * N; 
        
        while (lf < rt) { 
            int mid = lf + (rt - lf) / 2; 
            vector<vector<bool>> visited(N, vector<bool>(N, false)); 
            
            if (goWater(grid, 0, 0, visited, mid)) { 
                rt = mid; 
            } else { 
                lf = mid + 1;     
            }
        }
        return rt; 
    }
    
    bool goWater(vector<vector<int>> grid, int i, int j,vector<vector<bool>> visited, int mid) { 
        if (i == N-1 && j == N-1) return true; 
        visited[i][j] = true; 
        
        for (auto d: dir)  { 
            int ni = i + d[0]; 
            int nj = j + d[1]; 
            
            if (ni >=0 && ni < N && nj >= 0 && nj < N && 
               !visited[ni][nj] && max(grid[ni][nj], mid) == max(grid[i][j], mid)) { 
                if (goWater(grid, ni, nj, visited, mid)) return true; 
            }
        }
        return false; 
    }
    
    
};

