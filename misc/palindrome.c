#include <stdio.h> 
#include <string.h> 
#include <ctype.h> 
#include <math.h> 
#define false 0 
#define true  1

#define bool int 


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

    bool isPalindrome(int x) {
        int r = 1; 
        
        if (x < 0) return false; 
        
        while (r <= x / d)
            r = r * 10; 
        printf("r is %d ", r); 

 
        while (x > 0) { 
            if ((x / r) != (x % 10))
                return false; 
            x = (x % r) / 10; 
            r = r / 100; 
            
        }
        return true; 
    }



int main() 
{ 
	

	int len = 100; 
	
	// printf("is %d \n", reverse(1534236469)); 
	printf("is %d \n", isPalindrome(1410110141)); 
 
	return 0; 
} 

