#ifndef COMMAND_H
#define COMMAND_H
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define COMMAND_MAX_LEN 100
#define PARAMETER_MAX_LEN 20
#define QTD_PARAMETERS_MAX 5

typedef struct command tCommand;

struct command {
    char command[COMMAND_MAX_LEN];
    char parameters[QTD_PARAMETERS_MAX][PARAMETER_MAX_LEN]; // no maximo 5 parametros, aqui foram colocados 6 pois o primeiro parametro do exec eh o proprio programa
    int number_parameters;
};

tCommand treat_command();
void print_command(tCommand command);
void exec_program(tCommand *);



#endif