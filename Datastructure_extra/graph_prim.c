/*
 * 2017. 03. 28. minimum spanning tree - prim
 * 프림 알고리즘대로면 사이클이 안생긴다
 * 
 * 귀찮으니 그냥 행렬로 풀겠다
 * 큐를 이용합니다
 * 우선순위 큐 왜 쓰지ㅜㅠㅜ 산으로 가는 코드...
 */
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define V 9

// for graph - e_node
struct graph {
  struct e_node **graph;
  int v;
  int e;
};

// for queue prim - v_node
struct queue {
  struct v_node *front;
  struct v_node *rear;
};

struct v_node {
  int vertex;
  // int key;
  struct v_node *pre; //
  struct v_node *next; //
};

struct e_node {
  int from; // starting pt
  int to; // end pt
  int weight;
  int add_prim; // prim 간선인지의 여부
  struct e_node *next;
};

struct e_node **prim_search (struct graph *g, int start);
struct queue *init_queue ();
void enqueue (struct queue *q, int vertex);
void temp_enqueue (struct queue *q, int vertex);
struct v_node *dequeue (struct queue *q);
struct v_node *temp_dequeue (struct queue *q, int vertex);
int search_que_value (struct queue *que, int vertex);
struct graph *matrix_to_list (int **matrix, int vertices);
void insert_list_node (struct e_node **graph, struct e_node *new_node, int vertex);

int main() {
  int graph_matrix[V][V] = {{0, 45, 220, 79, 0, 0, 0, 0, 0}, // A
                            {45, 0, 0, 168, 98, 0, 0, 0, 0}, // B
                            {220, 0, 0, 0, 0, 10, 0, 0, 19}, // C
                            {79, 168, 0, 0, 15, 33, 60, 0, 0}, // D
                            {0, 98, 0, 15, 0, 0, 133, 63, 0}, // E
                            {0, 0, 10, 33, 0, 0, 93, 0, 65}, // F
                            {0, 0, 0, 60, 133, 93, 0, 100, 111}, // G
                            {0, 0, 0, 0, 63, 0, 100, 0, 0}, // H
                            {0, 0, 19, 0, 0, 65, 111, 0, 0}}; // I
  int i;

  int **matrix = (int **) malloc (sizeof (int *) * V);
  for (i = 0; i < V; i++) {
    matrix[i] = (int *) malloc (sizeof (int) * V);
    memcpy (matrix[i], graph_matrix[i], sizeof (int) * V);
  }
  // 인접 리스트로 표현된 그래프 
  struct graph *g = matrix_to_list (matrix, V);

  struct e_node **prim_edge = prim_search (g, 0);
  /*
  int sum = 0;
  for (i = 0; i < V - 1; i++) {
    printf ("edge from : %d to : %d weight : %d\n", prim_edge[i]->from, prim_edge[i]->to, prim_edge[i]->weight);
    sum += prim_edge[i]->weight;
  }
  printf ("total weight : %d\n", sum);
  */
  return 0;
}

/*
 * graph : graph matrix
 * v : number of v
 * start : start index
 */
struct e_node **prim_search (struct graph *g, int start) {
  struct queue *origin_que = init_queue (); // 모든 정점들을 추가할 큐
  struct queue *prim_que = init_queue (); // 찾은 정점들을 추가할 큐
  // 찾은 간선들을 저장할 배열
  struct e_node **prim_edge = (struct e_node **) malloc (
                                      sizeof (struct e_node *) * (g->v - 1));
  int i;
  // 초기화
  for (i = 0; i < g->v; i++) { // 초기 정점들을 큐에 추가 (시작점 제외)
    if (i != start) {
      temp_enqueue (origin_que, i);
      // enqueue (origin_que, i);
    }
  }
  temp_enqueue (prim_que, start); // 시작점 추가
  // enqueue (prim_que, start) // 시작점 추가

  // 탐색 - 노드 성질에 주의ㅜㅠ
  struct v_node *from_A;
  struct e_node *to_B;
  struct e_node *min_e = (struct e_node *) malloc (sizeof (struct e_node));
  i = 0;

