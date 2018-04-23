class Solution {
public:
    //https://www.cnblogs.com/grandyang/p/4629032.html
    int countDigitOne(int n) {
        int result = 0; 
        int a = 1, b = 1; 
        
        while (n > 0) { 
            result += (n+8)/10 * a + (n%10 ==1)*b; 
            b += n % 10 * a; 
            a *= 10; 
            n /= 10; 
        
        }
        return result; 
    }
};


