#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include <glob.h>
#include <signal.h>
#include <semaphore.h>





//redirection.c
void redi(int in, int out,int append,char input[],char output[]);
void redOut(int out,char output[]);
void redIn(int in,char input[]);
void redAppend(int append, char output[]);

//exec.c
void chooseExec(char*** Commands,int NumberOfCommands,int inPos, int outPos, int appendPos,char Input[],char Output[],int CountOfPipes);
void exec1(char*** Commands,int inPos, int outPos, int appendPos,char Input[],char Output[]);
void execpipes(char*** Commands,int NumberOfCommands, int inPos, int outPos, int appendPos,char Input[],char Output[]); 

//alias.c
#define MAX_ALIAS_COUNT 50
#define MAX_ALIAS_NAME_LENGTH 100
#define MAX_ALIAS_COMMAND_LENGTH 100


typedef struct Alias {
    char* name;
    char** command;
    int num_in_com;
} Alias;

typedef struct AliasList
{
    Alias* AList[MAX_ALIAS_COUNT];
    int num_of_al;
}AliasList;

void add_alias(AliasList* list1,char* command,char* name);
Alias* create_alias_command(char*** Commands,int* Counts);
void delete_alias(AliasList* l1,char* name);
void free_alias(Alias* a1);
int insert_alias(AliasList* l1,Alias* a1);
void print_Alist(AliasList* l1);
void free_alias_in_list(AliasList* l1);
char** return_command(AliasList* l1,char* name);
int existion_of_alias(AliasList* l1,char* name);
void remove_char(char *str, char c);

//history.c
#define MAX_HISTOR_COUNT 20

typedef struct Histor{
    char** order;
    int length;
    int number;
}Histor;

typedef struct HistorList{
    Histor* HList[MAX_HISTOR_COUNT];
    int num_of_al;
}HistorList;

Histor* create_histor_command(char** av,int NumOfToken);
void free_histor(Histor* b1);
void insert_histor(HistorList* h1,char** av,int NumOfToken);
void print_history(HistorList* h1);
void free_histor_list(HistorList* h1);
int get_lenght(HistorList* h1,int hisnum);
char** get_comm(HistorList* h1,int hisnum);

//wildcards.c
char** wildcard(char** Commands,int* arg);