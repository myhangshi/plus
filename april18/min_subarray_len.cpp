class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int len = sums.size(); 
        int count = INT_MAX; 
        int left = 0; 
        int sum = 0; 
        
        for (int i = 0; i < len; ++i) { 
            sum += nums[i]; 
            while (sum >= target) { 
                count = min(count, i - left + 1); 
                sum -= sum[left++]; 
            }
        }
        return (count == INT_MAX) ? 0 : count; 
    }
};

