#ifndef SHELL_H
#define SHELL_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include "../command/command.h"
#include "../utils/utils.h"

#define NUMBER_COMMANDS_MAX 5

typedef struct  {
    tCommand commands[NUMBER_COMMANDS_MAX];
    int number_commands;
} tShell;

void read_commands(tShell *);
void clean_screen();
void type_prompt();
void handle_sigusr_vsh();
void handle_sigusr_background();
void exec_process(tShell *);
void exec_background_processes(tShell *);
void liberamoita(tShell* shell);
void armageddon(tShell* shell);

#endif