class Solution {
public:
    
    void  DFSGrid(vector<vector<char>>& grid, int i, int j) { 
        int M = grid.size(); 
        int N = grid[0].size(); 
        
        if (i < 0 || i >= M || j < 0 || j >= N || grid[i][j] != '1') 
            return; 
        
        grid[i][j] = 'X'; 
        DFSGrid(grid, i+1, j);
        DFSGrid(grid, i-1, j);
        DFSGrid(grid, i, j+1);
        DFSGrid(grid, i, j-1);
    }
            
    
    int numIslands(vector<vector<char>>& grid) {
        if ( grid.size() == 0 || grid[0].size() == 0)
            return 0; 
        
        int M = grid.size(); 
        int N = grid[0].size(); 
        
        int count = 0; 
        
        for (int i = 0; i < M; ++i) { 
            for (int j = 0; j < N; ++j) { 
                if (grid[i][j] == '1') { 
                    count++; 
                    DFSGrid(grid, i, j); 
                }     
            }
        
        }
        
        return count; 
    }
};


