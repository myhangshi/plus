lass Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        vector<int> result; 
        
        int m = 0, n = 0, cn = 0, cm = 0; 
        for (int i = 0; i < nums.size(); ++i) { 
            if (nums[i] == m) cm++; 
            else if (nums[i] == n) cn++; 
            else if (cm == 0) { 
                m = nums[i]; 
                cm = 1; 
            } else if (cn == 0) { 
                n = nums[i]; 
                cn = 1; 
            } else { 
                cn--; cm--; 
            }
        }
        
        cm = cn = 0;
        for (auto &a : nums) {
            if (a == m) ++cm;
            else if (a == n) ++cn;
        }
        
        if (cm > nums.size() / 3) result.push_back(m);
        if (cn > nums.size() / 3) result.push_back(n);
        return result;
        
    }
};

