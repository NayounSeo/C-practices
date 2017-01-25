int traverseTree(Tree* node) {
    printf("value : %d\n", node->value);
    if (node->left == NULL && node->right != NULL) {  // 여기서 l, r 검사하든지 해야겠다.
        puts("1");
        return 1;
    } else if (node->right == NULL && node->left != NULL) {
        puts("2");
        return 2;
    }

    node->height = getHeight(node->left) - getHeight(node->right);
    printf("height : %d\n", node->height);
    Tree* node2start = NULL;
    puts("AA");
    if (node->height == 2) { //왼쪽 트리!
        node2start = node->left;
    } else if (node->height == -2) { //오른쪽 트리!!
        node2start = node->right;
    } else { //제일 위에서 없다면 아래에서도 없겠지?!
        puts("0");
        return 0;
    }
    puts("BB");

    return traverseTree(node2start);  // 재귀적으로 끝부분까지 타고 내려갈 수 있어야 해ㅜㅠ
}



void traverseTree(Tree* node) {
    if (node == NULL) { //생각해보니 이미 삽입이 일어나서 이럴리 없어..
        return;
    }

    node->height = getHeight(node->left) - getHeight(node->right);
    printf("%d\n", node->value);
    puts("AA");
    //분기 자체가 잘못됐어 하나 더 아래로 내려가든가.

    if (node->height == 2) { //왼쪽 트리!!


        //그냥 이렇게 되면 안되는데 l일때 r일때 나눠 줘야
        Tree* temp1 = node->left;
        Tree* temp2 = temp1->left;
        // gdb로 디버깅 결과 위의 예제에서 7삽입했을 때 temp2가 NULL이라ㅜㅠ
        if (temp2->left != NULL) { // LL
            temp2->right = temp1;
            temp1->left = NULL;
            node->left = temp2;
        } else { // if (temp2->right != NULL) (since l - r = 2) LR
            Tree* temp3 = temp2->right;
            temp3->left = temp2;
            temp2->right = NULL;
            temp3->right = temp1;
            temp1->left = NULL;
            node->left = temp3;
        }
    } else if (node->height == -2) { //오른쪽 트리!! 


        Tree* temp1 = node->right;
        Tree* temp2 = temp1->right;
        if (temp2->right != NULL) { //RR
            temp2->left = temp1;
            temp1->right = NULL;
            node->right = temp2;
        } else { // if (temp2->left != NULL) (since l - r = -2) RL
            Tree* temp3 = temp2->left;
            temp3->left = temp1;
            temp1->right = NULL;
            temp3->right = temp2;
            temp2->left = NULL;
            node->right = temp3;
        }
    } else {
        traverseTree(node->left);
        traverseTree(node->right);
    }
    puts("BB");

}



void traverseTree(Tree* node, Tree* parent, int direction) {
    node->height = getHeight(node->left) - getHeight(node->right);
    Tree* node2start = NULL;

    if (abs(node->height) >= 2) {
        if (node->left == NULL) {  // RR, RL
            Tree* temp1 = node->right;
            if (temp1->left == NULL) { //RR
                temp1->left = node;
                node->right = NULL;
                where_to_insert(parent, temp1, direction);
            } else { //RL
                Tree* temp2 = temp1->left;
                temp2->right = temp1;
                temp1->left = NULL;
                temp2->left = node;
                node->right = NULL;
                where_to_insert(parent, temp2, direction);
            }

        } else if (node->right == NULL) {  //LL, LR
            Tree* temp1 = node->left;
            if (temp1->right == NULL) { //LL
                temp1->right = node;
                node->left = NULL;
                where_to_insert(parent, temp1, direction);
            } else { //LR
                Tree* temp2 = temp1->right;
                temp2->left = temp1;
                temp1->right = NULL;
                temp2->right = node;
                node->left = NULL;
                where_to_insert(parent, temp2, direction);
            }

        } else {
            if (node->height > 0) {
                traverseTree(node->left, node, 1);
            } else {
                traverseTree(node->right, node, -1);
            }
        }
    }
    puts("0");
    return;

}

void where_to_insert(Tree* parent, Tree* to_insert, int direction) {
    if (direction > 0) {
        parent->right = to_insert;
    } else if (direction < 0) {
        parent->left = to_insert;
    } else { // == 0
        return;
    }
}