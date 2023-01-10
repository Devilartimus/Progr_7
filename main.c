#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void masSizePlus(int** mas, int* size, int value) //увеличение массива на единицу
{
    int* mas1 = malloc(sizeof(int)*((*size)+1));
    for (int i = 0; i < (*size); i++)
    {
        mas1[i] = *(*(mas + 0)+i);
    }
    if (*mas != NULL)
        free(*mas);
    (*size)+= 1;
    mas1[(*size)-1] = value;
    *(mas) = mas1;
}

void delSpaces(char** str) //удаление пробелов
{
    char* str1 = malloc(200);
    int index = 0;
    for (int i = 0; (*str)[i] != '\0'; i++)
    {
        if ((*str)[i] != ' ')
        {
            str1[index] = (*str)[i];
            index++;
        }
    }
    str1[index] = '\0';
    strcpy(*str, str1);
}

void findNumbers(char* str, int** mas, int* size) //заполняем массив цифрами
{
    char* str1 = malloc(100);
    int count = 0;
    delSpaces(&str);
    for (int i = 0; str[i] != '\0'; i++)
    {
        bool flag = false;
        for (int j = 43; j < 58; j++)
        {
            if (str[i] == (char)j)
            {
                str1[count] = (char)j;
                count++;
                flag = true;
                break;
            }
        }
        if ((str[i+1] == '-') || (str[i+1] == '+'))
            flag = false;
        if ((flag == true) && (str[i+1] == '\0') && (count != 0))
            flag = false;
        if ((flag == false) && (count != 0))
        {
            str1[count] = '\0';
            int value = atoi(str1);
            masSizePlus(mas, size, value);
            count = 0;
            free(str1);
            str1 = malloc(100);
        }
    }
}

void findIndication(char* str, char** str1) //поиск знаков
{
    char* str2 = malloc(100);
    int count = 0;
    delSpaces(&str);
    for (int i = 1; str[i] != '\0'; i++)
    {
        if (str[i] == '*')
        {
            str2[count] = '*';
            count++;
        }
        else if ((str[i] == '-') || (str[i] == '+'))
        {
            if (str[i-1] == '*')
                continue;
            else
            {
                str2[count] = '+';
                count++;
            }
        }
    }
    str2[count] = '\0';
    strcpy(*str1, str2);
}

void deleteIndex(int** mas, int* size, int index)
{
    int* mas1 = malloc(sizeof(int)*((*size)-1));
    for (int i = 0; i < (*size); i++)
    {
        if (i < index)
            mas1[i] = (*mas)[i];
        else if (i == index)
            continue;
        else if (i > index)
            mas1[i-1] = (*mas)[i];
    }
    if ((*mas) != NULL)
        free((*mas));
    (*mas) = mas1;
    (*size) -= 1;
}
void deleteIndexStr(char** str, int index)
{
    char* str1 = malloc(100);
    int count = 0;
    for (int i = 0; (*str)[i] != '\0'; i++)
    {
        if (i < index)
        {
            str1[i] = (*str)[i];
            count++;
        }
        else if (i == index)
            continue;
        else if (i > index)
        {
            str1[i-1] = (*str)[i];
            count++;
        }
    }
    str1[count] = '\0';
    strcpy(*str, str1);
}
void multiply(int** mas, int* size, char** str)
{
    for (int i = 0; (*str)[i] != '\0'; )
    {
        if ((*str)[i] == '*')
        {
            (*mas)[i] = (*mas)[i]*(*mas)[i+1];
            deleteIndex(mas,size,i+1);
            deleteIndexStr(str, i);
        }
        else
            i++;
    }
}

bool checkNum(char* str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        for (int j = 0; j < 48; j++)
        {
            if ((j == 42) || (j == 43) || (j == 45))
                continue;
            else if (str[i] == (char)j)
                return false;
        }
        for (int j = 58; j < 255; j++)
        {
            if (str[i] == (char)j)
                return false;
        }
    }
    return true;
}

bool checkSimb (char* str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i+1] == '\0')
        {
            if ((str[i] == '-') || (str[i] == '+') || (str[i] == '*'))
                return false;
        }
    }
    return true;
}

int main()
{
    char* str = malloc(200);
    char* str1 = malloc(200);
    printf("Enter math note: ");
    gets(str);
    int* mas = NULL;
    int size = 0, result = 0;
    if (checkNum(str) && checkSimb(str))
    {
        findNumbers(str, &mas, &size);
        for (int i = 0; i < size; i++)
        {
            printf("%d\t", mas[i]);
        }
        printf("\n");

        findIndication(str, &str1);
        puts(str1);
        multiply(&mas, &size, &str1);

        for (int i = 0; i < size; i++)
        {
            result += mas[i];
        }
        printf("\n\nRESULT = %d\n", result);
        return 0;
    }
    printf("\nNote have incorrect symbol\n");
    return 0;
}
