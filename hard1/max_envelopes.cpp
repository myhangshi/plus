class Solution {
public:
    int maxEnvelopes(vector<pair<int, int>>& envelopes) {
        int result = 0;
        int n = envelopes.size(); 
        vector<int> dp(n, 1); 
        
        sort(envelopes.begin(), envelopes.end()); 
        
        for (int i = 0; i < n; ++i) { 
            for (int j = 0; j < i; ++j) { 
                if (envelopes[i].first > envelopes[j].first && 
                   envelopes[i].second > envelopes[j].second) { 
                    dp[i] = max(dp[i], dp[j]+1); 
                }
            }
            result = max(result, dp[i]); 
        }
        return result;      
    }
    
};


