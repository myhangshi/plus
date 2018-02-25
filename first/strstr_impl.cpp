int strStr(char* haystack, char* needle) {
    int lh, ln; 
    char *h; 
    int i, j; 
    
    lh = strlen(haystack); 
    ln = strlen(needle); 
    
    for (j = 0; j < lh - ln + 1; j++) { 
        for (i = 0; i < ln; i++) { 
            if (haystack[i + j] != needle[i]) break; 
        }
        if (i == ln) return j; 
    }
    
    return -1; 
}



class Solution {
public:
    int strStr(string haystack, string needle) {
        int lh, ln; 
        int i, j; 
        
        lh = haystack.size(); 
        ln = needle.size(); 
        
        for (j = 0; j < lh - ln + 1; j++) { 
            for (i = 0; i < ln; i++) { 
                if (needle[i] != haystack[i + j]) 
                    break; 
            }
            if (i == ln) return j; 
        }
        return -1; 
    }
};


