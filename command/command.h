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


/* Trata um comando e seus parâmetros;
 * inputs: ponteiro char
 * output: nenhum;
 * pre-condicao: ponteiro char válido;
 * pos-condicao: string (char *) tratada e salva no TAD tCommand.
 */
 tCommand treat_command(char *);

/* Executa os processos em foreground;
 * inputs: ponteiro to tipo tCommand;
 * output: nenhum;
 * pre-condicao: ponteiro tCommand válido;
 * pos-condicao: Comando executando em foreground 
 */
pid_t exec_fg_command(tCommand *cmd);

/* Executa os processos em background
 * inputs: ponteiro do tipo tCommand;
 * output: nenhum;
 * pre-condicao: ponteiro tCommand válido;
 * pos-condicao: comando executados em background.
 */
pid_t exec_bg_command(tCommand *cmd, int** fd, int command_id, int n_commands);


#endif