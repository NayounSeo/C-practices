#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b);

struct student{
    char* name;
    char* major;
    int studentID;
}; 

int main() {
    char name[30];
    int arr[6];
    char* name1[3]; // 포인터 배열
    int num_of_students;
    struct student s[3];
    int i;

    /*
    printf("Enter your name : ");
    // &name (X)  name이나  &name[0]로 수정 
    scanf("%s", name);

    printf("Your name is %s\n", name);
    */

    /*
    printf("Enter six numbers : ");
    for (i = 0; i < 6; i++) {
        scanf("%d", &arr[i]);
    }

    swap(&arr[1], &arr[4]);
    swap(&arr[2], &arr[3]);

    printf("Your numbers swapped are : ");
    for (i = 0; i < 6; i++) {
        printf("%d ", arr[i]);
    }
    */

    /*
    for (i = 0; i < 3; i++) {
        name1[i] = (char*) malloc(sizeof(char) * 10);
    }
    
    printf("Enter three names : ");

    scanf("%s", name1[0]);
    scanf("%s", name1[1]);
    scanf("%s", name1[2]);

    printf("%s \n", name1[0]);
    printf("%p \n", name1[0]);

    printf("The names you entered : ");

    for (i = 0; i < 3; i++) {
        printf("%s \n", name1[i]);
    }

    for (i = 0; i < 3; i++) {
        free(name1[i]);
    }
    */

    /*
    printf("Enter the number of students and their name, ID, and major : ");
    scanf("%d", &num_of_students);

    //중간에 선언하면 안되고 자바같은 동적 할당은 없고! 그래서!
    for (i = 0; i < num_of_students; i++) {
        s[i].name = (char*) malloc(sizeof(char) * 10);
        s[i].major = (char*) malloc(sizeof(char) * 10);
        scanf("%s %d %s", s[i].name, &s[i].studentID, s[i].major);
    }

    for (i = 0; i < num_of_students; i++) {
        printf("%s %d %s \n", s[i].name, s[i].studentID, s[i].major);
    }
    */

    return 0;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
