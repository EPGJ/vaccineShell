#ifndef SHELL_H
#define SHELL_H
#define NUMBER_COMMANDS 5
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include "../command/command.h"
#include "../utils/utils.h"



typedef struct  {
    tCommand commands[NUMBER_COMMANDS];
} tShell;

void read_commands(tShell *);
void clean_screen();
void type_prompt();
// void read_command(tShell *);
// void exec_program(tShell *);
// int is_exit_command(tShell *);
// void display(tShell*);

#endif