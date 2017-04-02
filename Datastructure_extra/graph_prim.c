/*
 * 2017. 03. 28. minimum spanning tree - prim
 * 프림 알고리즘대로면 사이클이 안생긴다
 * 
 * 귀찮으니 그냥 행렬로 풀겠다
 * 큐를 이용합니다
 */
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define V 9

// for graph
struct graph {
  struct list_node **graph;
  int v;
  int e;
};

struct list_node {
  int vertex;
  struct list_node *next;
};

// for prim
struct queue {
  struct v_node *front;
  struct v_node *rear;
};

struct v_node {
  int vertex;
  struct v_node *next; //
};

struct e_node {
  int from; // starting pt
  int to; // end pt
  int weight; 
}

int main() {
  int graph_matrix[V][V] = {{0, 45, 220, 79, 0, 0, 0, 0, 0}, // A
                            {45, 0, 0, 168, 98, 0, 0, 0, 0}, // B
                            {220, 0, 0, 0, 0, 10, 0, 0, 19}, // C
                            {79, 168, 0, 0, 15, 33, 60, 0, 0}, // D
                            {0, 98, 0, 15, 0, 0, 133, 63, 0}, // E
                            {0, 0, 10, 33, 0, 0, 93, 0, 65}, // F
                            {0, 0, 0, 60, 133, 93, 0, 100, 111}, // G
                            {0, 0, 0, 0, 63, 0, 100, 0, 0}, // H
                            {0, 0, 19, 0, 0, 65, 111, 0, 0}} // I
  int i;

  int **matrix = (int **) malloc (sizeof (int *) * V);
  for (i = 0; i < V; i++) {
    matrix[i] = (int *) malloc (sizeof (int) * V);
    memcpy (matrix[i], graph_matrix[i], sizeof (int) * V);
  }
  // 인접 리스트로 표현된 그래프 
  struct graph *g = matrix_to_list (matrix, vertices);



  return 0;
}

/*
 * graph : graph matrix
 * v : number of v
 * start : start index
 */
struct node *prim_search (struct graph *g, int start) {
  struct queue *origin_que = init_queue (); // 모든 정점들을 추가할 큐
  struct queue *prim_que = init_queue (); // 찾은 정점들을 추가할 큐
  // 찾은 간선들을 저장할 배열
  struct e_node *prim_edge = (struct e_node *) malloc (
                                      sizeof (struct e_node) * (g->v - 1));
  // 초기화
  for (i = 0; i < g->v; i++) { // 초기 정점들을 큐에 추가 (시작점 제외)
    if (i != start) {
      enqueue (origin_que, i);
    }
  }
  enqueue (prim_que, start) // 시작점 추가

  // 탐색
  int min_edge = 9999;
  int i;
  while (origin_que->front != NULL) {
 
    /*
     * 우선 해당 정점의 인접리스트를 돈다.
     *   해당 정점이 프림에 추가되어 있는지 체크한다. 혹은 큐에 있는지
     *     아직 없다면 최소 간선을 확인한다. 
     */

  }




}

struct queue *init_queue () {
  struct queue *que = (struct queue *) malloc (sizeof (struct queue));
  que->front = NULL;
  que->rear = NULL;
  return que;
}

void enqueue (struct queue *q, int vertex) {
  struct v_node *node = (struct v_node *) malloc (sizeof (struct v_node));
  v_node->vertex = vertex;

  if (q->front == NULL) {
    q->front = node;
  }

  if (q->rear != NULL) {
    q->rear->next = node;
  }
  q->rear = node;
}

struct v_node *dequeue (struct queue *q) {
  struct v_node *head = q->front;
  if (q->front->next != NULL) {
    q->front = q->front->next;
  } else {
    q->front = NULL;
    q->rear = NULL;
  }

  return head;
}

int search_que_value (struct queue *que, int vertex) {
  struct v_node *cur = que->front;
  while (cur != NULL) {
    if (cur->vertex == vertex) {
      return 1; // 해당 정점이 큐에 있다
    }
    cur = cur->next;
  }
  return 0; // 해당 정점이 큐에 없다.
}

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
  g->v = vertices;
  g->e = edges;

  return g;
}

void insert_list_node (struct list_node **graph, struct list_node *new_node, int vertex) {
  if (graph[vertex] != NULL) {
    new_node->next = graph[vertex];
  }
  graph[vertex] = new_node;
}

/*
* 나윤아 안녕 이건 키감이 좋구나
* 자원이랑 다니느라 많이 힘들지
* 힘내
* - 2017년 3월 31일 원민언니 ㅋㅋㅋㅋ
*/