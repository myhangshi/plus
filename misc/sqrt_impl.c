class Solution {
public:
    int mySqrt(int x) {
        
        int low, high, mid, last_mid; 
        
        if (x < 2) return x; 
        low = 1; 
        high = x / 2; 
        last_mid = 0; 
        
        while (low <= high) { 
            mid = low + (high - low) / 2; 
            int v = x / mid; 
            
            if ( v > mid) { 
                low = mid + 1; 
                last_mid = mid; 
            } else if (v < mid) { 
                high = mid - 1; 
                
            } else return mid; 
            
        }
        
        return last_mid; 
    }
};

