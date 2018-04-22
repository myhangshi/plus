#include <stdio.h> 

int arrangeCoins(int n) {
        int sum = 0, i = 1;  

	while (n > i) { 
	   n -= i; 
	   i++;  
	} 
	printf(" i %d sum %d n %d \n", i, sum, n); 

        return i; 
}


int main() 
{ 
    
    int k = arrangeCoins(5); 
    printf("hello world %d \n", k); 



    return 0; 
} 
