#include <stdio.h>
#include <stdlib.h>
#include "shell/shell.h"

int main()
{

    int pid;
    tShell shell;
    clean_screen();

    while (1)
    {

        type_prompt();
        read_command(&shell);
        pid = fork();
        if (pid == 0)
        {
            exec_program(&shell);
        }
        else
        {
            wait(NULL);
        }

        if (is_exit_command(&shell))
        {
            break;
        }
    }

    return 0;
}