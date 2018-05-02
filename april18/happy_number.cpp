http://www.cnblogs.com/grandyang/p/4447233.html



class Solution {
public:
    int getSquare(int n) { 
        int sum = 0; 
        while (n > 0) {  
            sum += (n % 10) * (n % 10); 
            n = n / 10; 
        }
        return sum; 
    }
    
    
    bool isHappyKK(int n) {
        
        set<int> s;
        while (n != 1 && s.count(n) == 0) { 
            s.insert(n); 
            n = getSquare(n); 
        }
        
        return (n == 1); 
    }
    
     bool isHappy(int n) {
        set<int> s;
        while (n != 1) {
            int t = 0;
            while (n) {
                t += (n % 10) * (n % 10);
                n /= 10;
            }
            n = t;
            if (s.count(n)) break;
            else s.insert(n);
        }
        return n == 1; 
     } 
            
};

