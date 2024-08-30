#include "def.h"

Alias* create_alias_command(char*** Commands,int* Counts)
{
    Alias* a1 = malloc(sizeof(Alias));
    a1->name = malloc(sizeof(char)* strlen((Commands[0][0])));
    strcpy(a1->name,Commands[0][0]);
    //printf("Name %s \n",a1->name);
    a1->command = malloc(sizeof(char*)*(Counts[0]-1));
    a1->num_in_com = Counts[0]-1;
    //printf("Number:%d\t",a1->num_in_com);
    for(int i=0; i <Counts[0]-1; i++)
    {
        a1->command[i] = malloc(sizeof(char)*strlen(Commands[0][i+1]));
        strcpy(a1->command[i],Commands[0][i+1]);
        //printf("Command%d: %s \t",i,a1->command[i]);

    }
    //a1->command[Counts[0]-1] = NULL;
    //printf("Command%d: %s \t",Counts[0]-1,a1->command[Counts[0]-1]);
    //printf("alias created\n");
    return a1;
}

int insert_alias(AliasList* l1,Alias* a1)
{
    for(int i=0; i< l1->num_of_al; i++)//checking if this alias'name already exist
    {
        if(strcmp(l1->AList[i]->name,a1->name)==0)
        {
            return(1);
        }
    }
    if(l1->num_of_al < MAX_ALIAS_COUNT)
    {
        l1->AList[l1->num_of_al] = a1;
        l1->num_of_al++;
        //printf("alias inserted");
        return(0);
    }
    else
    {
        return(1);
    }
}

void delete_alias(AliasList* l1,char* name)
{
    int pos;
    for(int i=0; i< l1->num_of_al;i++)
    {
        if(strcmp(l1->AList[i]->name,name)==0)
        {
            pos = i;
        }
    }
    if(pos < l1->num_of_al-1)
    {
        Alias* temp = l1->AList[l1->num_of_al-1];
        l1->AList[l1->num_of_al-1] =NULL;
        free_alias(l1->AList[pos]);
        l1->AList[pos] = temp;
        l1->num_of_al--;
    }
    else
    {
        free_alias(l1->AList[l1->num_of_al-1]);
        l1->num_of_al--;
    }
}

void print_Alist(AliasList* l1)
{
    for(int i=0; i<l1->num_of_al; i++)
    {
        printf(" \nAlias: %d \n",i);
        printf("Name: %s \n",l1->AList[i]->name);
        printf("Command:");
        for(int k = 0; k < l1->AList[i]->num_in_com; k++)
        {
            printf("<%s>\t",l1->AList[i]->command[k]);
        }

    }
    printf("\n");
}

void free_alias_in_list(AliasList* l1)
{
    for(int i=0; i<l1->num_of_al;i++)
    {
        free_alias(l1->AList[i]);
    }
}

void free_alias(Alias* a1)
{
    free(a1->name);
    for(int i=0; i < a1->num_in_com; i++)
    {
        free(a1->command[i]);
    }
    free(a1->command);
    free(a1);
    //printf("Alias free\t");
}

char** return_command(AliasList* l1,char* name)
{
    for(int i=0; i<l1->num_of_al; i++)
    {
        if(strcmp(l1->AList[i]->name,name)==0)
        {
           
            return l1->AList[i]->command;

        }
    }
    return NULL;
}

int existion_of_alias(AliasList* l1,char* name)
{
    for(int i=0; i<l1->num_of_al; i++)
    {
        if(strcmp(l1->AList[i]->name,name)==0)
        {
            //printf("NumInCOm:%d",l1->AList[i]->num_in_com);
            return (l1->AList[i]->num_in_com);

        }
    }
    return(0);
}



void remove_char(char *str, char c) {
    int i, j;
    for (i = 0, j = 0; str[i] != '\0'; i++) {
        if (str[i] != c) {
            str[j] = str[i];
            j++;
        }
    }
    str[j] = '\0'; // Add the null terminator at the end of the new string
}



