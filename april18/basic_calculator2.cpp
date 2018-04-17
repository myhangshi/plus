class Solution {
public:
    int calculate(string s) {
        int result = 0, d = 0; 
        char sign = '+'; 
        
        stack<int> nums; 
        
        for (int i = 0; i < s.size(); ++i) { 
            if (s[i] >= '0' && s[i] <= '9') { 
                d = d * 10 + s[i] - '0'; 
            }  
            
            if ((s[i] < '0' && s[i] != ' ') || i == (s.size() - 1)) { 
                if (sign == '+') nums.push(d); 
                if (sign == '-') nums.push(-d); 
                
                if (sign == '*' || sign == '/') { 
                    int tmp = sign == '*' ? nums.top() * d : nums.top() / d; 
                    nums.pop(); 
                    nums.push(tmp); 
                }
                sign = s[i]; 
                d = 0; 
            }    
        }
        
        while (!nums.empty()) { 
            result += nums.top(); 
            nums.pop(); 
        }
        return result; 
    
    }
};


