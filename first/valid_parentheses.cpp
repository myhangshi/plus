class Solution {
public:
    bool isValid(string s) {
        stack<char> stk; 
        string left = "({["; 
        string right = ")}]"; 
        
        for (int i = 0; i < s.size(); i++) { 
            char ch = s[i]; 
            if (left.find(ch) != string::npos) { 
                stk.push(ch); 
            } else { 
                if (stk.empty()) return false; 
                if (right.find(ch) == string::npos) continue; 
                if (stk.top() == left[right.find(ch)]) 
                    stk.pop(); 
                else return false; 
            }
        
        }
        return stk.empty(); 
        
    }
};

