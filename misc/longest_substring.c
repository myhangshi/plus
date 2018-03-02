class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int ASCII_NUM = 255; 
        int count[ASCII_NUM] = {0}; 
        int start = 0; 
        
        fill(count, count + ASCII_NUM, -1); 
        int max_len = 0; 
        for (int i = 0; i < s.size(); i++) { 
            if (count[s[i]] >= start) { 
                max_len = max(max_len, i - start);  
                start = count[s[i]] + 1; 
            }
            count[s[i]] = i; 
        }
        return max(max_len, (int)s.size() - start); 
    }
};


