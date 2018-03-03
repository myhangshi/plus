class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> result; 
        if (matrix.empty()) return result; 
        
        int startX = 0, endX = matrix[0].size() - 1; 
        int startY = 0, endY = matrix.size() - 1; 
        
        while (true) { 
            for (int j = startX; j <= endX; j++)
                result.push_back(matrix[startY][j]); 
            if (++startY > endY) break; 
            
            for (int j = startY; j <= endY; j++)
                result.push_back(matrix[j][endX]); 
            if (--endX < startX) break; 
            
            for (int j = endX; j >= startX; j--)
                result.push_back(matrix[endY][j]); 
            if (--endY < startY) break; 
            
            for (int j = endY; j >= startY; j--)
                result.push_back(matrix[j][startX]); 
            if (++startX > endX) break; 
        
        }
        return result; 
    }
};

