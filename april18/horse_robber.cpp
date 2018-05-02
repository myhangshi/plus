http://www.cnblogs.com/grandyang/p/4383632.html

class Solution {
public:
    int rob(vector<int>& nums) {
        int N = nums.size(); 
        
        if (N == 0) return 0; 
        if (N == 1) return nums[0]; 
        
        vector<int> sum = vector<int>(N); 
        sum[0] = nums[0]; 
        sum[1] = max(nums[0], nums[1]); 
        
        for (int i = 2; i < N; ++i) { 
            sum[i] = max(sum[i-1], sum[i-2] + nums[i]); 
        }
        return sum[N-1]; 
    }
};


