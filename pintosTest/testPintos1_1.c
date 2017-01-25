#include <stdio.h>
#include <stdlib.h> //malloc!
#include <string.h>
#include <stdint.h>

void argument_stack(char **parse, int count, void **esp);

int main(void) {
  char *a = (char*) malloc(sizeof(char) * 100);
  char *temp;
  char *y;
  char **parse;
  int count = 0;
  int i = 0;

  /* 테스트를 위해 여유있게 할당 */
  void **esp = (void **) malloc(sizeof(void *) * 512);

  strcpy(a, "parpe94 puremint09 dophamipa109 cherrybit09");

  parse = (char**) malloc(sizeof(char*) * strlen(a));
  temp = strtok_r(a, " ", &y);
  parse[i] = (char*) malloc(sizeof(char) * strlen(temp));
  parse[i] = temp;

  while (temp != NULL) {
    count += 1;
    i += 1;
    temp = strtok_r(NULL, " ", &y);
    if (temp == NULL) {
      break;
    }
    parse[i] = (char*) malloc(sizeof(char) * strlen(temp));
    parse[i] = temp;
  }

  argument_stack(parse, count, esp);

  return 0;
}

void argument_stack(char **parse, int count, void **esp) {
  /* ppt 예제 코드 */
  int i, j;

  for (i = count - 1; i > -1; i--) {
    for (j = strlen(parse[i]); j > -1; j--) {
      *esp -= 1;
      **(char **)esp = parse[i][j];
    }
  }

  *esp -= 1;
  (unsigned) (**esp) = 0;
  *esp -= 1;
  **(char *)esp = 0;

  for (i = count - 1; i > -1; i--) {
    *esp -= 1;
    **(char *)esp = parse[i];
  }

  *esp -= 1;
  **(char **)esp = parse;
  *esp -= 1;
  **(int)esp = count;
  
  *esp -= 1;
  **esp = 0;
}


/* 예닮이랑 같이 고쳤던 코드 ㅜㅠㅜ 돌아가는데 스택에 이상한게 들어간다! */
void argument_stack(char ** parse, int count, void ** esp) {
  int i, j;

  for (i = count - 1; i > -1; i--) {
    for (j = strlen(parse[i]); j > -1; j--) {
      *esp -= 1;
      **(char **)esp = parse[i][j];
    }
  }

  /* 여기까지는 ppt에 있었고 문제도 없었던 듯
   * 워드 사이즈(4바이트)로 정렬 */
  *esp = (uint32_t) (*esp) & 0xfffffffc;

  *esp -= 4;
  memset(*esp, 0, sizeof(uint32_t));

  for (i = count - 1; i > -1; i--) {
    *esp -= 4;
    **(uint32_t **)esp = (uint32_t)parse[i];
  }

  *esp -= 4;
  **(uint32_t **)esp = (uint32_t)parse;
  *esp -= 4;
  **(uint32_t **)esp = (uint32_t)count;
  
  *esp -= 4;
  memset(*esp, 0, sizeof(uint32_t));
}


/* 복붙한 예닮이 코드 ㅜㅠㅜㅠㅜㅠ */
static void
argument_stack (char **parse, const int count, void **esp)
{
  int i, j;
  uint32_t argv_address[count];

  for (i = count - 1; i > - 1; i--)
    {
      *esp -= (strlen (parse[i]) + 1);
      memcpy (*esp, parse[i], strlen (parse[i]) + 1);
      // for (j = strlen (parse[i]); j > - 1; j--)
      //   {
      //     /* 한 글자 단위로 삽입하여 1바이트 연산 */
      //     *esp -= 1;
      //     **(char **) esp = parse[i][j];
      //   }
      argv_address[i] = (uint32_t) (*esp);
    }

  /* 워드 사이즈(4바이트)로 정렬
   * 정렬 후에는 포인터 연산시 4바이트씩 연산 */
  *esp = (uint32_t) (*esp) & 0xfffffffc;
  /* 구분자 NULL 을 스택에 삽입 */
  *esp -= 4;
  memset (*esp, 0, sizeof (uint32_t));

  for (i = count - 1; i > -1; i--)
    {
      *esp -= 4;
      *(uint32_t *) (*esp) = argv_address[i];
    }

  /* (**argv) 의 주소값을 스택에 삽입 
   * (**argv) 의 주소값 == (*argv[0]) 의 주소값 */
  *esp -= 4;
  *(uint32_t *) (*esp) = (uint32_t) (*esp) + 4;

  /* argc 의 주소값을 스택에 삽입 */
  *esp -= 4;
  *(uint32_t *) (*esp) = (uint32_t) count;

  /* 가짜 주소값을 스택에 삽입 */
  *esp -= 4;
  memset (*esp, 0, sizeof (uint32_t));
}