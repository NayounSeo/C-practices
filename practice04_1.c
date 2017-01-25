#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node* prev;
    struct Node* next;
};

typedef struct Node* PtrtoNode;

typedef struct list {
    PtrtoNode head;
    PtrtoNode tail;
} List;

List* list;

void createList();
void insertNode(int e);
void insertNodeRight(PtrtoNode h, int X);
void insertNodeLeft(PtrtoNode h, int X);
void print(PtrtoNode list);
PtrtoNode find(PtrtoNode h, int X);
void deleteNode(PtrtoNode h, int X);

int main() {
    char function[3];
    int a, b;

    createList();

    //list는 포인터니까 포인터가 가리키는 공간으로 넣어줍니다 
    //(*list 였나 그랬음.. createList에서 List* 만들어주고 반환하고 그거 써야 했을 때)
    //insertNode(0);
    /* 디버깅에서 -
     * *list = {head=0x0000020efaacb00{value=-84215.. prev=NULL next=NULL}...}
     * list = 0x0000020efaae2c0{head=0x0000020efaacb00{val....}...}
     * 처럼 나온다. 닮이가 그려주는 그림으로도 이해가 된다 - 
     * 포인터가 가리키는 것은 malloc이 할당해주는 공간
     */

    do {
        scanf("%s", function);
        
        if (strcmp(function, "i") == 0) {
            scanf("%d", &a);
            insertNode(a);
            continue;
        }
        if (strcmp(function, "iL") == 0) {
            scanf("%d %d", &a, &b);
            PtrtoNode ptr = find(list->head, a);
            insertNodeLeft(ptr, b);
            continue;
        }
        if (strcmp(function, "iR") == 0) {
            scanf("%d %d", &a, &b);
            PtrtoNode ptr = find(list->head, a);
            insertNodeRight(ptr, b);
            continue;
        }
        if (strcmp(function, "d") == 0) {
            scanf("%d", &a);
            deleteNode(list->head, a);
            continue;
        }
        if (strcmp(function, "p") == 0) {
            print(list->head);
            break;
        }

    } while (strcmp(function, "p") != 0);

    return 0;
}

void createList() {
    list = (List*) malloc(sizeof(List));
    list->head = (struct Node*) malloc(sizeof(struct Node));
    list->head->prev = NULL;
    list->tail = NULL;
    list->head->next = list->tail;

    return;
}

void insertNode(int e) {
    if (list->tail == NULL) {
        insertNodeRight(list->head, e);
        return;
    }
    insertNodeRight(list->tail, e);
    return;
}

void insertNodeRight(PtrtoNode h, int X) {
    PtrtoNode newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->value = X;
    newNode->next = h->next;
    newNode->prev = h;

    if (h->next == NULL) {
        h->next = newNode;
        list->tail = newNode;
    } else {
        h->next->prev = newNode;
        h->next = newNode;
    }
    return;
}

void insertNodeLeft(PtrtoNode h, int X) {
    PtrtoNode newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->value = X;
    newNode->prev = h->prev;
    newNode->next = h;

    if (h->prev == NULL) {
        h->prev = newNode;
    } else {
        h->prev->next = newNode;
        h->prev = newNode;
    }
    return;
}

void print(PtrtoNode head) {
    PtrtoNode current = head;
    if (head == list->head) {
        current = head->next;
    }

    while (current != NULL) {
        printf("%d -> ", current->value);
        current = current->next;
    }
    printf("\n");
    return;
}

void deleteNode(PtrtoNode h, int X) {
    PtrtoNode found = find(h, X);
    if (found != NULL) {
        found->prev->next = found->next;
        if (found != list->tail) {
            found->next->prev = found->prev;
        } else {
            found->prev = list->tail;
        }
        //이건 필요한 코드인가?
        found->prev = NULL;
        found->next = NULL;
        free(found);
    }
}

PtrtoNode find(PtrtoNode head, int X) {
    PtrtoNode current = head;

    while (current != NULL) {
        if (current->value == X) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}