  /*
   * 우선 해당 정점의 인접리스트를 돈다.
   *   해당 정점이 프림에 추가되어 있는지 체크한다. 혹은 큐에 있는지
   *     아직 없다면 최소 간선을 확인한다. 
   */
  while (origin_que->front != NULL) {
    min_e->weight = 9999;
    from_A = prim_que->front;
    while (from_A != NULL) { // 이미 추가된 정점들에 대해
      to_B = g->graph[from_A->vertex];
      while (to_B != NULL) { // A 정점에 연결된 간선에 대하여 
        // 간선이 min 값보다 작고 이미 추가된 prim 간선이 아니라면
        if (to_B->weight < min_e->weight && to_B->add_prim != 1) {
          printf("min_e weight %d to_B weigth %d\n", min_e->weight, to_B->weight);
          min_e = to_B;
        }
        to_B = to_B->next;
      }
      from_A = from_A->next;
    }

    // TODO : 확인된 최소 프림 간선을 추가할 부분, 정점을 추가해야하는 부분
    prim_edge[i] = (struct e_node *) malloc (sizeof (struct e_node));
    prim_edge[i] = min_e;
    min_e->add_prim = 1;
    i += 1;
    struct v_node *temp = temp_dequeue (origin_que, to_B->to);
    // struct v_node *temp = temp_dequeue (origin_que, to_B->to);
    // free (temp);
    temp_enqueue (prim_que, to_B->to);
  }

  return prim_edge;
}

struct queue *init_queue () {
  struct queue *que = (struct queue *) malloc (sizeof (struct queue));
  que->front = NULL;
  que->rear = NULL;
  return que;
}

void enqueue (struct queue *q, int vertex) {
  struct v_node *node = (struct v_node *) malloc (sizeof (struct v_node));
  node->vertex = vertex;

  if (q->front == NULL) {
    q->front = node;
  }

  if (q->rear != NULL) {
    q->rear->next = node;
  }
  q->rear = node;
}

void temp_enqueue (struct queue *q, int vertex) {
  struct v_node *node = (struct v_node *) malloc (sizeof (struct v_node));
  node->vertex = vertex;
  node->next = NULL;

  if (q->front == NULL) {
    q->front = node;
    node->pre = NULL;
  } else {
    q->rear->next = node;
    node->pre = q->rear;
  }
  q->rear = node;
}

// void priority_enqueue (struct queue *q, int vertex) { }

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

struct v_node *temp_dequeue (struct queue *q, int vertex) {
  printf ("함수들어와쬬어 뿌우~~~\n");
  struct v_node *cur = q->front;
  while (cur != NULL) {
    if (cur->vertex == vertex) {
      // 머리일때, 끝일때, 중간일때 모두 아울러서
      if (cur == q->front) {
        printf ("11111111111\n");
        cur->next->pre = q->front;
        q->front = cur->next;
      } else if (cur == q->rear) {
        printf ("1122222222221\n");
        cur->pre->next = NULL;
        q->rear = cur->pre;
      } else {
        printf ("33333333331\n");
        cur->pre->next = cur->next;
        cur->next->pre = cur->pre;
      }
      return cur;
    }
    cur = cur->next;
  }
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

// 가중치가 있는 그래프를 위해 변경한 코드
struct graph *matrix_to_list (int **matrix, int vertices) {
  struct e_node **adj_list = (struct e_node **) malloc (sizeof (struct e_node *) * vertices);
  int edges = 0;
  int from, to;

  for (from = 0; from < vertices; from++) {
    for (to = 0; to < vertices; to++) {
      if (matrix[from][to] > 0) { // 가중치가 있다면
        struct e_node *new_node = (struct e_node *) malloc (sizeof (struct e_node));
        new_node->from = from;
        new_node->to = to;
        new_node->weight = matrix[from][to]; // 가중치를 함께 기록
        new_node->add_prim = 0; // 프림 간선이 아니다
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

void insert_list_node (struct e_node **graph, struct e_node *new_node, 
                       int vertex) {
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
