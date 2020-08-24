/*
    Ввод записи с клавиатуры, загрузка и сохранение таблицы в текстовом файле,
    просмотр таблицы, сортировка таблицы по указанному полю, поиск в таблице по полю,
    удаление записи, редактирование записи; 

    Фамилия, кол-во оценок, оценки, средний балл.
*/

#define CLEAR system("clear") 
#define AWAIT getchar();getchar();

#include "list.h"

void showMenu();

int ID = 0;

int main()
{
    int key;
    List *list;
    list = initList();

    int id;
    float aver;
    char name[64];

    while(1)
    {
        showMenu();

        scanf("%d", &key);

        switch (key)
        {
        case 1:
            CLEAR;
            pushBack(list, createStudent(ID));
            ID++;
            break;
        case 2:
            CLEAR;
            printf("\nEnter ID\n");
            scanf("%d", &key);
            popId(list, key);
            break;
        case 3:
            CLEAR;
            showList(list);
            AWAIT;
            break;
        case 4:
            CLEAR;
            printf("1.ID\n2.Average mark\n3.Name\n");
            scanf("%d", &key);
            switch (key)
            {
            case 1:
                CLEAR;
                printf("Enter ID\n");
                scanf("%d", &id);
                showNode(searchId(list, id));
                break;
            case 2:
                CLEAR;
                printf("Enter Average mark\n");
                scanf("%f", &aver);
                showNode(searchAverage(list, aver));
                break;
            case 3:
                CLEAR;
                printf("Enter name\n");
                scanf("%s", name);
                showNode(searchName(list, name));
                break;
            default:
                printf("invalid\n");
                break;
            }
            AWAIT;
            break;
        case 5:
            CLEAR;
            printf("1.ID\n2.Average mark\n3.Name\n");
            scanf("%d", &key);
            switch (key)
            {
            case 1:
                CLEAR;
                sortId(list);
                break;
            case 2:
                CLEAR;
                sortAverage(list);
                break;
            case 3:
                CLEAR;
                sortName(list);
                break;
            default:
                printf("invalid\n");
                break;
            }
            break;
        case 6:
            saveToFile(list);
            break;
        case 7:
            CLEAR;
            printf("1.Name\n2.Marks\n0.Back\n");
            scanf("%d", &key);
            switch (key)
            {
            case 1:
                CLEAR;
                printf("Enter ID\n");
                scanf("%d", &id);
                editName(list, id);
                break;
            case 2:
                CLEAR;
                printf("Enter ID\n");
                scanf("%d", &id);
                editMarks(list, id);
                break;
            case 0:
                break;
            default:
                printf("invalid\n");
                break;
            }
            AWAIT;
            break;
        case 0:
            exit(0);
        }
    }

    return 0;
}

void showMenu()
{
    CLEAR;
    printf("1.Add student\n");
    printf("2.Delete student\n");
    printf("3.Show List\n");
    printf("4.Search\n");
    printf("5.Sort\n");
    printf("6.Save\n");
    printf("7.Edit note\n");
    printf("0.Exit\n");
}