#include <stdio.h>
#include <stdlib.h>

struct student {
    char* name;
    char* major;
    int studentID;
};

/* 재귀를 이용해 1부터 n까지 곱하는 함수 */
int power(int n, int p);

int main() {
    int number = 0, p = 0, result = 1;
    struct student* s;
    int num_of_student = 0;
    
    FILE* fr;
    FILE* fw;
    int i = 0;

    /*
    printf("Enter number : ");
    scanf("%d", &number);
    printf("Enter power : ");
    scanf("%d", &p);

    for (i = 0; i < p; i++) {
        result *= number;
    }
    printf("루프  %d^%d = %d\n", number, p, result);
    result = power(number, p);
    printf("재귀함수  %d^%d = %d\n", number, p, result);
    */

    fr = fopen("input_practice02_3.txt", "rt");
    fw = fopen("output_practice02_3.txt", "wt");

    if (fr == NULL || fw == NULL ) {
        printf("파일을 찾을 수 없습니다.");
    }
    
    fscanf(fr, "%d\n\n", &num_of_student);

    //☆★☆
    s = (struct student*) malloc (sizeof(struct student) * num_of_student);

    for (i = 0; i < num_of_student; i++) { 
        s[i].name = (char*) malloc(sizeof(char) * 10);
        s[i].studentID = 0;
        s[i].major = (char*) malloc(sizeof(char) * 7);
    }

    i = 0;

    while (!feof(fr)) {
        fscanf(fr, "%s\n", s[i].name);
        fscanf(fr, "%d\n", &s[i].studentID);
        //fgets(s.major, sizeof(char) * 7, fr);
        fscanf(fr, "%s\n\n", s[i].major);
        i++;
        if (i == num_of_student) {
            break;
        }
    }
    fclose(fr);

    for (i = 0; i < num_of_student; i++) {
        fprintf(fw, "%s %d %s \n", s[i].name, s[i].studentID, s[i].major);
    }

    fclose(fw);

    return 0;
}

int power(int n, int p) {
    if (p == 0) {
        return 1;
    }
    if (p == 1) {
        return n * 1;
    }

    n *= power(n, p - 1);
}