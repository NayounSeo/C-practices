#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

struct test_intr {
  uint32_t eax;
}

int main(void) {
  char* ptr;
  int a = 0x1900010;

  printf("%d     %x\n", a, a);
  printf("%lu     %lu\n", sizeof(int *), sizeof(uint64_t));


  ptr = (char*) malloc(sizeof(char) * 20);

  strcpy(ptr, "ACDEFGHIJKLMNOPQRSTUVWXYZ");

  puts(ptr);
  printf("%s\t %p\n", ptr, ptr);
  printf("%d\n", *(ptr + 1));  //두번 문자의 아스키

  if ((uint64_t)ptr > 0x1900010) {
    puts("들어오는거얌?");
  } else {
    puts("안되는거얌?");
  }




  return 0;
}