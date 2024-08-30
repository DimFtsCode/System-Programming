#include "def.h"

void chooseExec(char*** Commands,int NumberOfCommands,int inPos, int outPos, int appendPos,char Input[],char Output[],int CountOfPipes)
{
    if(!CountOfPipes)
    {
        exec1(Commands,inPos,outPos,appendPos,Input,Output);
    }
    else
    {
        execpipes(Commands,NumberOfCommands,inPos,outPos,appendPos,Input,Output);
    }
}


void exec1(char*** Commands,int inPos, int outPos, int appendPos,char Input[],char Output[])
{
    int status;
    int pid;
    pid = fork();
    if(pid==0)
    {
        redi(inPos,outPos,appendPos,Input,Output);
	    if (execvp(Commands[0][0], Commands[0]) == -1) {
	        perror("execvp");
		    exit(1);
	    }
    }
    else if((pid)<0)
	{
		printf("Fork failed \n");
		exit(1);
	}
    else
    {
        waitpid(pid,&status,0);
    }
    
}

void execpipes(char*** Commands,int NumberOfCommands, int inPos, int outPos, int appendPos,char Input[],char Output[])
{
    int status;
    int pids[NumberOfCommands]; //we create as pids as the commands
	int pipes[NumberOfCommands-1][2]; // we create as pipes as the commands
	int pr;
	for (pr = 0; pr < NumberOfCommands-1; pr++) {
    	if (pipe(pipes[pr]) == -1) {
        	printf("Error with creating pipe\n");
			exit(1);
		}
	}



	for(pr = 0; pr < NumberOfCommands; pr++)
	{
		
		pids[pr] = fork();
		if(pids[pr] ==0)
		{
			if(pr == 0) // first command can has input
			{
				
				for(int t9 = 0; t9 <NumberOfCommands-1; t9++ )//closing all the read pipes
				{
					close(pipes[t9][0]);
				}
				for(int t9 = 1; t9 <NumberOfCommands-1; t9++ )//closing all the write pipes except the first pipe
				{
					close(pipes[t9][1]);
				}
				redIn(inPos,Input);
				dup2(pipes[0][1],1); // dup exec output to pipe[] write
				close(pipes[0][1]);
				if (execvp(Commands[0][0], Commands[0]) == -1) {
					perror("execvp");
					exit(1);
				}
				
			}
			else if(pr == NumberOfCommands-1) // we are in the last command
			{
				for(int t9 = 0; t9 <NumberOfCommands-2; t9++ )//closing all the read pipes except the last pipe
				{
					close(pipes[t9][0]);
				}
				
				for(int t9 = 0; t9 <NumberOfCommands-1; t9++ )//closing all the write pipes 
				{
					close(pipes[t9][1]);
				}
				redAppend(appendPos,Output); //if app in output file
				redOut(outPos,Output); // if just out
				dup2(pipes[pr-1][0],0);
				close(pipes[pr-1][0]);
				if (execvp(Commands[pr][0], Commands[pr]) == -1) {
					perror("execvp");
					exit(1);
				}
			}
			else // we are in the middle commands
			{
				for(int t9 = 0; t9 <NumberOfCommands-1; t9++ )//closing all the read pipes except the last pipe
				{
					if(t9 !=(pr-1))
					{
						close(pipes[t9][0]);
					}
				}
				for(int t9 = 0; t9 <NumberOfCommands-1; t9++ )//closing all the write pipes 
				{
					if(t9 != pr)
					{
						close(pipes[t9][0]);
					}
				}
				dup2(pipes[pr-1][0],0);
				dup2(pipes[pr][1],1);
				close(pipes[pr-1][0]);
				close(pipes[pr][1]);
				if (execvp(Commands[pr][0], Commands[pr]) == -1) {
					perror("execvp");
					exit(1);
				}

			}
					
		}
		else if((pids[pr])<0)
		{
			printf("Fork failed \n");
			exit(1);
		}
		
	}

	for(int i=0; i < NumberOfCommands-1; i++) //close pipes in main  process
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
    for(int i=0; i < NumberOfCommands; i++) // wait childs in main process
	{
		waitpid(pids[i],&status,0);
	}	
}