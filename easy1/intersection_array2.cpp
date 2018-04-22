class Solution {
public:
    vector<int> intersect2(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> mp; 
        vector<int> result; 
        
        for (auto a: nums1) { 
            mp[a]++;         
        }
        
        for (auto a: nums2) { 
            if (mp.find(a) != mp.end() && mp[a] > 0) { 
                //if (mp.find(a) != mp.end() ) { 
                result.push_back(a); 
                mp[a]--; 
            }
        }
        return result; 
    }
    
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> m;
        vector<int> res;
        for (auto a : nums1) ++m[a];
        for (auto a : nums2) {
            if (m[a]-- > 0) res.push_back(a);
        }
        return res;
    }
};


