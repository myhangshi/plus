
//http://www.cnblogs.com/grandyang/p/4431646.html
class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        int d = INT_MAX;
        while ((m & d) != (n & d)) {
            d <<= 1;
        }
        return m & d;
    }
};
class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        int d = 0;
        while (m != n) {
            m >>= 1;
            n >>= 1; 
            d++; 
        }
        return (m << d);
    }
};


