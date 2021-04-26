#ifndef COMMAND_H
#define COMMAND_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define COMMAND_MAX_LEN 100
#define PARAMETER_MAX_LEN 20
#define QTD_PARAMETERS_MAX 3

typedef struct command tCommand;

struct command {
    char command[COMMAND_MAX_LEN];
    char parameters[QTD_PARAMETERS_MAX][PARAMETER_MAX_LEN]; 
    int number_parameters;
};

tCommand treat_command();
void print_command(tCommand *cmd);
pid_t exec_fg_command(tCommand *cmd);
pid_t exec_bg_command(tCommand *cmd, int** fd, int command_id, int n_commands);


#endif