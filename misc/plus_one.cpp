class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int carry = 1; 
        vector<int> result; 
        
        int n = digits.size(); 
        
        for (int i = n - 1; i >= 0; i--) { 
            int c = carry + digits[i]; 
            carry = c / 10; 
            result.insert(result.begin(), c % 10); 
        }
        
        if (carry > 0) result.insert(result.begin(), carry);
        return result; 
    }
}; 

