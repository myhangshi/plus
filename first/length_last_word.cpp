class Solution {
public:
    int lengthOfLastWord(string s) {
        int index = s.size() - 1; 
        while (s[index] == ' ' && index >=0) index--;
        
        if (index < 0) return 0; 
        
        int low = index; 
        while (s[low] != ' ' && low >= 0) low--;
        
        if (low < -1) return 0; 
        else return index - low; 
    }
};


