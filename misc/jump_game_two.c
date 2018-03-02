class Solution {
public:
    int jump(vector<int>& nums) {
        int step = 0; 
        int left = 0; 
        int right = 0; 
        int n = nums.size(); 
        int old_right, new_right; 
        
        if (nums.size() <=1) return 0; 
        
        while (left <= right) { 
            ++step; 
            old_right = right; 
            for (int i = left; i <= old_right; i++) { 
                new_right = i + nums[i]; 
                if (new_right >= n - 1) 
                    return step; 
                
                if (new_right > right) right = new_right; 
            }
        }
        
        return 0; 
    }
};

