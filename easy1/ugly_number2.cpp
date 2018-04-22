class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> result(n, 0); 
        int r2 = 0, r3 = 0, r5 = 0; 
        result[0] = 1; 
        for (int i = 1; i < n; ++i) { 
            int m2 = result[r2] * 2; 
            int m3 = result[r3] * 3; 
            int m5 = result[r5] * 5; 
            
            int r = min(m2, min(m3, m5)); 
            result[i] = r; 
            if (r == m2) r2++; 
            if (r == m3) r3++; 
            if (r == m5) r5++; 
        
        }
        return result[n-1]; 
    }
};

