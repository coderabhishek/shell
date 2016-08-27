#ifndef support_routines_include_guard

#define support_routines_include_guard
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

typedef int bool;
enum { false, true };

#define MAX 500
#define history_file "history"
#define his_num 10
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct command
{
  char **argv;
}command;

bool handle_builtins(char cmd[]);

//handles the interrupts
void  INThandler(int sig);

//separates with pipes
command* tokenize(char *complete_cmd,command *command_list,int *cnt);

//for single command which is already separated by all the piping expressions
int tokenize2(char *single_cmd,command *cmd);

#endif
