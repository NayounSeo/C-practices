#include <stdio.h>
#include <stdlib.h>

typedef struct BT {
    int value;
    struct BT* left;
    struct BT* right;
} BT;

struct BT* bt = NULL;

void insertTreeNode(struct BT* bt, int value);
void findTreeNode(struct BT* bt, int value);
void printPre(struct BT* bt);
void printIn(struct BT* bt);
void printPost(struct BT* bt);

int main(void) {
    char command[5];
    int data;
    char p_mth[5];

    while (1) {
        printf("new loop : ");
        scanf("%s", command);

        if (!strcmp(command, "i")) {
            scanf("%d", &data);
            insertTreeNode(bt, data);
        } else if (!strcmp(command, "p")){
            scanf("%s", p_mth);
            if (!strcmp(p_mth, "in")) {
                printIn(bt);
                printf("\n");
            } else if (!strcmp(p_mth, "pre")) {
                printPre(bt);
                printf("\n");
            } else if (!strcmp(p_mth, "post")) {
                printPost(bt);
                printf("\n");
            }
        } else if (!strcmp(command, "f")) {
            scanf("%d", &data);
            findTreeNode(bt, data);
        } else {
            break;
        }
    }


    return 0;
}

// 변수 이름은 전역변수랑 똑같이 만들지 말자 ㅂㄷㅂㄷ..
void insertTreeNode(BT* bt1, int value) {
    if (bt1 == NULL) {
        BT* newNode = (BT*)malloc(sizeof(BT));
        newNode->value = value;
		newNode->left = NULL;
		newNode->right = NULL;
		bt = newNode;
        return;
    }
    if (value >= bt1->value) {
        if (bt1->right == NULL) {
            BT* newNode = (BT*) malloc(sizeof(BT));
            newNode->value = value;
			newNode->left = NULL;
			newNode->right = NULL;
            bt1->right = newNode;
        } else {
            insertTreeNode(bt1->right, value);
        }
    } else {
        if (bt1->left == NULL) {
            BT* newNode = (BT*) malloc(sizeof(BT));
            newNode->value = value;
			newNode->left = NULL;
			newNode->right = NULL;
            bt1->left = newNode;
        } else {
            insertTreeNode(bt1->left, value);
        }
    }
}

void findTreeNode(BT* bt, int value) {
    if (bt == NULL) { // 초기, 끝 노드
        printf("Tree or Key does not exist\n");
        return;
    }
    if (value > bt->value) {
        findTreeNode(bt->right, value);
    } else if (value < bt->value) {
        findTreeNode(bt->left, value);
    } else {
        printf("%p\t\t%d\n", bt, bt->value);
    }
}

void printPre(BT* bt) {
    if (bt != NULL) {
        printf("%d\t", bt->value);
        printPre(bt->left);
        printPre(bt->right);
    }
}

void printIn(BT* bt) {
    if (bt != NULL) {
        printIn(bt->left);
        printf("%d\t", bt->value);
        printIn(bt->right);
	}
}

void printPost(BT* bt) {
    if (bt != NULL) {
        printPost(bt->left);
        printPost(bt->right);
        printf("%d\t", bt->value);
	}
}
