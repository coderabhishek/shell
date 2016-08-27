#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include "support_routines.h"
#include "handle_builtins.h"

/* executes single process */
int single_process (int in, int out, command *cmd, int *fd)
{
  pid_t pid = fork ();
  if (pid == 0)
    {
      if (in != 0)
        {
          dup2 (in, 0);
          close (in);
        }
       if (out != 1)
        {
          dup2 (out, 1);
          close (out);
        }
     return execvp (cmd->argv [0], (char * const *)cmd->argv);
    }
  else {
  	close(fd[1]);
  	wait(NULL);
  }
  return pid;
}


/* executes many processes */
int run_pipes (int n, command *cmd)
{
  int i;
  pid_t pid;
  int in, fd [2];

  in = 0;

  for (i = 0; i < n ; ++i)
    {
      pipe (fd);
      
      if(i<(n-1)){
      	single_process(in, fd[1], cmd + i, fd);
      }
	  else
	  	single_process(in,1,cmd+i, fd);

      in = fd[0];
    }
}

int main()
{
	
	char *cmd;

	cmd = (char*) malloc (sizeof(char)*MAX*10);

	while(1)
		{
			signal(SIGINT, INThandler);
			
			//prints current directory
			char cwd[MAX];
			getcwd(cwd, MAX);
			fflush(stdin);
			printf(ANSI_COLOR_RED "%s" ANSI_COLOR_RESET " :", cwd);
			//input the command
			if(fgets(cmd, MAX, stdin) != 0)
			{
				add_to_history(cmd);
				char c;
				int ll;
				for(ll=0;cmd[ll]!='\0';ll++)
						if(cmd[ll]=='\n') cmd[ll] = '\0';

				if(handle_builtins(cmd))
				{
					command *command_list;	
					command_list = (command *)malloc(sizeof(command));				
					int *cnt = (int *)malloc(sizeof(int));
					command_list = tokenize(cmd,command_list,cnt);
					int command_cnt = *cnt;	
			       	run_pipes(command_cnt,command_list);
			    }
			}
			else printf("\n");
		}
}






 