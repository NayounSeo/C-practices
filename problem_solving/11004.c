/*
 * N번째 수를 quick sort를 이용해 풀어봅시다 
 * 1월에 C++로 풀었지만 4월 말에 C로 품...
 */
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>

int nth_element (int *arr, int to, int k);
int quick_partition (int *arr, int from, int to);

int main() {
  int n, k;
  int i;

  scanf("%d %d", &n, &k);
  int *arr = (int *) malloc (sizeof (int) * n);
  for (i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
  }

  int k_th = nth_element (arr, n, k);
  printf ("%d\n", k_th);

  return 0;
}

int nth_element (int *arr, int to, int k) {
  int from = 0;
  to -= 1;   // due to index
  k -= 1;   // due to index

  int mark = quick_partition (arr, from, to);
  while (mark != k) {
    if (k == -1) { // 모든 원소가 같아부리는뎁쇼
      mark = 0;
      break;
    }

    if (k < mark) {
      mark = quick_partition (arr, from, mark - 1);
    } else {
      mark = quick_partition (arr, mark + 1, to);
    }
  }
  return arr[mark];
}

int quick_partition (int *arr, int from, int to) {
  int i; // less than
  int j; // greater
  int temp;
  for (i = from - 1, j = from; j < to; j++) {
    if (arr[j] <= arr[to]) {
      i += 1;
      temp = arr[j];
      arr[j] = arr[i];
      arr[i] = temp;
    }
  }

  if (i + 1 > to) { // 모든 원소가 같았을 때
    return -1;
  }

  i += 1;
  temp = arr[i];
  arr[i] = arr[to];
  arr[to] = temp;

  return i;
}