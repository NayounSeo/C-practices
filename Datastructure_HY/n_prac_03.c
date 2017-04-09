#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

struct stack {
  char *arr;
  int size;
  int top;
};

struct out_arr {
  char *arr;
  int size;
};

void stdin_open (struct stack *s, struct out_arr *out);
void stdin_close (struct stack *s, struct out_arr *out);
void stdin_sharp (struct stack *s, struct out_arr *out);
struct stack *create_stack(int arr_size);
struct out_arr *create_out_arr (int arr_size);
struct stack *make_empty_stack(struct stack *s);
int is_empty (struct stack *s);
void push (char x, struct stack *s);
char pop (struct stack *s);
void delete_stack (struct stack *s);

int main () {
  char in = '.';
  int arr_size = 128;
  struct out_arr *out = create_out_arr (arr_size);
  struct stack *s = create_stack (arr_size);
  scanf ("%c", &in);

  while (in != '!') {
    fflush (stdin);
    if (in == '(') {
      puts("((((");
      stdin_open (s, out);
    } else if (in == ')') {
      puts("))))");
      stdin_close (s, out);
    } else if (in == '#') {
      puts("####");
      stdin_sharp (s, out);
    } else {
      puts("elseelseelseelse");
      out->arr[out->size] = in;
      out->size += 1;
      scanf ("%c", &in);
    }
  }

  delete_stack (s);
  return 0;
}

void stdin_open (struct stack *s,  struct out_arr *out) {
  printf ("\t\t\tstdin_open\n");
  char x;
  push ('(', s);

  scanf("%c", &x);
  while ((x != 41) || (x != 35)) {
    printf ("x = %c, %d\n", x, x);
    push (x, s);
    scanf("%c", &x);
  }
  if (x == ')') { // ) 이 입력되서 push가 끝났다면
    stdin_close (s, out);
    // 이 다음?
  } else if (x == '#') {
    stdin_sharp (s, out);
    // 이 다음?
  }
}

void stdin_close (struct stack *s,  struct out_arr *out) {
  printf ("\t\t\tstdin_close\n");
  char x = pop (s);
  if (x == '\0') { // 스택이 비어있으면
    // #을 제외한 문자들을 무시하도록 - push 할 수 없도록
    s->top = s->size;
    return;
  }
  while (x != '(') {
    out->arr[out->size] = x;
    out->size += 1;
    x = pop (s);
  }
  // TODO : 다시 입력을 받을 수 있어야 한다. 
}

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

char pop (struct stack *s) {
  printf ("\t\tpop\n");
  if (s->top == 0) {
    return '\0';
  }
  char x = s->arr[s->top - 1];
  s->top -= 1;

  return x;
}

void delete_stack (struct stack *s) {
  free (s->arr);
  free (s);
}