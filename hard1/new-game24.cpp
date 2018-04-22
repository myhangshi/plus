#include <iostream> 
#include <vector> 
#include <unordered_map> 
#include <algorithm> 
#include <map> 

using namespace std; 

   
bool helper(vector<double>& nums, vector<char>& ops, double eps) {
        if (nums.size() == 1) return abs(nums[0] - 24) < eps;
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = 0; j < nums.size(); ++j) {
                if (i == j) continue;
                vector<double> t;
                for (int k = 0; k < nums.size(); ++k) {
                    if (k != i && k != j) t.push_back(nums[k]);
                }
                for (char op : ops) {
                    if ((op == '+' || op == '*') && i > j) continue;
                    if (op == '/' && nums[j] < eps) continue;
                    switch(op) {
                        case '+': t.push_back(nums[i] + nums[j]); break;
                        case '-': t.push_back(nums[i] - nums[j]); break;
                        case '*': t.push_back(nums[i] * nums[j]); break;
                        case '/': t.push_back(nums[i] / nums[j]); break;
                    }
                    if (helper(t, ops, eps)) return true;
                    t.pop_back();
                }
            }
        }
        return false;
}


bool judgePoint24(vector<int>& nums) {
        double eps = 0.001;
        vector<char> ops{'+', '-', '*', '/'};
        vector<double> arr(nums.begin(), nums.end());
        return helper(arr, ops, eps);
}
 

int main() 
{ 
    vector<int> vect{1,2,3, 8}; 

    bool result = judgePoint24(vect); 

    cout<<"answer  " << result; 
    cout << endl;

    return 0;
} 

