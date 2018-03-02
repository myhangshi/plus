#include <stdio.h> 
#include <string.h> 
#include <ctype.h> 
#include <math.h> 


int reverse(int x) {
        long long t = x > 0 ? x : -x; 
        long long result = 0; 
        
        while (t > 0) { 
            result = result * 10 + t % 10; 
		printf("the result is t %ld \n", result); 
            t = t /10; 
        }

        
        if (result > pow(2, 31) ) result = 0; 
        
        if (x > 0) return result; 
        else return -result; 
        
}


int main() 
{ 
	

	int len = 100; 
	
	// printf("is %d \n", reverse(1534236469)); 
	printf("is %d \n", reverse(1563847412)); 
 
	return 0; 
} 

class Solution {
public:
    int reverse(int x) {
        long long t = x > 0 ? x : -x; 
        long long result = 0; 
        
        while (t > 0) { 
            result = result * 10 + t % 10; 
            t = t /10; 
        }
        
        if (result > pow(2,31) ) result = 0; 
        //bool sign = x > 0 ? false : true; 
        
        //if (result > 2147483647 || (sign && result > 2147483648)) 
        //    return 0; 
        
        if (x > 0) return result; 
        else return - result; 
        
    }
};
