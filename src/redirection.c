#include "def.h"


void redi(int in, int out,int append,char input[],char output[])
{   
    if(in)
    {
        int fd0;
        if((fd0 = open(input,O_RDONLY)) < 0)
        {
            perror("Couldn't open input file");
            exit(1);
        }
        if((dup2(fd0,0)==-1))
        {
            perror("dup2 fd0");
            exit(1);
        }
        close(fd0);
    }
    if(out) 
    {
        int fd1;
        if((fd1 = open(output, O_WRONLY|O_CREAT|O_TRUNC, 0666)) < 0)
        {
            perror("Couldn't open output file");
            exit(EXIT_FAILURE);
        }
        if((dup2(fd1,1)==-1))
        {
            perror("dup2 fd1");
            exit(EXIT_FAILURE);
        }
        close(fd1);
    }
    if(append)
    {
        int fd1;
        if((fd1 = open(output, O_WRONLY | O_CREAT|O_APPEND, 0666)) < 0)
        {
            perror("Couldn't open output file");
            exit(EXIT_FAILURE);
        }
        if((dup2(fd1,1)==-1))
        {
            perror("dup2 fd1");
            exit(EXIT_FAILURE);
        }
        close(fd1);
    }
    
}

void redIn(int in,char input[])
{
    if(in)
    {
        int fd0;
        if((fd0 = open(input,O_RDONLY)) < 0)
        {
            perror("Couldn't open input file");
            exit(1);
        }
        if((dup2(fd0,0)==-1))
        {
            perror("dup2 fd0");
            exit(1);
        }
        close(fd0);
    }
}

void redOut(int out,char output[])
{
   if(out) 
    {
        int fd1;
        if((fd1 = open(output, O_WRONLY|O_CREAT|O_TRUNC, 0666)) < 0)
        {
            perror("Couldn't open output file");
            exit(EXIT_FAILURE);
        }
        if((dup2(fd1,1)==-1))
        {
            perror("dup2 fd1");
            exit(EXIT_FAILURE);
        }
        close(fd1);
    }
}

void redAppend(int append, char output[])
{
    if(append)
    {
        int fd1;
        if((fd1 = open(output, O_WRONLY | O_CREAT|O_APPEND, 0666)) < 0)
        {
            perror("Couldn't open output file");
            exit(EXIT_FAILURE);
        }
        if((dup2(fd1,1)==-1))
        {
            perror("dup2 fd1");
            exit(EXIT_FAILURE);
        }
        close(fd1);
    }
}