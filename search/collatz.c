#include <stdio.h>

void collatz(unsigned int n){
  while(n > 1){
    printf("%u\t->\t", n);
    n = n & 1 ? n / 2 : n * 3 + 1;
  }
  printf("1");
}


