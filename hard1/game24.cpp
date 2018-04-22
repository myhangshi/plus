#include <iostream> 
#include <vector> 
#include <unordered_map> 
#include <algorithm> 
#include <map> 

using namespace std; 

void helper(vector<double>& nums, double eps, bool & result) { 
        if (result) return; 
        
        if (nums.size() == 1) { 
            if (abs(nums[0] - 24) < eps) result = true; 
            return; 
        }
        
        for (int i = 0; i < nums.size(); ++i) { 
            for (int j = 0; j < i; ++j) { 
                double p = nums[i], q = nums[j]; 
                vector<double> t{p+q, p-q, q-p, p*q}; 
                if (p > eps) t.push_back(q/p); 
                if (q > eps) t.push_back(p/q); 
                
                nums.erase(nums.begin() + i); 
                nums.erase(nums.begin() + j); 
                
                for (double d : t) { 
                    nums.push_back(d); 
                    helper(nums, eps, result); 
                    nums.pop_back(); 
                }
            
            
                nums.insert(nums.begin() + j, q); 
                nums.insert(nums.begin() + i, p); 
            }
        }
    
}

bool judgePoint24(vector<int>& nums) {
        bool result = false; 
        double eps = 0.001; 
        vector<double> arr(nums.begin(), nums.end()); 
        helper(arr, eps, result); 
        return result; 
}
    

int main() 
{ 
    vector<int> vect{1,2,3, 8}; 

    bool result = judgePoint24(vect); 

    cout<<"answer  " << result; 
    cout << endl;

    return 0;
} 

