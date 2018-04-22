class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& A) {
        int result = 0, n = A.size(); 
        vector<unordered_map<int, int>> dp(n); 
        
        for (int i = 0; i < n; ++i) { 
            for (int j = 0; j < i; ++j) { 
                //long delta = (long) A[i] - A[j]; 
                //if (delta > INT_MAX || delta < INT_MIN) continue; 
                //int diff = (int) delta; 
                int diff = A[i] - A[j]; 
                ++dp[i][diff]; 
                if (dp[j].count(diff)) { 
                    result += dp[j][diff]; 
                    dp[i][diff] += dp[j][diff]; 
                }
            
            }
        }
        
        return result; 
    }
};
