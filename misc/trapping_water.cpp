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
            int h = min(l_high[i], r_high[i]) - height[i]; 
            if (h > 0) { 
                sum += h; 
            } 
        }
        return sum;     
    }
};

class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size(); 
        
       int *max_left = new int[n]();
int *max_right = new int[n]();
        
for (int i = 1; i < n; i++) {
max_left[i] = max(max_left[i - 1], height[i - 1]);
max_right[n - 1 - i] = max(max_right[n - i],height[n - i]);
}
int sum = 0;
for (int i = 0; i < n; i++) {
int h = min(max_left[i], max_right[i]);
if (h > height[i]) {
sum += h - height[i];
}
}
delete[] max_left;
delete[] max_right;
return sum;
    }
};

