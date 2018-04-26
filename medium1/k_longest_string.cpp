class Solution {
public:
    int longestSubstring(string s, int k) {
        int result = 0; 
        int i = 0; 
        int n = s.size(); 
        
        while (i <= n-k) { 
            int m[26] = {0}; 
            int mask = 0, max_idx = i; 
            
            for (int j = i; j < n; ++j) { 
                int t = s[j] - 'a'; 
                ++m[t]; 
                if (m[t] < k) mask |= (1 << t); 
                else mask &= (~(1<<t)); 
                
                if (mask == 0) { 
                    result = max(result, j-i+1); 
                    max_idx = j; 
                }
            
            }
            i = max_idx + 1; 
        
        }
        return result; 
    }
};


