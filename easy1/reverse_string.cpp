#include <stdio.h> 

char* reverseString(char* s) {
      char *end = s, *start = s; 
      while (*end) end++; 
    
      end--; 
      while (start < end) { 
          char c = *start; 
          *start = *end;
          *end = c;      
          start++, end--; 
      } 
      return s; 
}


int main() 
{ 
    char s[] = "hello"; 
    printf("hello world %s \n", s); 
    
    char *p = reverseString(s); 
    printf("hello world %s \n", p); 



    return 0; 
} 
