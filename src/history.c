#include "def.h"


Histor* create_histor_command(char** av,int NumOfToken)
{
    static int num = 1; 
    Histor* b1 = malloc(sizeof(Histor));
    b1->length = NumOfToken;
    b1->order = malloc(sizeof(char*)*(NumOfToken));
    b1->number = num;
    num++;
    for(int i=0; i<NumOfToken-1; i++)
    {
        b1->order[i] = malloc(sizeof(char)* strlen(av[i]));
        strcpy(b1->order[i],av[i]);
    }
    b1->order[NumOfToken-1] = NULL;
    return b1;
}

void free_histor(Histor* b1)
{
    for(int i=0; i < b1->length; i++)
    {
        free(b1->order[i]);
    }
    free(b1);
}

void insert_histor(HistorList* h1,char** av,int NumOfToken)
{
    Histor* b1 = create_histor_command(av,NumOfToken);
    if(h1->num_of_al<MAX_HISTOR_COUNT)
    {
        h1->HList[h1->num_of_al] = b1;
        h1->num_of_al++;
    }
    else if(h1->num_of_al == MAX_HISTOR_COUNT)
    {
        free(h1->HList[0]);
        for(int i =1;i<h1->num_of_al;i++)
        {
            Histor* temp;
            temp = h1->HList[i];
            h1->HList[i-1] = temp;
        }
        h1->HList[MAX_HISTOR_COUNT-1] = b1;
    }
}

void print_history(HistorList* h1)
{
    for(int i =0; i < h1->num_of_al; i++)
    {
        printf("%d \t",h1->HList[i]->number);
        for(int k = 0; k < h1->HList[i]->length-1;k++)
        {
            printf("%s \t",h1->HList[i]->order[k]);
        }
        printf("\n");
    }
    printf("\n");
}

void free_histor_list(HistorList* h1)
{
    for(int i=0; i < h1->num_of_al; i++)
    {
        free_histor(h1->HList[i]);
    }
}

int get_lenght(HistorList* h1,int hisnum)
{
    for(int i=0; i < h1->num_of_al; i++)
    {
        if (h1->HList[i]->number == hisnum)
        {
            return h1->HList[i]->length;
        }
        
    }
    return 0;
}

char** get_comm(HistorList* h1,int hisnum)
{
    for(int i=0; i < h1->num_of_al; i++)
    {
        if (h1->HList[i]->number == hisnum)
        {
            return h1->HList[i]->order;
        }
        
    }
    return NULL;
}




