#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#include<sys/types.h>
#include<unistd.h>


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

int tokenize(char *str, char *tokens[50])
{
	int i=0,j=0, tokens_index=0;
	char *cur = (char *)malloc(50*sizeof(char));
	for(i=0;str[i]!='\0';++i)
	{

		if(str[i]==' ')
		{
			cur[j] = '\0';
			tokens[tokens_index++] = cur;
			cur = (char *)malloc(50*sizeof(char));
			j=0;
		}
		else cur[j++] = str[i];
	}
	cur[j] = '\0';
	tokens[tokens_index++] = cur;
	tokens[tokens_index] = NULL;
	return tokens_index;
}


void main()
{
	char cmd[50];
	while(1){
		signal(SIGINT, INThandler);
		char cwd[50];
		getcwd(cwd, 50);
		printf("%s", cwd);
		if(fgets(cmd, sizeof(cmd), stdin) != 0){
			cmd[strlen(cmd)-1] = '\0';
			if(cmd[0]!='\0'){
				char *tokens[50];
				int tokens_size = tokenize(cmd, tokens);
				pid_t pid = fork();
				if(pid==0)
				{
					execvp(tokens[0], tokens);
					perror("Its all fucked!!");
				}
				else wait(NULL);
			}
		}
		else printf("\n");
	}
}