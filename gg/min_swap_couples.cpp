class Solution {
public:
    int minSwapsCouples(vector<int>& row) {
        
        vector<int> pos(row.size(), 0); 
        
        for (int i = 0; i < row.size(); i++) { 
            pos[row[i]] = i; 
        }
        
        int result = 0; 
        
        for (int i = 0; i < row.size(); i += 2) { 
            
            if (row[i]/2 == row[i+1]/2) continue; 
            
            int partner = 0; 
            
            if (row[i] % 2 == 0) partner = pos[row[i]+1];
            else partner = pos[row[i]-1];
            
            result++; 
            pos[row[i+1]] = partner; 
            swap(row[i+1], row[partner]); 
        
        }
        return result; 
    }
};

