#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

typedef struct  {
    char cmd[100];
    char command[100];
    char *parameters[20];
    
} tShell;


void clean_screen();
void type_prompt();
void read_command(tShell *);
void exec_program(tShell *);
int is_exit_command(tShell *);


#endif