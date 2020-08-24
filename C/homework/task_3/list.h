#ifndef _LIST_H

#include "student.h"
#include <malloc.h>
#include <stdlib.h>

typedef struct Node
{
    Student *student;
    struct Node *next;
    struct Node *prev;
};

typedef struct Node Node;

typedef struct List
{
    size_t size;
    Node *head;
    Node *tail;
};

typedef struct List List;

List *initList();                               //Инициализация списка
void deleteList(List **list);                   //Удаление списка
void pushFront(List *list, Student *student);   //Добавить в начало
Student *popFront(List *list);                  //Удалить первый
void pushBack(List *list, Student *student);    //Добавить в конец
Student *popBack(List *list);                   //Удалить последний
Node *searchId(List *list, int id);             //Поиск по id
Node *searchName(List *list, char *name);       //Посик по имени
Node *searchAverage(List *list, float average); //Поиск по среднему баллу
void showList(List *list);                      //Показать список
void showNode(Node *node);                      //Показать студента
Student *popId(List *list, int id);             //Удалить по id
void sortId(List *list);                        //Сортировать по id
void sortAverage(List *list);                   //Сортировать по среднему баллу
void sortName(List *list);                      //Сортировать по алфавиту
void swap(Node *node1, Node *node2, List *list);//Смена узлов местами
void editName(List *list, int id);              //Редактирование записи
void editMarks(List *list, int id);
void saveToFile(List *list);                 

////////////////////////////////////////////////////////////////////////////////////

List *initList()
{
    List *tmp = (List*)malloc(sizeof(List));
    tmp->size = 0;
    tmp->head = NULL;
    tmp->tail = NULL;
}

void deleteList(List **list)
{
    Node *tmp = (*list)->head;
    Node *next = NULL;
    while (tmp)
    {
        next = tmp->next; 
        free(tmp);
        tmp = next;
    }
    free(*list);
    (*list) = NULL;
}

void pushFront(List *list, Student *student)
{
    Node *tmp = (Node*)malloc(sizeof(Node));
    if(tmp == NULL)
    {
        exit(1);
    }
    tmp->student = student;
    tmp->next = list->head;
    tmp->prev = NULL;
    if(list->head)
    {
        list->head->prev = tmp;
    }
    list->head = tmp;
    if(list->tail == NULL)
    {
        list->tail = tmp;
    }
    list->size++;
}

Student *popFront(List *list)
{
    Node *prev;
    Student *tmp;
    if(list->head == NULL)
    {
        exit(2);
    }
    prev = list->head;
    list->head = list->head->next;
    if(list->head)
    {
        list->head->prev = NULL;
    }
    if(prev == list->tail)
    {
        list->tail = NULL;
    }
    tmp = prev->student;
    free(prev);
    list->size--;
    return tmp;
}

void pushBack(List *list, Student *student)
{
    Node *tmp = (Node*)malloc(sizeof(Node));
    if(tmp == NULL)
    {
        exit(3);
    }
    tmp->student = student;
    tmp->next = NULL;
    tmp->prev = list->tail;
    if(list->tail)
    {
        list->tail->next = tmp;
    }
    list->tail = tmp;
    if(list->head == NULL)
    {
        list->head = tmp;
    }
    list->size++;
}

Student *popBack(List *list)
{
    Node *next;
    Student *tmp;
    if(list->tail == NULL)
    {
        exit(4);
    }
    next = list->tail;
    list->tail = list->tail->prev;
    if(list->tail)
    {
        list->tail->next = NULL;
    }
    if(next == list->head)
    {
        list->head = NULL;
    }
    tmp = next->student;
    free(next);
    list->size--;
    return tmp;
}

