#include <stdio.h>
#include <stdlib.h> //malloc!
#include <string.h>

int main(void) {
  char *a = (char*) malloc(sizeof(char) * 100);
  char *temp;
  char *y;
  char **parse;
  int count = 0;
  int i = 0;

  strcpy(a, "parpe94 puremint09 dophamipa109 cherrybit09");

  parse = (char**) malloc(sizeof(char*) * strlen(a));
  temp = strtok_r(a, " ", &y);
  printf("%s------------------\n", a);
  printf("%s------------------\n", temp);
  puts("*********************************");
  parse[i] = (char*) malloc(sizeof(char) * strlen(temp));
  parse[i] = temp;

  while (temp != NULL) {
    count += 1;
    i += 1;
    temp = strtok_r(NULL, " ", &y);
    printf("%s------------------\n", a);
    printf("%s------------------\n", temp);
    puts("*********************************");
    if (temp == NULL) {
      break;
    }
    parse[i] = (char*) malloc(sizeof(char) * strlen(temp));
    parse[i] = temp;
  }

  printf("%d\n", count);

  return 0;
}
