#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define MAX_ARR 128

struct stack {
  char *arr;
  int size;
  int top;
};

struct out_arr {
  char *arr;
  int size;
};

int stdin_open (struct stack *s, char *input, struct out_arr *out, int i);
void stdin_sharp (struct stack *s,  struct out_arr *out);

struct stack *create_stack(int arr_size);
struct out_arr *create_out_arr (int arr_size);
struct stack *make_empty_stack(struct stack *s);
int is_empty (struct stack *s);
void push (char x, struct stack *s);
void memorize_input (char x, struct out_arr *out);
char pop (struct stack *s);
void delete_stack (struct stack *s);

int main () {
  int arr_size = MAX_ARR;
  char input[MAX_ARR] = {'\0', };

  struct stack *s = create_stack (arr_size);
  struct out_arr *out = create_out_arr (arr_size);

  int i = 0;
  while (1) {
    fgets (input, arr_size, stdin);
    while (input[0] != '!' || i < MAX_ARR) {
      if (input[i] == '(') {
        i = stdin_open (s, input, out, i);
      } else if (input[i] == ')') {
        // stdin_close (s, out);
        // 솔직히 이건 짝이 안맞을 경우 + ㅋ하지만 이미 스택에 있는 애들은 살려야
        char x = pop (s);
        while (x != '\0') { // 스택의 내용을 출력 문자열로 이동시키고
          memorize_input (x, out);
          x = pop (s);
        }
        s->top = s->size; // 더이상 스택에 들어갈 수 없게
        i += 1;

      } else if (input[i] == '#') {
        stdin_sharp (s, out);
        break; // 안쪽 while 빠져나오기
      } else {
        push (input[i], s);
        i += 1;
      }
    }

    i = 0; // 초기화를 위해
  }

  delete_stack (s);
  return 0;
}

int stdin_open (struct stack *s, char *input, struct out_arr *out, int i) {
  printf ("\t\t\tstdin_open\n");
  char x = '\0'; // while 안에 있으면 왜..?ㅜㅠ
  char open = '(';

  int opn_cnt = 1;
  while (opn_cnt != 0) {
    if (input[i] == '(') {
      push (input[i], s);
    }
    i += 1;

    while (input[i] != ')') {
      if (input[i] == '(') {
        opn_cnt += 1;
      }
      push (input[i], s);
      i += 1;
    }

    // if (input[i] == ')') {
    while (strncmp (&x, &open, 1) != 0) {
      printf("문자열 비교 %d\n", strncmp (&x, &open, 1));
      x = pop (s);
      printf ("x : %c %d, input[i] : %c, i = %d\n", x, x, input[i], i);
      memorize_input (x, out);
    }
    // i += 1;
    // pop (s); // 남아있는 '('도 pop ()
    opn_cnt -= 1;
    // }
  }
  return i;
}

/*
void stdin_close (struct stack *s,  struct out_arr *out) {
  printf ("\t\t\tstdin_close\n");
  char x = pop (s);
  if (x == '\0') { // 스택이 비어있으면
    s->top = s->size;
    return;
  }
  while (x != '(') {
    out->arr[out->size] = x;
    out->size += 1;
    x = pop (s);
  }
}
*/

void stdin_sharp (struct stack *s,  struct out_arr *out) {
  printf ("\t\t\tstdin_sharp\n");
  int is_emt = is_empty (s);
  if (is_emt) {
    printf("right. ");
  } else {
    printf("wrong. ");
  }
  int out_size = out->size;
  int i;
  for (i = 0; i < out_size; i++) {
    printf ("%c", out->arr[i]);
  }

  make_empty_stack (s);
  // 하고 다시 입력 받을 수 있어야
}

// void stdin_exclamation (struct stack *s);

struct stack *create_stack (int arr_size) {
  struct stack *s = (struct stack *) malloc (sizeof (struct stack));
  s->arr = (char *) malloc (sizeof (char) * arr_size);
  s->size = arr_size;
  s->top = 0;

  
  printf ("stack top : %d, stack size : %d\n", s->top, s->size);

  return s;
}

struct out_arr *create_out_arr (int arr_size) {
  struct out_arr *out = (struct out_arr *) malloc (sizeof (struct out_arr));
  out->arr = (char *) malloc (sizeof (char) * arr_size);
  out->size = 0;
  return out;
}

// 아마 #이 입력됐을때, 그리고 빈 스택에 )이 들어왔을때 사용해야 함
struct stack *make_empty_stack(struct stack *s) {
  while (s->top != 0) {
    pop (s);
  }
  return s;
}

int is_empty (struct stack *s) {
  if (s->top == 0) {
    return 1;
  }
  return 0;
}

void push (char x, struct stack *s) {
  printf ("\t\tpush\n");
  if (s->top == s->size) {
    return;
  }
  printf ("stack top : %d, stack size : %d, char : %c\n", s->top, s->size, x);
  s->arr[s->top] = x;
  s->top += 1;
}

void memorize_input (char x, struct out_arr *out) {
  if (out->size == MAX_ARR) {
    return;
  }
  out->arr[out->size] = x;
  out->size += 1;
}

char pop (struct stack *s) {
  printf ("\t\tpop\n");
  if (s->top == 0) {
    return '\0';
  }
  char x = s->arr[s->top - 1];
  s->arr[s->top - 1] = '\0';
  s->top -= 1;

  return x;
}

void delete_stack (struct stack *s) {
  free (s->arr);
  free (s);
}