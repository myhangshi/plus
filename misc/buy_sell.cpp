class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int result = 0; 
        
        if (prices.size() <= 1) return result; 
        
        int valley = prices[0]; 
        
        for (int i = 1; i < prices.size(); i++) { 
            result = max(result, prices[i] - valley); 
            valley = min(valley, prices[i]); 
        }
        
        return result; 
    }
};

