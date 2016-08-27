#ifndef handle_builtins_include_guard

#define handle_builtins_include_guard
#include <string.h>
#include "support_routines.h"

void history()
{
	FILE *hist_file = fopen(history_file, "r");
	char *history = (char *)malloc(MAX*sizeof(char));
	fread(history, sizeof(char), MAX, hist_file);
	int h_len = strlen(history), j=0;
	for(int i=h_len-1;i>=0&&j<=his_num;--i)
	{
		while(i>=0 && history[i--]!='\n');
		j++;

	}
	printf("%s\n", history);
	fclose(hist_file);
}

void add_to_history(char cmd[])
{
	FILE *hist_file = fopen(history_file, "a");
	char *history = (char *)malloc(MAX*sizeof(char));
	fprintf(hist_file, "%s\n", cmd);
	fclose(hist_file);
}

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

	//Taking care of `.` and `..`
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
	chdir(abs_path);
}


bool handle_builtins(char cmd[])
{
	command *cmds = (command *)malloc(sizeof(cmd));
	int token_size = tokenize2(cmd, cmds);
	char **exec_cmd = cmds->argv;
	if(!strcmp(exec_cmd[0], "cd")){
		run_cd(exec_cmd[1]);
		return false;
	}
	else if(!strcmp(exec_cmd[0], "exit"))
	{
		exit(0);
	}
	else if(!strcmp(exec_cmd[0], "history"))
	{
		history();
		return false;
	}
	return true;
}

#endif