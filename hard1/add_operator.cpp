class Solution {
public:
    vector<string> addOperators(string num, int target) {
        vector<string> result; 
        
        if (num.size() == 0) return result; 
        nextStep(num, 0, target, 0, "", 0, result); 
        return result; 
    }
    
    void nextStep(string& numStr, int cur_index, int& target, long value, 
                  string equation, long pre_num, vector<string>& result) { 
    
        if (value == target && cur_index == numStr.size()) { 
            result.push_back(equation); 
            return;
        }
        
        for (int i = 1; i < numStr.size() - cur_index + 1; i++) { 
           // if (i > 1 && numStr[cur_index] == '0') break; 
            string temp = numStr.substr(cur_index, i); 
            long num = stol(temp); 
            
            if (cur_index == 0) { 
                nextStep(numStr, cur_index+i, target, num, temp, num, result); 
                continue; 
            }
        
            nextStep(numStr, cur_index+i, target, value+num, equation+'+'+temp, num, result); 
            nextStep(numStr, cur_index+i, target, value-num, equation+'-'+temp, -num, result); 
            nextStep(numStr, cur_index+i, target, value-pre_num+pre_num*num, equation+'*'+temp, pre_num*num, result); 
            
        }
    
    }
    
};

