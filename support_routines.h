#ifndef support_routines_include_guard

#define support_routines_include_guard
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

typedef int bool;
enum { false, true };

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
			while(str[i+1]==' ')
			 i++;
		}
		else cur[j++] = str[i];
	}
	cur[j] = '\0';
	tokens[tokens_index++] = cur;
	tokens[tokens_index] = NULL;
	return tokens_index;
}

#endif
