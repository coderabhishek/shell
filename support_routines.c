#include "support_routines.h"

bool handle_builtins(char cmd[]);
void  INThandler(int sig)
{
    signal(sig, SIG_IGN);
     printf("\nDo you really want to quit? [y/n]");
     char ch = getchar();
     if (ch == 'y' || ch == 'Y')
          exit(0);
     else
          signal(SIGINT, INThandler);
}

//for single command which is already separated by all the piping expressions
int tokenize2(char *single_cmd, command *cmd)      
{
	int i=0,j=0,index=0;
	
	char *cur = (char *)malloc(MAX*sizeof(char));
	
	cmd->argv = (char **)malloc((index+1)*sizeof(char*));

	while(single_cmd[i] == ' ') i++;

	while(true)
	{
		if(single_cmd[i]==' ' || single_cmd[i]=='\0')
		{
			cur[j] = '\0';
			cmd->argv[index++] = cur;
			cur = (char *)malloc(MAX*sizeof(char));
			
			//skips all spaces
			while( single_cmd[i] == ' ' ) i++;  
			
			//if this is not the last argument then allocate one more space
			if(single_cmd[i]!='\0')
				cmd->argv = (char **) realloc(cmd->argv,(index+1)*sizeof(char*)); 	
			else
				break;

			j=0;
		}
		else cur[j++] = single_cmd[i++];
	}
	
	return index;
}


//separates with pipes
command* tokenize(char *complete_cmd,command *command_list,int *cnt)
{
	int i=0,j=0,index=0;
	
	char *cur = (char *)malloc(MAX*sizeof(char));
	
	while(true)
	{
	if(complete_cmd[i]=='|' || complete_cmd[i]=='\0')
		{

			cur[j] = '\0';
			tokenize2(cur,command_list+index);
			index++;	
			cur = (char *)malloc(MAX*sizeof(char));
			
			
			if(complete_cmd[i] == '|') i++;

			while(complete_cmd[i] == ' ') i++;
			if(complete_cmd[i]!='\0')
				command_list = (command *) realloc(command_list,(index+1)*sizeof(command));
			else	
				break;
			j=0;
		}
	else 
		cur[j++] = complete_cmd[i++];
	}

	(*cnt) = index;
	return command_list;	
}