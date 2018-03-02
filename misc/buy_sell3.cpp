class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size(); 
        vector<int> g1(n, 0); 
        vector<int> g2(n, 0); 
        
        if (n <= 1) return 0; 
        
        //low direction 
        int valley = prices[0]; 
        for (int i = 1; i < n; i++) { 
            g1[i] = max(g1[i-1], prices[i] - valley); 
            valley = min(valley, prices[i]); 
        }
        
        //high direction 
        int peak = prices[n-1]; 
        for (int i = n-2; i >=0; i--) { 
            g2[i] = max(g2[i-1], peak - prices[i]); 
            peak = max(peak, prices[i]); 
        }
        
        int max_profit = 0; 
        for (int i = 0; i < n; i++) 
            if (g1[i] + g2[i] > max_profit) 
                max_profit = g1[i] + g2[i]; 
        
        return max_profit; 
        
    }
};

