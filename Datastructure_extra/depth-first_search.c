#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define V 6

struct graph {
  struct list_node **graph;
  int vertices;
  int edges;
  int time;  // DFS에 쓰일 속성
};

struct list_node { // 리스트 노드
  int vertex; // 꼭지점 이름
  struct list_node *next;
};

struct queue {
  struct queue_node *front;
  struct queue_node *rear;
};

struct queue_node {
  int value;; // white, grey. black 중 하나의 값을 가짐
  char wgb; // white or grey or black
  int start; // 검색된 시점
  int end; // 검색이 끝난 시점
  struct queue_node *prev;
  struct queue_node *next;
};

struct graph *matrix_to_list (int **matrix, int vertices);
void insert_list_node (struct list_node **graph, struct list_node *new_node, int vertex);

struct queue_node **depth_first_search (struct graph *g, struct queue_node **vertexes);
void dfs_visit (struct graph *g, struct queue_node **vertexes, int index);

void enqueue (struct queue *q, struct queue_node *node);
struct queue_node *dequeue (struct queue *q);
struct queue_node *traverse_queue_node (struct queue *q, int value);

int main() {
  // 먼저 리스트를 준비해 줍시다. 
  int adj_mat[6][6] = {{0, 1, 0, 1, 0, 0},
                       {0, 0, 0, 0, 1, 0},
                       {0, 0, 0, 0, 1, 1},
                       {0, 1, 0, 0, 0, 0},
                       {0, 0, 0, 1, 0, 0},
                       {0, 0, 0, 0, 0, 1}};
  int i, j;
  int **matrix = (int **) malloc (sizeof (int *) * V);
  for (i = 0; i < V; i++) {
    matrix[i] = (int *) malloc (sizeof (int) * 6);
    memcpy (matrix[i], adj_mat[i], sizeof (int) * 6);
  }
  // 리스트로 표현된 그래프 반환
  struct graph *g = matrix_to_list (matrix, V);

  struct queue_node *vertexes[V];
  struct queue_node **result = depth_first_search (g, vertexes);

  for (i = 0; i < V; i++) {
    struct queue_node *node = result[i];
    // printf("꼭지점 value : %d\twgb : %c\tstart : %d\tend : %d\t prev : %d\n",
    printf("꼭지점 value : %d\twgb : %c\tstart : %d\tend : %d\t",
      node->value, node->wgb, node->start, node->end);
    if (node->prev != NULL) {
      printf("prev : %d\n", node->prev->value);
    } else {
      printf("\n");
    }
  }

  return 0;
}

// 인접 리스트를 만드는 함수들
struct graph *matrix_to_list (int **matrix, int vertices) {
  struct list_node **adj_list = (struct list_node **) malloc (sizeof (struct list_node *) * vertices);
  int edges = 0;
  int from, to;

  for (from = 0; from < vertices; from++) {
    for (to = 0; to < vertices; to++) {
      if (matrix[from][to] == 1) {
        struct list_node *new_node = (struct list_node *) malloc (sizeof (struct list_node));
        new_node->vertex = to;
        insert_list_node (adj_list, new_node, from);
        edges += 1;
      }
    }
  }

  struct graph *g = (struct graph *) malloc (sizeof (struct graph));
  g->graph = adj_list;
  g->vertices = vertices;
  g->edges = edges;
  g->time = 0;

  return g;
}

void insert_list_node (struct list_node **graph, struct list_node *new_node, int vertex) {
  if (graph[vertex] != NULL) {
    new_node->next = graph[vertex]; // graph[vertex] = graph[vertex][0] 이라고 생각해서!
  }
  graph[vertex] = new_node;
}

// BFS에 관련된 함수들
struct queue_node **depth_first_search (struct graph *g, struct queue_node **vertexes) {
  // struct queue_node *vertexes[V];
  int i;
  for (i = 0; i < V; i++) {
    struct queue_node *node = (struct queue_node *) malloc (sizeof (struct queue_node));
    node->value = i;
    node->wgb = 'w';
    vertexes[i] = node;
  }

  for (i = 0; i < V; i++) {
    if (vertexes[i]->wgb == 'w') {
      dfs_visit (g, vertexes, i);
    }
  }
  return vertexes;
}


void dfs_visit (struct graph *g, struct queue_node **vertexes, int index) {
  struct queue_node *node = vertexes[index];
  g->time += 1;
  node->start = g->time;
  node->wgb = 'g';

  struct list_node *cur = g->graph[node->value];  // index 정점과 연결된 다르 정점
  while (cur != NULL) {
    int vertex = cur->vertex;
    if (vertexes[vertex]->wgb == 'w') {
      vertexes[vertex]->prev = node;
      dfs_visit (g, vertexes, vertex);
    }
    cur = cur->next;
  }
  node->wgb = 'b';
  g->time += 1;
  node->end = g->time;
}

void enqueue (struct queue *q, struct queue_node *node) { // 큐의 끝에만 삽입
  printf("\tenqueue할 값 : %d\n", node->value);
  node->next = NULL;
  if (q->rear != NULL) {
    q->rear->next = node;
  }
  if (q->front == NULL) {
    q->front = node;
  }
  q->rear = node;
}

struct queue_node *dequeue (struct queue *q) {
  struct queue_node *head = q->front;
  if (q->front->next != NULL) { // 내 생각에는 NULL이면 그냥 NULL 될 것 같았는데...
    q->front = q->front->next;
  } else {
    q->front = NULL;
    q->rear = NULL;
    // head->next = NULL;
  }
  printf("\tdequeue value : %d\n", head->value);
  return head;
}

struct queue_node *traverse_queue_node (struct queue *q, int value) {
  struct queue_node *current = q->rear;

  while (current != NULL && current->value == value) {
    current = current->next;
  }
  return current;
}