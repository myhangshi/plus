class Solution {
public:
    
    int countPrimes(int n) {
        
        
        vector<bool> num(n, true); 
        int total = 0; 
        
        num[0] = false; 
        num[1] = false; 
        
        int res = 0, limit = sqrt(n); 
        
        for (int i = 2; i <= limit; ++i) { 
            if (num[i]) { 
                for (int j = i * i; j < n; j += i) { 
                    num[j] = false; 
                }
                
            }
        
        }
        
        for (int j = 0; j < n; ++j) { 
            if (num[j]) ++total; 
        }
       
        return total; 
    }
};


