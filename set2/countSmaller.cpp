class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> t, result(nums.size()); 
        
        for (int i = nums.size() - 1; i >= 0; i--) { 
            int idx = 0; 
            int lo = 0, hi = t.size(), mid; 
            while (lo < hi) { 
                mid = lo + (hi - lo) / 2; 
                if (t[mid] < nums[i]) lo = mid + 1; 
                else hi = mid; 
            
            }
            result[i] = hi; 
            t.insert(t.begin()+hi, nums[i]); 
        }
        
        return result; 
    }
};


