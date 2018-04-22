class Solution {
public:
    string addStrings(string num1, string num2) {
        string result = ""; 
        int m = num1.size(), n = num2.size(); 
        int i = m - 1; 
        int j = n - 1; 
        int carry = 0; 
        
        while (i >= 0 || j >= 0) { 
            int a = i >= 0 ? num1[i--] - '0' : 0; 
            int b = j >= 0 ? num2[j--] - '0' : 0; 
            
            int sum = a + b + carry; 
            result.insert(result.begin(), sum % 10 + '0'); 
            carry = sum / 10; 
        }
        return carry ? "1" + result : result; 
    }
};


