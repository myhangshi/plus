class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int idx = 0; 
        
        for (int i = 0; i < nums.size(); i++) { 
            if (nums[i] != 0) nums[idx++] = nums[i]; 
        }
        
        for (int i = idx; i <nums.size(); i++) { 
            nums[i] = 0; 
        }
            
        
        /* 
        int cnt = 0; 
        for (auto a : nums) {
            if (a == 0) cnt++; 
        }*/ 
        
        
    }
};


