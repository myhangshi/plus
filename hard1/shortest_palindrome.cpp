class Solution {
public:
    // http://www.cnblogs.com/grandyang/p/4523624.html
    // https://blog.csdn.net/v_july_v/article/details/7041827
    
    string shortestPalindrome(string s) {
        string t = s;
        reverse(t.begin(), t.end()); 
        int n = s.size(); 
        int i = 0; 
        
        for (i = n; i > 0; --i) { 
            if (s.substr(0, i) == t.substr(n-i)) { 
                break; 
            }
        }
        
        return t.substr(0, n - i) + s; 
    }
};


