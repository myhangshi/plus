class Solution {
public:
    vector<string> letterCombinations(string digits) {    
        vector<string> result;
        string dict[] = {" ", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        
        if (digits.size() == 0) return result; 
        string comb(digits.size(), '\0'); 
        findLetterComb(digits, 0, dict, comb, result); 
        return result; 
    }
    
    void findLetterComb(string &digits, int index, string dict[], string &comb, 
                       vector<string> &result) 
    { 
        if (index == digits.size()) { 
            result.push_back(comb); 
            return; 
        }
        
        string lett = dict[digits[index]-'0']; 
        for (int i = 0; i < lett.size(); ++i) { 
            comb[index] = lett[i]; 
            findLetterComb(digits, index+1, dict, comb, result); 
        
        }
    
    
    }
    
    
};

