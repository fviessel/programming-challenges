#include<stdio.h>
#include<stdbool.h>

int main(void) {
  int n = 1;
  while(n != 0x7FFFFFFF) {
    bool print_number = true;
    if(n%3 == 0) { printf("Fizz"); print_number = false; }
    if(n%5 == 0) { printf("Buzz"); print_number = false; }
    
    if(print_number) {
      printf("%d", n);
    }

    printf("\n");
    n += 1;
  }
}
