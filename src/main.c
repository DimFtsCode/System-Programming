#include "def.h"



int main(){
	char* prompt = "in-mysh-now:> ";
    char* line = NULL ;
    char* line_copy;
    size_t n = 0;
    ssize_t nchars_read;
    const char* delimiter = " \n";
    char* tok;
    int ContOrBreak = 1;
	AliasList l1;
	l1.num_of_al = 0;
	HistorList h1;
	h1.num_of_al = 0;
	
	signal(SIGINT,SIG_IGN);
	signal(SIGTSTP,SIG_IGN);
	
	while(ContOrBreak){
		int numoffg=0;
		int numbofbg=0;
		int orders = 0;
		int status;
		int HistoryFlag = 0;


		
		
		/*for(int i=0; i <100; i++) //Initiation PipesPos to 0
		{
			PipesPos[i] = 0;
		}*/
		static int pr = 0;
        int NumOfTok = 0;
        printf(" %s", prompt);
		if(pr)
		{
			printf("\n");
		}
    
        
        
        nchars_read = getline(&line, &n, stdin); //taking line from the terminal
        if (nchars_read == -1){
            printf("Exiting shell....\n");
            return (-1);
        }

        line_copy = malloc(sizeof(char)* nchars_read);
        if(line_copy == NULL){
            printf("line_copy memory allocation error");
            return (-1);
        }

        strcpy(line_copy,line);

        tok = strtok(line, delimiter);

        while (tok != NULL){
            NumOfTok++;
            tok = strtok(NULL, delimiter);
        }
        NumOfTok++;

        /* Allocate space to hold the array of strings */
		char** avv;
        avv = malloc(sizeof(char *) * NumOfTok);
        if(avv == NULL){
            printf("argv memory allocation error");
            return (-1);
        }

        tok = strtok(line_copy, delimiter);
		
        for (int j = 0; tok != NULL; j++){ //creating the starting argument splited in strings
            avv[j] = malloc(sizeof(char) * strlen(tok));
            if(avv[j] == NULL){
                printf("argv[%d] memory allocation error",j);
            }
            strcpy(avv[j], tok);

            tok = strtok(NULL, delimiter);
        }
        avv[NumOfTok-1] = NULL;
       
	   insert_histor(&h1,avv,NumOfTok);

	   
	   // History "Number"
	   if(strcmp(avv[0],"myHistory")==0 && (avv[1] != NULL))
	   {
			int hisnum = atoi(avv[1]);
			int hislenght = get_lenght(&h1,hisnum);
			if(hislenght == 0)
			{
				printf("Command does not exist in history");
			}
			else
			{
				free(avv[0]);
				free(avv[1]);
				free(avv[2]);
				char** av1 = get_comm(&h1,hisnum);
				avv = malloc(sizeof(char*)*hislenght);
				for(int i=0; i <hislenght-1; i++)
				{
					avv[i] = malloc(sizeof(char)*strlen(av1[i]));
					strcpy(avv[i],av1[i]);
				}
				avv[hislenght-1] = NULL;
				NumOfTok = hislenght;
			}
	    }


		// History
		if(strcmp(avv[0],"myHistory")==0 && (avv[1] == NULL))
	   	{
			print_history(&h1);
			HistoryFlag = 1;


		}

		//passing for bg and fg orders
		for(int i=0; i <NumOfTok-1; i++)
		{
			if(strcmp(avv[i],"&;")==0)
			{
				numbofbg++;

			}
			if(strcmp(avv[i],";")==0)
			{
				numoffg++;
			}
		}
		
		if((!numbofbg) && (!numoffg))
		{
			orders = 1;
			numoffg =1;
		}
		else
		{
			orders = numbofbg + numoffg;
		}
		//printf("BG: %d | FG: %d",numbofbg,numoffg);
		int countAv;
		int s1 =0;
		int s2 =0;
		int s3 =0;
		int pidsBG[numbofbg];
		int pidFG;
		int cBG = 0;



		while(orders > 0)
		{
			countAv = 0;
			while(s1 < NumOfTok-1)
			{
				if((strcmp(avv[s1],"&;")==0) || (strcmp(avv[s1],";")==0))
				{
					s1++;
					break;
				}
				else
				{
					countAv++;
					s1++;
				}
			}
			char** av = malloc(sizeof(char*)*(countAv+1));
			s3 = 0;
			while(s2<NumOfTok-1)
			{
				if((strcmp(avv[s2],"&;")==0) || (strcmp(avv[s2],";")==0))
				{
					s2++;
					break;
				}
				else
				{
					av[s3] = malloc(sizeof(char)* strlen(avv[s2]));
					strcpy(av[s3],avv[s2]);
					
					s2++; 
					s3++;
				}
				
			}
			av[countAv] = NULL;

			for(int i=0; i <= countAv; i++)
			{
				printf("(%d)<%s>\t",i,av[i]);
			}
		
			
			int inPos = 0; //flag for input
			int outPos = 0; //flag for output
			int appendPos = 0; //Flags to determine the order
			int TermFlag = 0; //flag for terminate
			char Input[64],Output[64];
			int CountOfPipes = 0; // count of pipes
			//int PipesPos[100]; //Limit is 100 pipes
			//int Pos = 0;
			char*** Commands; 
			//int status;
			int CrAl=0; //flag for createaliance
			int DelAl=0; // flag for deleting aliance
			int PrintAl=0; // flag for printing alinace
			int cd = 0; // flag for built in order
			
		
        
			if((strcmp(av[0],"exit")==0) || (strcmp(av[0],"quit")==0)) // quit or exit close shell
			{
				TermFlag = 1;
				ContOrBreak = 0;
			}
			strcpy(Input,"Not");
			strcpy(Output,"Not");
			//printf("countAv %d \n",countAv);
			
			//here we start parsing 
			for(int i =0; i < countAv; i++)
			{
				if(strcmp(av[0],"printalias") == 0)
				{
					PrintAl = 1;
					//printf("printalias");
				}
				if(strcmp(av[0],"createalias") == 0)
				{
					CrAl = 1;
					//printf("createalias");
				}
				if(strcmp(av[0],"destroyalias") == 0)
				{
					DelAl = 1;
					//printf("destroyalias");
				}
				if(strcmp(av[i],"<") == 0)
				{
					inPos = i;
					
					strcpy(Input,av[i+1]);
					//printf("Input at pos %d: %s \n",i+1,Input);
				}
				if(strcmp(av[i],">") == 0)
				{
					outPos = i;
					
					strcpy(Output,av[i+1]);
					//printf("Output at pos %d: %s \n",i+1,Output);
				}
				if(strcmp(av[i],">>") == 0)
				{
					appendPos = i;
					
					strcpy(Output,av[i+1]);
					//printf("Output at pos %d: %s \n",i+1,Output);
				}
				if((strcmp(av[i],"|")==0)) //only in the first pipe
				{
					//PipesPos[Pos++] = i;
					CountOfPipes++;
					//printf("CountOfPipes: %d",CountOfPipes);
				}
			}

			/*
			//printf("Countofpipes: %d \n",CountOfPipes);
			if(CountOfPipes>0)
			{
				for(int t=0; t < CountOfPipes; t++)
				{
					printf("PipesPos: %d\t",PipesPos[t]);
				}
			}*/
			int NumberOfCommands = CountOfPipes +1;
			//printf("NumberOfcommands: %d \n",NumberOfCommands);
			
			Commands = malloc(sizeof(char**)*(NumberOfCommands));
			
			int* Counts = malloc(NumberOfCommands * sizeof(int)); // array for memorize the size of each command
			int t1 =0; //First av passing finding the count
			int t2 =0; //Second av passing creating the Command 
			int t3 =0; // for array of counts
			int t4 =0; // for verbs in a command
			int t5 = 0; // for diff commands in commands
		// createalias myhome “cd /home/users/smith”	
		// sort < file1.txt | grep file2.txt | cat > file3.txt &
			while(t3 < NumberOfCommands)
			{
				int CoA = 0;
				int pos1 = -1;
				Counts[t3]=0;
				while(t1 <countAv) // to null
				{
					
					if(strcmp(av[t1],"&")==0)
					{
						
						break;
					}
					if(strcmp(av[t1],"|") ==0 )  //break the inside loop
					{
						t1++;
						break;
					}
					if((strcmp(av[t1],"<") != 0) && (strcmp(av[t1],">") != 0) && (strcmp(av[t1],">>") != 0) && (strcmp(av[t1],Input) != 0) && (strcmp(av[t1],Output) != 0) && (strcmp(av[t1],"createalias") != 0) && (strcmp(av[t1],"destroyalias") != 0))
					{
						if((CrAl == 0) && ((CoA =existion_of_alias(&l1,av[t1])) > 0)) //if alias exist and not create
						{
							Counts[t3] = Counts[t3] + (CoA+1); //count of this command is previous count + count of alias
							pos1 = t1; //alias position
							//printf("Pos1: %d and CoA: %d and CrAl: %d\t",pos1,CoA,CrAl);
						}
						else
						{
							Counts[t3]++;
						}
					}
					t1++;//for av
				}
				//printf("Count %d: = %d \n",t3,Counts[t3]);
				
				Commands[t5] = malloc(sizeof(char*)*(Counts[t3]+1));
				// createalias myhome "cd /home/users/smith"
				// createalias sor "sort -r -d"
				while(t2 < countAv) // to null
				{
					
					if(strcmp(av[t2],"&")==0)
					{
						
						break;
					}
					
					if(strcmp(av[t2],"|") ==0 )  //break the inside loop
					{
						t2++;
						break;
					}
					if((strcmp(av[t2],"<") != 0) && (strcmp(av[t2],">") != 0) && (strcmp(av[t2],">>") != 0) && (strcmp(av[t2],Input) != 0) && (strcmp(av[t2],Output) != 0) && (strcmp(av[t2],"createalias") != 0) && (strcmp(av[t2],"destroyalias") != 0))
					{//createalias sor "sort -d -r"
						if((CrAl==0) && (t2 == pos1)) //if we are in the current position of alias
						{
							int CoA1 = existion_of_alias(&l1,av[pos1]);
							char** CoaCommands = return_command(&l1,av[pos1]);
							for(int i=0; i<CoA1; i++)
							{
								Commands[t5][t4] = malloc(sizeof(char)*strlen(CoaCommands[i]));
								strcpy(Commands[t5][t4],CoaCommands[i]);
								//printf("(%d)<%s>",t4,Commands[t5][t4]);
								//printf("CoaCommands: %s - t4:%d",CoaCommands[i],t4);
								t4++;
							} 
						}
						else
						{
							if(CrAl)//if createalias rmove "" from order
							{
								for (int i = 0; av[t2][i]; i++) {
									remove_char(av[t2],'"');
									av[t2] = realloc(av[t2],sizeof(strlen(av[t2])));
								//printf("%c", av[t2][i]);
								}
							}
							Commands[t5][t4] = malloc(sizeof(char)*strlen(av[t2]));
							strcpy(Commands[t5][t4], av[t2]);
							//printf("(%d)<%s>",t4,Commands[t5][t4]);
							t4++;
						}	
					}
					t2++;//for av
				}
				Commands[t5][t4] = NULL;
				//printf("(%d)<%s>\t",t4,Commands[t5][t4]);
				//printf("t5:(%d)",t5);
				t5++;
				t4=0; //New array
				
					
				t3++;	
			}
			//We have the commands now and we check them for wildcard
			for(int i=0; i< NumberOfCommands; i++)
			{
				Commands[i] = wildcard(Commands[i],&Counts[i]);
			}


			if(strcmp(Commands[0][0],"cd")==0)
			{
				if(chdir(Commands[0][1])!=0)
					perror("chdir: ");
				else printf("Folder changed. \n");
				cd = 1;
			}
			//We have ready the Commands the Output the Input and the flags for redirection(in,out,append)
			if((numbofbg) && (!HistoryFlag))//bg command 
			{
				
				
				pidsBG[cBG] = fork();
				if(pidsBG[cBG]==0)
				{
					signal(SIGINT,SIG_DFL);
					signal(SIGTSTP,SIG_DFL);
					sleep(5);
					chooseExec(Commands,NumberOfCommands,inPos,outPos,appendPos,Input,Output,CountOfPipes);
					exit(0);
				}
				else if((pidsBG[cBG])<0)
				{
					printf("Fork failed \n");
					exit(1);
				}
				cBG ++;
				numbofbg--;
			}
			else if(CrAl)
			{// createalias sor "sort -r -d"
				Alias* a1;
				a1 = create_alias_command(Commands,Counts);
				int ch =insert_alias(&l1,a1);
				if(ch)
				{
					printf("problem with memory or this alias name already exist \n");
				}
				
			}
			else if(DelAl)
			{
				delete_alias(&l1,Commands[0][0]);
			}
			else if(PrintAl)
			{
				print_Alist(&l1);
			}
			else if((!TermFlag) && (!numbofbg) && (numoffg) && (!HistoryFlag) && (!cd))
			{
				pidFG = fork();
				if(pidFG==0)
				{
					signal(SIGINT,SIG_DFL);
					signal(SIGTSTP,SIG_DFL);
					//sleep(5);
					chooseExec(Commands,NumberOfCommands,inPos,outPos,appendPos,Input,Output,CountOfPipes);
					exit(0);
				}
				else if((pidFG)<0)
				{
					printf("Fork failed \n");
					exit(1);
				}
				else
				{
					waitpid(pidFG,&status,0);
				}
			}
			
			
			
			//Dont forget free Command Input Output and Everything
			for(int i=0; i < NumberOfCommands; i++)
			{
				//printf("\ti= %d",i);
				for(int k=0; k <= Counts[i]; k++) // In count we dont count NULL
				{
					//printf("k= %d",k);
					free(Commands[i][k]);
				}
				free(Commands[i]);
			}
		
		
			
			free(Commands);
			free(Counts);
			orders--;
			for(int i=0; i < countAv-1; i++)
			{
				free(av[i]);
			}
			free(av);
		}
		
			
		
		/*for(int i=0; i < cBG; i++)
		{
			waitpid(pidsBG[i],&status,0);
		}*/


        //free(line_copy);
        for(int i =0; i <= NumOfTok-1; i++)
        {
            free(avv[i]);
        }
        free(avv);
    	 
		
		
    } 
    free(line);
	free_alias_in_list(&l1);
	free_histor_list(&h1);
	return 0;
}


//sort < file1.txt | cat -d | grep > file4.txt
//cat file1.txt file2.txt file3.txt | sort > file4.txt