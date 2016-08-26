#ifndef handle_builtins_include_guard

#define handle_builtins_include_guard
#include <string.h>
#include "support_routines.h"

int tokenize(char *str, char *tokens[50]);


void run_cd(char *path)
{
	char abs_path[100];
	getcwd(abs_path, 50);
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
}

#endif