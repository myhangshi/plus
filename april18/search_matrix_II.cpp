class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        
        if (matrix.empty() || matrix[0].empty()) return false;
        if (target < matrix[0][0] || target > matrix.back().back()) return false;
      
        
        int M = matrix.size(); 
        int N = matrix[0].size(); 
        
        int x = 0, y = N - 1; 
        
        while (x < M && y >= 0) { 
            if (matrix[x][y] == target) return true; 
            else if (matrix[x][y] > target) y--; 
            else x++; 
        
        }
        
        return false; 
    }
};


