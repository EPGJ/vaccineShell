#include <stdio.h>
#include <stdlib.h>
#include "shell/shell.h"

int main()
{   
    int pid;
    tShell shell;


    struct sigaction susr1 = {0};
    susr1.sa_handler = &handle_sigusr1;
    susr1.sa_flags = SA_RESTART;

    struct sigaction susr2 = {0};
    susr2.sa_handler = &handle_sigusr2;
    susr2.sa_flags = SA_RESTART;
    
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