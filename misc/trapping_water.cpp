ass Solution {
public:
    int trap(vector<int>& height) {
        int len = height.size(); 
        if (len <= 0) return 0; 
        
        int l_high[len], r_high[len]; 
        int sum = 0; 
        
        for (int i = 0; i < len; i++) { 
            l_high[i] = 0; 
            r_high[i] = 0; 
        }
        
        for (int i = 1; i < len; i++) { 
            l_high[i] = max(l_high[i-1], height[i-1]); 
            r_high[len-1-i] = max(r_high[len-i], height[len-i]); 
        }
        
        for (int i = 0; i < len; i++) { 
            int h = max(l_high[i], r_high[i]) - height[i]; 
            if (h > 0) { 
                sum += h; 
            } 
        }
        return sum;     
    }
};

