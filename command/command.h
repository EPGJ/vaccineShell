#ifndef COMMAND_H
#define COMMAND_H
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>




typedef struct  {
    char cmd[100];
    char command[100];
    char *parameters[20]; 
    int number_parameters;
} tCommand;



#endif