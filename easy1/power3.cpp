class Solution {
public:
    bool isPowerOfThree2(int n) {
        while (n > 0 && n % 3 == 0) { 
            n /= 3; 
        }
        return n == 1; 
    }
    
     bool isPowerOfThree(int n) {
        return (n > 0 && 1162261467 % n == 0);
    }
    
};

