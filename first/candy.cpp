class Solution {
public:
    int candy(vector<int>& ratings) {
        int len = ratings.size(); 
        vector<int> count(len); 
        
        for (int i = 1, inc = 1; i < len; i++) { 
            if (ratings[i] > ratings[i - 1]) { 
                count[i] = max(inc++, count[i]); 
            } else { 
                inc = 1; 
            } 
        }
        
        for (int i = len - 1, inc = 1; i > 0; i--) { 
            if (ratings[i] < ratings[i - 1]) { 
                count[i -1] = max(count[i-1], inc++); 
            } else { 
                inc = 1; 
            }
        
        }
        
        int total = 0; 
        for (int i = 0; i < len; i++) { 
            total += count[i] + 1; 
        }
        
        return total; 
        
    }
};

