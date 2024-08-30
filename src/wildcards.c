#include "def.h"

char** wildcard(char** Commands,int* arg)
{
    int i =0;
    glob_t globbuf;
    int tot_arg;

    while(1)
    {
        if(strpbrk(Commands[i],"*?")!=NULL)
        {
            glob(Commands[i],0,NULL, &globbuf);
            tot_arg = (*arg) + globbuf.gl_pathc -1;
            char** new_cmd = malloc(sizeof(char*)*(tot_arg+1));
            if(new_cmd == NULL)
            {
                printf("Malloc in wild");
            }
            for(int j=0; j < i; j++)
            {
                new_cmd[j] = Commands[j];
            }
            for(size_t j=0; j < globbuf.gl_pathc; j++)
            {
                new_cmd[i+j] = strdup(globbuf.gl_pathv[j]);
            }
            for(int j = i+1; j < (*arg); j++)
            {
                new_cmd[j+globbuf.gl_pathc-1] = Commands[j];
            }
            new_cmd[tot_arg] = NULL;
            i = i + globbuf.gl_pathc -1; 
            free(Commands);
            globfree(&globbuf);
            Commands = new_cmd;
            (*arg) = tot_arg;


            
        }
        i++;
        if(Commands[i] == NULL)
            break;
    }
    return Commands;
}