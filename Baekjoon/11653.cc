/* 11653 
 * 소수 걸러내는게 문제인것 같다. */
#include <stdio.h>
#include <memory.h>
#include <math.h>

int main(void) {
  long N;
  scanf("%ld", &N);
  int *num = (int *) malloc (sizeof(int) * (N + 1));
  memset(num, 1, sizeof(int) * (N + 1));
  int *prime = (int *) malloc (sizeof(int));

  int i = 2;
  int until = sqrt(N) > 2? sqrt(N): N;
  while (i <= until && N > 1) {
    printf("N : %d, i : %d\n", N, i);
    if (N % i == 0) {
      printf("%d\n", i);
      N = N / i;
    } else {
      i += 1;
    }
  }
  return 0;
}

/* 어떤 하나의 수가 소수인지를 판별해야 한다면 
 * sqrt() 이용해서 루프 돌리는게 좋겠지만
 * 여러 수를 확인해야 한다면 이렇게
 * 에라토스테네스의 체 방법이 좋은 듯하다
 * 그리고 쓸 거라면 소수로 이루어진 배열 반환도 같이 쓰는게 좋나봐
 */
int eratosthenes_sieve (int* num, int *prime, int max) {
  int prime_count = 0; // 반환값

  num[0] = 0;
  num[1] = 0;

  for (int i = 2; i < max; i++) {
    if (num[i]) { // 아직 지워지지 않은 수라면 소수에 등록한다.
      prime = (int *) realloc (prime, sizeof (int) * prime_count + 1);
      prime[prime_count] = i; 
      prime_count += 1;
      for (int j = 2 * i; j < max; j += i) {
        num[j] = 0;
      }
    } // end if
  }

  return prime_count;
}