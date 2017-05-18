/* 십진법 끝자리 0의 개수 
 * nCm = n!/(n - m)!(m)! 
 * 분자 : n * (n - 1) * ... * (n - m + 1) if n < 2m
 * 분모 : m!
 */
#include <stdio.h>
#include <math.h>

int cnt_5 (int num);
int cnt_2 (int num);

int main() {
  long n;
  long m;
  scanf("%ld %ld", &n, &m);
  long n_m = (n - m) > m? (n - m) : m;

  int num_2 = 0;
  int num_5 = 0;

  // printf("분자\n");
  while (n > n_m) {  // 분자
    // printf("\tn : %ld\n", n);
    if (n % 5 == 0) {
      num_5 += cnt_5 (n);
      // printf("\t\tn : %ld, num_5 : %d\n", n, num_5);
    }
    if (n % 2 == 0) {
      num_2 += cnt_2 (n);
      // printf("\t\tn : %ld, num_2 : %d\n", n, num_2);
    }
    n -= 1;
  }
  // printf("\tnum_5 : %d,\tnum_2 : %d\n", num_5, num_2);

  // printf("분모\n");
  while (n_m > 0) {  // 분모
    // printf("\tn_m : %ld\n", n_m);
    if (n_m % 5 == 0) {
      num_5 -= cnt_5 (n_m);
      // printf("\t\tn_m : %ld, num_5 : %d\n", n_m, num_5);
    }
    if (n_m % 2 == 0) {
      num_2 -= cnt_2 (n_m);
      // printf("\t\tn_m : %ld, num_2 : %d\n", n_m, num_2);
    }
    n_m -= 1;
  }
  // printf("\tnum_5 : %d,\tnum_2 : %d\n", num_5, num_2);

  int result = num_5 > num_2? num_2 : num_5;
  printf("%d\n", result);

  return 0;
}

int cnt_5 (int num) {
  int cnt = 0;
  int max_cnt_pow_5 = floor(log(num) / log(5));

  while (max_cnt_pow_5 > 0) {
    int pow_5 = pow(5, max_cnt_pow_5);

    while (num % pow_5 == 0 && num > 1) {
      cnt += max_cnt_pow_5;
      num /= pow_5;
    }

    max_cnt_pow_5 -= 1;
  }
  return cnt;
}

int cnt_2 (int num) {
  int cnt = 0;
  int max_cnt_pow_2 = floor(log(num) / log(2));

  while (max_cnt_pow_2 > 0) {
    int pow_2 = pow(2, max_cnt_pow_2);

    while (num % pow_2 == 0 && num > 1) {
      cnt += max_cnt_pow_2;
      num /= pow_2;
    }

    max_cnt_pow_2 -= 1;
  }
  return cnt;
}