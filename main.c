#include <stdio.h>
#include <stdlib.h>
#include "shell/shell.h"

int main()
{   
    int pid;
    tShell shell;
    //Cria mascara de sinais bloqueados
    sigset_t block;
    //Inicializa mascara
    sigemptyset(&block);
    //Define quais sinais devem ser bloqueados
    sigaddset(&block, SIGINT);
    sigaddset(&block, SIGQUIT);
    sigaddset(&block, SIGTSTP);

    
    struct sigaction susr1 = {0};
    susr1.sa_handler = &handle_sigusr1;
    susr1.sa_flags = SA_RESTART;
    susr1.sa_mask = block;


    struct sigaction susr2 = {0};
    susr2.sa_handler = &handle_sigusr2;
    susr2.sa_flags = SA_RESTART;
    susr2.sa_mask = block;


    sigaction(SIGUSR1, &susr1, NULL);
    sigaction(SIGUSR2, &susr2, NULL);



    clean_screen();

    while (1)
    {

        type_prompt();
        read_commands(&shell);

        


        wait(NULL);
        
        // pid = fork();
        // if (pid == 0){
        //     exec_program(&shell);
        // }
        // else{
        //     wait(NULL);
        // }
        // if (is_exit_command(&shell)){
        //     break;
        // }
    }

    return 0;
}