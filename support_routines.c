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


char *sanitize_input(char input[])
{
	int n = strlen(input), w=0;
	char *res = (char *)malloc(MAX*sizeof(char));
	FILE *hist_file = fopen(history_file, "r");
	if(hist_file){
		char *history = (char *)malloc(MAX*sizeof(char));
		fread(history, sizeof(char), MAX, hist_file);
		for(int i=0;i<n;)
		{
			if(input[i]=='!')
			{
				int nn, t=0;
				if(isdigit(input[i+1])){
					char *num_s = (char *)malloc(MAX);
					while(i<n && isdigit(input[++i]))
						num_s[t++] = input[i];
					num_s[t] = '\0';
					nn = atoi(num_s);
				}
				else if(input[i+1]=='!'){
					i += 2;
					int lines = 0;
					for(int ii=0;history[ii]!='\0';++ii)
						if(history[ii]=='\n')
							lines++;
					nn = lines;
				}
				int j=0;
				int strl = strlen(history);
				for(int ii=0;ii<strl &&j<=nn;++ii)
				{
					int k = ii;
					while(ii<strl && history[ii]!='\n')
						ii++;
					j++;
					if(j==nn)
					for(int u=k;u<ii;++u)
						res[w++] = history[u];
				}
			}
			else res[w++] = input[i++];
		}
		res[w] = '\0';
		return res;
	} 
	else return input;
}


//for single command which is already separated by all the piping expressions
int tokenize2(char *single_cmd, command *cmd)      
{
	int i=0,j=0,index=0;
	
	char *cur = (char *)malloc(MAX*sizeof(char));
	
	cmd->argv = (char **)malloc((index+1)*sizeof(char*));

	while(single_cmd[i] == ' ') i++;

	int col = 0;

	while(true)
	{
		/* checks whether input is a string */ 
		if(single_cmd[i] == '\"' || single_cmd[i] == '\'')
			{col = col ^ 1; i++; continue; }

		if( (single_cmd[i]==' ' && col == 0)  || single_cmd[i]=='\0')
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
command* tokenize(char *complete_cmd,command *command_list,int *cnt,int *dt,int *df)
{
	int i=0,j=0,index=0;
	
	char *cur = (char *)malloc(MAX*sizeof(char));
	int direct_to = 0;
	int direct_from = 0;

	while(true)
	{
	if(complete_cmd[i] == '>')
		direct_to = 1;

	if(complete_cmd[i] == '<')
		direct_from = 1;	

	if(complete_cmd[i]=='|' || complete_cmd[i]=='>' || complete_cmd[i]=='\0' || complete_cmd[i]=='<')
		{

			cur[j] = '\0';
			tokenize2(cur,command_list+index);
			index++;	
			cur = (char *)malloc(MAX*sizeof(char));
			
			
			if(complete_cmd[i] == '|' || complete_cmd[i]=='>' || complete_cmd[i]=='<') i++;

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

	if(direct_to)
		(*dt) = 1;
		
	if(direct_from)
		(*df) = 1;
		
	(*cnt) = index;
	return command_list;	
}