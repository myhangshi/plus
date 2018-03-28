class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        return vector<int>{lower_bound(nums, target), upper_bound(nums, target) }; 
    }
    
    int lower_bound (vector<int>& nums, int target) {
        int low = 0; 
        int high = nums.size() - 1; 
        
        while (low <= high) { 
            int mid = low + (high - low) / 2; 
            
            if (nums[mid] < target) low = mid + 1; 
            else if (nums[mid] > target) high = mid - 1;
            else { 
                if (mid > 0 && nums[mid - 1] == target) high = mid - 1; 
                else return mid; 
            }
        
        }
        return -1; 

    } 
    
    int upper_bound (vector<int>& nums, int target) {
        int low = 0; 
        int high = nums.size() - 1; 
        
        while (low <= high) { 
            int mid = low + (high - low) / 2; 
            
            if (nums[mid] < target) low = mid + 1; 
            else if (nums[mid] > target) high = mid - 1;
            else { 
                if (mid < nums.size() - 1 && nums[mid + 1] == target) low = mid + 1; 
                else return mid; 
            }
        
        }
        return -1; 
    } 
    
};
