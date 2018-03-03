class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>>  result; 
        if (numRows <= 0) return result; 
        result.push_back(vector<int>(1,1)); 
        
        for (int i = 2; i <= numRows; i++) { 
            vector<int> current(i, 1); 
            for (int j = 1; j < i - 1; j++) { 
                current[j] = result[i-2][j-1] + result[i-2][j]; 
            }
            result.push_back(current); 
        }
        return result; 
    }
};


