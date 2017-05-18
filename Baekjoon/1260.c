/* 2015-02-12
 * Baekjoon 1260
 * Write by Yedarm Seong */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *dfs_arr;
int *bfs_arr;
int number;

int InitMatrix(int **arr, int size);
int Connection(int **arr, int a, int b);
int DFS(int **arr, int vertex, int size);
int BFS(int **arr, int *queue, int vertex, int size);

int main() {
    int n, m, v;
    int a, b;
    int **arr;
    int *bfs_queue;
    int i, j;

    scanf("%d %d %d", &n, &m, &v);

    dfs_arr = (int *) malloc(sizeof(int) * n);
    bfs_arr = (int *) malloc(sizeof(int) * n);
    memset(dfs_arr, 0, sizeof(int) * n);
    memset(bfs_arr, 0, sizeof(int) * n);

    bfs_queue = (int *) malloc(sizeof(int) * n);
    memset(bfs_queue, 0, sizeof(int) * n);
    
    arr = (int **) malloc(sizeof(int *) * n);
    for (i = 0; i < n; i++) {
        arr[i] = (int *) malloc(sizeof(int) * n);
    }

    if (InitMatrix(arr, n) == 0) {
        return 0;
    }

    for (i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        if (Connection(arr, a - 1, b - 1) == 0) {
            return 0;
        }
    }

    number = 1;
    if (DFS(arr, v - 1, n) == 0) {
        return 0;;
    }

    number = 1;
    if (BFS(arr, bfs_queue, v - 1, n) == 0) {
        return 0;
    }

    number = 1;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (dfs_arr[j] == number) {
                printf("%d ", j + 1);
                number++;
                break;
            }
        }
    }
    puts("");

    number = 1;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (bfs_arr[j] == number) {
                printf("%d ", j + 1);
                number++;
                break;
            }
        }
    }
    puts("");

    return 0;
}

int InitMatrix(int **arr, int size) {
    if (arr == NULL) {
        return 0;
    }

    int i, j;

    for (i = 0; i < size; i++) {
        memset(arr[i], 0, sizeof(int) * size);
    }
    return 1;
}

int Connection(int **arr, int a, int b) {
    if (arr == NULL) {
        return 0;
    }

    arr[a][b] = 1;
    arr[b][a] = 1;
    return 1;
}

int DFS(int **arr, int vertex, int size) {
    if (arr == NULL) {
        return 0;
    }
    else if (size < 1) {
        return 0;
    }

    int i;
    dfs_arr[vertex] = number++;

    for (i = 0; i < size; i++) {
        if (arr[i][vertex] == 1) {
            if (dfs_arr[i] == 0) {
                DFS(arr, i, size);
            }
        }
    }
    return 1;
}

int BFS(int **arr, int *queue, int vertex, int size) {
    if (arr == NULL) {
        return 0;
    }
    else if (size < 1) {
        return 0;
    }

    int i;
    int front = 0;
    int rear = 0;
    bfs_arr[vertex] = number++;
    queue[rear] = vertex;
    rear++;

    while (1) {
        if (rear <= front) {
            break;
        }

        vertex = queue[front++];

        for (i = 0; i < size; i++) {
            if (arr[i][vertex] == 1) {
                if (bfs_arr[i] == 0) {
                    bfs_arr[i] = number++;
                    queue[rear] = i;
                    rear++;
                }
            }
        }
    }
    return 1;
}
