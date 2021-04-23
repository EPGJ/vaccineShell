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
    char *parameters[20]; // no maximo 5 parametros, aqui foram colocados 6 pois o primeiro parametro do exec eh o proprio programa
    int number_parameters;
} tShell;


void clean_screen();
void type_prompt();
void read_command(tShell *);
void exec_program(tShell *);
int is_exit_command(tShell *);
void display(tShell*);

#endif