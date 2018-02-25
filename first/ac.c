#include <stdio.h> 
#include <string.h> 
#include <ctype.h> 

bool isPalindrome(char* s) {
    int low = 0; 
    int high = strlen(s); 
    
    while (low < high) {
        while (!isalnum(s[low]) && low < high) low++; 
        while (!isalnum(s[high]) && low < high) high--; 
        if (low > high) return false; 
	printf(" %d low %d high \n", low, high); 
        
        if (tolower(s[low++]) != tolower(s[high--]))
            return false; 
    }
    return true; 
}


int main() 
{ 
	
	char *s = "hello"; 

	int len = strlen(s); 
	
	printf("Hello World!%u \n", len);
	printf("is palindrome %d \n", isPalindrome("aa")); 
 
	return 0; 
} 

