class Solution {
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        int m = nums1.size(), n = nums2.size(); 
        vector<int> result; 
        
        for (int i = max(0, k-n); i <= min(k, m); ++i) { 
            result = max(result, mergeVector(maxVector(nums1, i), maxVector(nums2, k-i))); 
        }
        return result; 
    }
    
    vector<int> maxVector(vector<int> nums, int k) { 
        int drop = nums.size() - k; 
        vector<int> result; 
        
        for (int num: nums) { 
            while (drop && result.size() && result.back() < num) { 
                result.pop_back(); 
                --drop; 
            }
            result.push_back(num); 
        }
        
        result.resize(k); 
        return result; 
    }
    
    vector<int> mergeVector(vector<int> nums1, vector<int> nums2) { 
        vector<int> result; 
        
        while (nums1.size() + nums2.size()) { 
            vector<int> & tmp = nums1 > nums2 ? nums1 : nums2; 
            result.push_back(tmp[0]); 
            tmp.erase(tmp.begin()); 
        }
        
        return result; 
    }
    
    
};