Node *searchId(List *list, int id)
{
    Node *tmp;
    tmp = list->head;
    while (tmp != NULL)
    {
        if(tmp->student->id == id)
        {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}

Node *searchName(List *list, char *name)
{
    Node *tmp;
    tmp = list->head;
    while (tmp != NULL)
    {
        if(*tmp->student->name == *name)
        {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}

Node *searchAverage(List *list, float average)
{
    Node *tmp;
    tmp = list->head;
    while (tmp != NULL)
    {
        if(tmp->student->averageMark == average)
        {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}

void showList(List *list)
{
    Node *tmp;
    if(list->size == 0)
    {
        printf("List empty\n");
        return;
    }
    tmp = list->head;
    for(int i = 0; i < list->size; i++)
    {
        showNode(tmp);
        tmp = tmp->next; 
    } 
}

void showNode(Node *node)
{
    if(node == NULL)
    {   
        printf("not exist\n");
        return;
    }
    printf("\nId: %d\n", node->student->id);
    printf("Name: %s\n", node->student->name);
    printf("Marks: ");
    for(int i = 0; i < node->student->numbOfMarks; i++)
    {
        printf(" %d ", node->student->marks[i]);
    }
    printf("\n");
    printf("Average mark %.2f\n", node->student->averageMark);
}

Student *popId(List *list, int id)
{
    Node *tmp = searchId(list, id);
    Student *student;
    if(tmp == NULL)
    {
        printf("not exist\n");
        student = tmp;
    }
    if(tmp->next == NULL)
    {
        student = popBack(list);
        student = tmp->student;
    }else
    if(tmp->prev == NULL)
    {
        student = popFront(list);
        student = tmp->student;
    }else
    {
        tmp->next->prev = tmp->prev;
        tmp->prev->next = tmp->next;

        student = tmp->student;
        free(tmp);
        list->size--;
    }
    return student;
}

void sortId(List *list)
{
    Node *iter;
    int fl = 1;
    while (fl)
    {
        iter = list->head;
        fl = 0;
        while (iter->next != NULL)
        {
            if(iter->student->id > iter->next->student->id)
            {
                swap(iter, iter->next, list);
                fl = 1;
                if(iter->next == NULL)
                {
                    break;
                }
            }
            iter = iter->next;
        }
    }
}

void sortAverage(List *list)
{
    Node *iter;
    int fl = 1;
    while (fl)
    {
        iter = list->head;
        fl = 0;
        while (iter->next != NULL)
        {
            if(iter->student->averageMark < iter->next->student->averageMark)
            {
                swap(iter, iter->next, list);
                fl = 1;
                if(iter->next == NULL)
                {
                    break;
                }
            }
            iter = iter->next;
        }
    }
}

void sortName(List *list)
{
    Node *iter;
    int fl = 1;
    while (fl)
    {
        iter = list->head;
        fl = 0;
        while (iter->next != NULL)
        {
            if(strcmp(iter->student->name, iter->next->student->name) > 0)
            {
                swap(iter, iter->next, list);
                fl = 1;
                if(iter->next == NULL)
                {
                    break;
                }
            }
            iter = iter->next;
        }
    }
}

void swap(Node *node1, Node *node2, List *list)
{
    if(node1->prev != NULL && node2->next != NULL)
    {
        node1->next = node2->next;
        node1->prev->next = node2;
        node2->prev = node1->prev;
        node1->prev = node2;
        node2->next->prev = node1;
        node2->next = node1;
    }
    if(node1->prev == NULL && node2->next != NULL)
    {
        node1->next = node2->next;
        node2->prev = NULL;
        node1->prev = node2;
        node2->next->prev = node1;
        node2->next = node1;
        list->head = node2;
    }
    if(node1->prev != NULL && node2->next == NULL)
    {
        node1->next = NULL;
        node1->prev->next = node2;
        node2->prev = node1->prev;
        node1->prev = node2;
        node2->next = node1;
        list->tail = node1;
    }
    if(node1->prev == NULL && node2->next == NULL)
    {
        node1->next = NULL;
        node2->prev = NULL;
        node1->prev = node2;
        node2->next = node1;
        list->head = node2;
        list->tail = node1;
    }
}

void editName(List *list, int id)
{
    Node *tmp = searchId(list, id);
    if(tmp == NULL)
    {
        printf("not exist\n");
        return;
    }
    showNode(tmp);
    printf("Enter new name\n");
    scanf("%s", tmp->student->name);
}

void editMarks(List *list, int id)
{
    Node *tmp = searchId(list, id);
    if(tmp == NULL)
    {
        printf("not exist\n");
        return;
    }
    int sum = 0;
    showNode(tmp);
    printf("Enter new quantity of marks\n");
    scanf("%d", &tmp->student->numbOfMarks);
    tmp->student->marks = (int*)realloc(tmp->student->marks, sizeof(int)*tmp->student->numbOfMarks);
    printf("Enter marks(use space)\n");
    for(int i = 0; i < tmp->student->numbOfMarks; i++)
    {
        scanf("%d", tmp->student->marks + i);
        sum += tmp->student->marks[i];
    }
    tmp->student->averageMark = (float)sum / tmp->student->numbOfMarks;
}

void saveToFile(List *list)
{
    char fileName[] = "List_of_students";
    FILE *file = fopen(fileName, "w");

    if(file == NULL)
    {
        printf("file error\n");
        getchar();
        return;
    }

    Node *node = list->head;
    while (node != NULL)
    {
        fprintf(file, "Id: %d\n", node->student->id);
        fprintf(file, "Name: %s\n", node->student->name);
        fprintf(file ,"Marks: ");
        for(int i = 0; i < node->student->numbOfMarks; i++)
        {
            fprintf(file, " %d ", node->student->marks[i]);
        }
        fprintf(file, "\n");
        fprintf(file, "Average mark %.2f\n", node->student->averageMark);
        fprintf(file, "\n");
        node = node->next;
    }
    fclose(file);
}

#endif