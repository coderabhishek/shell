#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <ncurses.h>
#include "trie.h"
#include <fcntl.h>
#include <sys/sendfile.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include "support_routines.h"
#include "handle_builtins.h"


/* executes single process */
int single_process (int in, int out, command *cmd, int *fd,int direct_from,int n)
{
 

 if(direct_from && in == 0)
      {	
      	int new_file = open(cmd[n].argv[0], O_RDWR , 0666);
      	in = new_file;
	  }	
	      
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
int run_pipes (int n, command *cmd,int direct_to,int direct_from)
{
  int i;
  pid_t pid;
  int in, fd [2];

 in = 0;

if(direct_from) n--;

 for (i = 0; i < n ; ++i)
    {
	pipe(fd);


	 if(i<(n-1))
      	{
      	single_process(in, fd[1], cmd + i, fd,direct_from,n);
      	}
	  else 
	  	{ 
	  	  if(direct_to == 0 )
	  			{
	  			single_process(in,1,cmd+i,fd,direct_from,n);
	  	  		}
	  	  else if(direct_to)
	  			{
	  			int new_file = open(cmd[i].argv[0], O_RDWR | O_CREAT, 0666); 
	  			char readBuff[MAX*10];
	  			read(in,readBuff,sizeof(readBuff));
	  			write(new_file,readBuff,strlen(readBuff)+1);
	  			close(new_file);
			  	}
		}	

      in = fd[0];
    }
}

int main()
{
	char *cmd;
	node *root = init_trie();

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
		char ch;
		int i=0;
		
		ch = getchar();
		
		while(ch!='\n')
		{	
			if(ch=='	')
			{
				cmd[i] = '\0';
				getchar();
				search(root, cmd);
				printf(ANSI_COLOR_RED "\n%s" ANSI_COLOR_RESET " :%s", cwd, cmd);
				
			}
			else cmd[i++] = ch; 
		
		ch = getchar();	
		}
		
		cmd[i] = '\0';
		
		if(cmd[0] != '\0')
		{
			int ll;
			for(ll=0;cmd[ll]!='\0';ll++)
					if(cmd[ll]=='\n') cmd[ll] = '\0';
			cmd = (char *)sanitize_input(cmd);
			for(ll=0;cmd[ll]!='\0';ll++)
					if(cmd[ll]=='\n') cmd[ll] = '\0';
			add_to_history(cmd);

			if(handle_builtins(cmd))
			{
				command *command_list;	
				command_list = (command *)malloc(sizeof(command));				
				

				int *cnt = (int *)malloc(sizeof(int));
				int *dt = (int *)malloc(sizeof(int));	
				int *df = (int *)malloc(sizeof(int));

				command_list = tokenize(cmd,command_list,cnt,dt,df);
				int command_cnt = *cnt;	
		       	
		       	run_pipes(command_cnt,command_list,*dt,*df);
		    }
		}
		else printf("\n");
	}
}






 