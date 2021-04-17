#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>


void type_prompt(){
    static int first_time = 1;
    if(first_time){
        const char* CLEAR_SCREEN_ANSI="\e[1;1H\e[2J";
        write(STDOUT_FILENO, CLEAR_SCREEN_ANSI,12);
        first_time = 0;
    }
    printf("\033[0;32m"); // muda a cor da string para verde
    printf("vsh>");
    printf("\033[0m");
}


void read_command(char cmd[], char * par[]){

    char line[1024];
    int count = 0, i = 0, j = 0;
    char *array[100], *pch;


    for(;;){
        int c = fgetc (stdin);
        line[count++]= (char) c;
        if (c == '\n') break;
    }
    if (count == 1) return;
    pch = strtok( line, "\n");

    while(pch != NULL){
        array[i++] = strdup(pch);
        pch = strtok(NULL,"\n");
    }
    strcpy(cmd,array[0]);

    for(int j = 0; j< i; j ++){
        par[j] = array[j];
    }
    par[i] = NULL;




}




int main(){
    char cmd[100], command[100],*parameters[20];
    char *envp[] = {(char *)"PATH=/bin",  0 };
    int pid;
    while(1){
        type_prompt();
        read_command(command,parameters);
        
        pid = fork();
        if(pid ==0){
            strcpy(cmd, "/bin/");
            printf("(%s)\n", cmd);
            strcat(cmd, command);
            printf("(%s)\n", cmd);
            execve(cmd, parameters, envp);
        }
        else{
            wait(NULL);
        }
        
        if (strcmp(command, "exit")==0){
            break;
        }
    }
    return 0;
}