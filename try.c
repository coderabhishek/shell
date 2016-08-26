#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include "support_routines.h"
#include "handle_builtins.h"

void main()
{
	char cmd[50];
	while(1){
		signal(SIGINT, INThandler);
		char cwd[50];
		getcwd(cwd, 50);
		printf("%s ", cwd);
		if(fgets(cmd, sizeof(cmd), stdin) != 0){
			cmd[strlen(cmd)-1] = '\0';
			bool ch = handle_builtins(cmd);
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