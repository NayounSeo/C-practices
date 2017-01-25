#include <stdio.h>
#include <stdlib.h>
#define MAX_ENROLL 3

typedef struct {
    char* name;
    char* major;
    int studentID;
} studentT;

typedef struct {
    studentT* students[MAX_ENROLL];
    int numEnrolled;
} courseT;

/* 파일에서 교과 수강생 정보 읽기 */
void GetClassData(courseT* course);
/* 파일에 교과 수강생 정보 쓰기 */
void OutClassData(courseT* course);
void FreeMemories(courseT* course);

int main() {
    courseT course;
    int i;

    for (i = 0; i < MAX_ENROLL; i++) {
        course.students[i] = (studentT*) malloc(sizeof(studentT));
        //구조체변수.구조체변수의 멤버
        //구조체변수.구조체포인터형->구조체포인터형의 멤버. 포인터니까 ->
        course.students[i]->name = (char*) malloc(sizeof(char) * 20);
        course.students[i]->major = (char*) malloc(sizeof(char) * 20);
    }

    GetClassData(&course); //파일 읽고 변수에 쓰기

    OutClassData(&course); //변수를 파일에 쓰기
    
    FreeMemories(&course); //메모리 해제 및 파일 닫기.

    return 0;
}

void GetClassData(courseT* course) {
    FILE* fr;
    char enroll[10];
    char cant_enroll[10];
    int i = 0;

    fr = fopen("input.txt", "rt");
    if (fr == NULL) {
        printf("Cannot find file.");
    }

    while (!feof(fr)) {
        fscanf(fr, "%s", enroll);
        if (i >= MAX_ENROLL) {
            fscanf(fr, "%s\t %d\t %s\t", cant_enroll);
            printf("%s can't enroll this class.\n", cant_enroll);
        } else if (strcmp(enroll, "enroll") == 0) {
            //***중요
            fscanf(fr, "%s %d %s\n", course->students[i]->name, &(
                course->students[i]->studentID), course->students[i]->major);
            i++;
        }
    }

    fclose(fr);
}

void OutClassData(courseT* course) {
    FILE* fw;
    int num_of_students;
    int i;
    fw = fopen("output.txt", "wt");

    num_of_students = sizeof(course->students) / sizeof(course->students[0]);
    fprintf(fw, "Enrolled number : %d\n\n", num_of_students);

    for (i = 0; i < num_of_students; i++) {
        fprintf(fw, "%s\t%d\t%s\t\n", course->students[i]->name, \
                course->students[i]->studentID, course->students[i]->major);
    }

    fclose(fw);
}

void FreeMemories(courseT* course) {
    int num_of_students;
    int i;

    num_of_students = sizeof(course->students) / sizeof(course->students[0]);
    printf("%d\n", num_of_students);

    for (i = 0; i < num_of_students; i++) {
        free(course->students[i]->name);
        free(course->students[i]->major);
        free(course->students[i]);
    }
}