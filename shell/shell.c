#include "shell.h"

void clean_screen()
{
    printf("\e[1;1H\e[2J");
}



void read_commands(tShell *shell)
{
    char line[1024];
    int count = 0;
    for (;;)
    {
        int c = fgetc(stdin);
        line[count++] = (char)c;
        if (c == '\n'){
            line[count-1] = '\0';
            break;
        }
    }
    // Trata se for apenas uma quebra de linha
    if (count == 1) return;

    char* cmd_str;
    int i = -1;
    cmd_str = strtok(line, "|");
    while(cmd_str!=NULL && (i++) < NUMBER_COMMANDS){
        shell->commands[i] = treat_command(cmd_str);
        print_command(shell->commands[i]);
        // printf("(%s)\n", trim(cmd_str));
        cmd_str = strtok(NULL, "|");
    }

}

void type_prompt()
{
    printf("\033[0;32m"); // muda a cor da string para verde
    printf("vsh>");
    printf("\033[0m");
}

// void exec_program(tShell *shell)
// {

//     execvp(shell->command, shell->parameters);
// }
// int is_exit_command(tShell *shell)
// {
//     if (strcmp(shell->command, "exit") == 0)
//     {
//         return 1;
//     }
//     else
//         return 0;
// }

// // temporary function
// void display(tShell *shell)
// {
//     printf("command --> %s\n", shell->command);

//     for (int j = 0; j < shell->number_parameters; j++)
//     {
//         printf("arg[%d] == %s\n", j, shell->parameters[j]);
//     }
// }
