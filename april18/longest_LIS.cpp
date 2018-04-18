class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size(); 
        
        if (n == 0) return 0; 
        vector<int> lis(n, 1); 
        int i, j, mx = 1; 
        
        for (int i = 1; i < n; i++) { 
            for (int j = 0; j < i; j++) { 
                if (nums[i] > nums[j] && lis[i] < lis[j]+1)
                    lis[i] = lis[j] + 1; 
            }
            if (mx < lis[i]) mx = lis[i]; 
        }
        
        return mx; 
    }
};

