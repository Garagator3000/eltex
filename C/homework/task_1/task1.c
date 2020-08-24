/*
    Если в строке встречаются подряд два числа, разделенные запятыми – n1,n2, 
    то последующий фрагмент из n2 символов повторяется n1 раз. 
    Если встречается одно число, то n1 раз повторяется символ, 
    например, (aaa4,3abcdef) преобразуется в (aaaabcabcabcabcdef).
*/

/*
    Предполагается, что входная строка, будет корректна и не будет сюрпризов, вроде переполнения int
    Если будут встречены другие числа, то они будут считаться как простые символы, часть строки
    Алгоритм на два числа, сработает, только если они разделены запятыми
*/

#include "stdio.h"
#include "malloc.h"

int IsDigit(char ch)
{
    if(ch >= '0' && ch <='9')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int *SearchNumber(char string[], int size)
{
    int n[4] = {0, 0, 0, 0}; //Первое и второе число, а так же границы вырезания;
    int *ptr = n;
    int k = 0, i = 0; //Итераторы;
    int dif = 0; //Для подсчета индкса первого нахождения числа;
    int check_point = 0; //Место между числами, запятая;
    for(k = 0; k<size; k++) //идем по массиву пока не встретим запятую;
    {
        if(IsDigit(string[k])) //Если встреченный символ цифра, то формируем число n1;
        {
            if(n[0] == 0) //Запоминаем первый индекс числа
            {
                n[2] = k;
            }
            n[0] = n[0]*10 + (int)string[k] - '0';
            dif++;
        }
        if(string[k] == ',')
        {
            check_point = ++k; //чтобы след. цикл не остановился на первой итерации
            break;
        }
        if(string[k] == '\0')
        {
            n[3] = n[2] + dif;
            return ptr;
        }
    }
    for(i = check_point; i < size; i++) //Идем по массиву, зная, что первые символы цифры, заканчиваем при встрече первого не числа
    {
        if(IsDigit(string[i]))
        {
            n[1] = n[1]*10 + (int)string[i] - '0';
        }
        else
        {
            break;
        }
    }
    n[3] = --i; //потому что делал инкремент check_point;
    return ptr;
}

char *SetInsertString(int n2, char string[], int end_cut) //Получить подстроку, которую нужно копировать
{
    char *insert = NULL;
    insert = (char*)malloc(n2*sizeof(char));
    for(int i = 0; i < n2; i++)
    {
        insert[i] = string[i + end_cut + 1]; 
    }
    return insert;
}

int main()
{    
    char string[] = "abc3,4defg"; //Входная строка 
    int n1 = 0, n2 = 0, begin_cut = 0, end_cut = 0;
    int *buffer = NULL;
    char *insert = NULL; //Строка для вставки(дублирования)
    int size_string = sizeof(string)/sizeof(char); 
    char *final_string = NULL;
    int size_final_string = 0;

    buffer = SearchNumber(string, size_string);

    n1 = buffer[0];         //смотри условие
    n2 = buffer[1];         //смотри условие
    begin_cut = buffer[2];  //индекс первой цифры
    end_cut = buffer[3];    //индекс последней цифры

    if(n2 != 0) //Если два числа
    {
        insert = SetInsertString(n2, string, end_cut);
        //"end_cut - begin_cut", это то, сколько индексов занимает "n1,n2";
        //"n1-1", из примера в условии;
        size_final_string = n2 * (n1-1) + size_string - (end_cut - begin_cut);
        final_string = (char*)malloc(sizeof(char)*size_final_string);
        for(int i = 0; i < size_final_string; i++) //Формируем выходную строку
        {
            for(int k = 0; k < begin_cut; k++, i++) //Вставляем то, что было до цифр
            {
                final_string[i] = string[k];
            }
            for(int k = 0; k < (n1 - 1); k++) //Вставляем то, что нужно продублировать
            {
                for(int j = 0; j < n2; j++, i++)
                {
                    final_string[i] = insert[j];
                }
            }
            for(int k = ++end_cut; k < size_string; k++, i++) //Вставляем остаток;
            {
                final_string[i] = string[k];
            }
        }
        printf("%s\n", final_string);
    }

    if((n2 == 0) && (n1 != 0)) //Если одно число
    {
        size_final_string = size_string + n1 - 1;
        final_string = (char*)malloc(size_final_string * sizeof(char));
        for(int i = 0; i < size_final_string; i++)
        {
            for(int k = 0; k < begin_cut; k++, i++) //Вставляем то, что было до цифр
            {
                final_string[i] = string[k];
            }
            for(int k = 0; k < (n1); k++, i++) //Вставляем то, что нужно продублировать
            {
                final_string[i] = string[end_cut];;   
            }
            for(int k = ++end_cut; k < size_string; k++, i++) //Вставляем остаток;
            {
                final_string[i] = string[k];
            }
            break;
        }
        printf("%s\n", final_string);
    }
    
    if((n1 == 0) && (n2 == 0)) //Если чисел нет
    {
        size_final_string = size_string;
        final_string = (char*)malloc(sizeof(char)*size_final_string);
        for(int i = 0; i < size_string; i++)
        {
            final_string[i] = string[i];
        }
        printf("%s\n", final_string);
    }

    free(final_string);

    return 0;
}