#ifndef _STUDENT_H

#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Student
{
    int id;
    char name[64];
    int numbOfMarks;
    int *marks;
    float averageMark;
};

typedef struct Student Student;

Student *createStudent(int id);

/////////////////////////////////////////////////////////////////////////////

Student *createStudent(int id)
{
    Student *student = (Student*)malloc(sizeof(Student));
    int sum = 0;
    student->id = id;
    printf("Enter name\n");
    scanf("%s", student->name);
    printf("Enter quantity of marks\n");
    scanf("%d", &student->numbOfMarks);
    student->marks = (int*)malloc(sizeof(int)*student->numbOfMarks);
    printf("Enter marks(use space)\n");
    for(int i = 0; i < student->numbOfMarks; i++)
    {
        scanf("%d", student->marks + i);
        sum += student->marks[i];
    }
    student->averageMark = (float)sum / student->numbOfMarks;
    return student;
}

#endif