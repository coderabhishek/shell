#ifndef handle_builtins_include_guard

#define handle_builtins_include_guard
#include <string.h>
#include "support_routines.h"

int tokenize(char *str, char *tokens[50]);


void run_cd(char *path)
{
	char abs_path[100];
	abs_path[0] = '\0';
	if(path[0]!='/')
	{
		getcwd(abs_path, 50);
		int t = strlen(abs_path);
		abs_path[t] = '/';
		abs_path[t+1] = '\0';
	}
	int read_head=0, write_head=0;
	while(abs_path[read_head]!='\0')
	{
		if(abs_path[read_head]=='.' && abs_path[read_head+1]!='.')
		{
			read_head++;
			if(abs_path[read_head]=='/')
				read_head++;
		}
		else if(abs_path[read_head]=='.')
		{
			while(write_head>=0 && abs_path[write_head]!='/')
				write_head--;
		}
		else
			abs_path[write_head++] = abs_path[read_head++];
	}
	abs_path[write_head] = '\0';
	strcat(abs_path, path);
	printf("absPath%s\n", abs_path);
	chdir(abs_path);
}


bool handle_builtins(char cmd[])
{
	char *tokens[50];
	int token_size = tokenize(cmd, tokens);
	if(!strcmp(tokens[0], "cd")){
		run_cd(tokens[1]);
		return false;
	}
	else if(!strcmp(tokens[0], "exit"))
	{
		exit(0);
	}
	return true;
}

#endif