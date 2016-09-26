#include <stdio.h>
#include <stdlib.h>

typedef int Element;
typedef struct Node* PtrToNode;
struct Node {
    Element data;
    PtrToNode next;
};
typedef PtrToNode Position;
typedef PtrToNode List;     //연결리스트마다 머리의 역할을 하는 변수!!*

void initList(List list);
void insertNode(Element X, List list);
void deleteNode(Element X, List list);
void display(List list);
Position find(Element X, List list);
Position findPrevious(Element X, List list);

int main() {
    List list = NULL;
    initList(&list);

    insertNode(1, list);
    insertNode(2, list);
    insertNode(3, list);
    insertNode(4, list);
    insertNode(5, list);
    insertNode(6, list);
    insertNode(7, list);

    display(list);

    deleteNode(7, list);
    display(list);
    deleteNode(5, list);
    display(list);
    deleteNode(8, list);
    display(list);

    printf("\n");
    Position found1 = find(4, list);
    printf("%p\n", found1);

    insertNode(9, list);
    insertNode(10, list);

    Position found2 = findPrevious(6, list);
    printf("%p\n", found2);
    display(list);

    deleteNode(1, list);
    display(list);

    deleteNode(2, list);
    display(list);

    return 0;
}

//☆★☆ 처음이라서? 주소로 넘겨줘야 함 주의!ㅜㅠ
void initList(List* list) {
    *list = (struct Node*) malloc(sizeof(struct Node));
    (*list)->next = NULL;
}

void insertNode(Element X, List list) {
    PtrToNode current;
    PtrToNode newNode;
    newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->data = X;
    newNode->next = NULL;

    current = list;
    while (current != NULL) {
        if (current->next == NULL) {
            current->next = newNode;
            return;
        }
        current = current->next;
    }

    return;
}

void deleteNode(Element X, List list) {
    PtrToNode current = list;

    while (current->next != NULL) {
        if (current->next->data == X) {
            PtrToNode temp = current->next;
            current->next = temp->next;
            printf("%d(을)를 가진 첫 노드 %p를 삭제했습니다.\n", X, temp);
            free(temp);
            return;
        }
        current = current->next;
    }
    printf("%d(을)를 가진 노드는 없습니다.\n", X);
    return;
}

void display(List list) {
    PtrToNode current = list->next;

    while (current != NULL) {
        printf("%d  ", current->data);
        current = current->next;
    }
    printf("\n");
    return;
}

Position find(Element X, List list) {
    PtrToNode current = list;

    while (current != NULL) {
        if (current->data == X) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

Position findPrevious(Element X, List list) {
    PtrToNode current = list;

    while (current->next != NULL) {
        if (current->next->data == X) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}
