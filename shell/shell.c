#include "shell.h"

void clean_screen()
{
    printf("\e[1;1H\e[2J");
}



void read_commands(tShell *shell)
{
    char line[1024];
    int len = 0, wspace_count = 0;
    
    for (;;)
    {
        int c = fgetc(stdin);
        line[len++] = (char)c;
        if (isspace(c)) wspace_count++; // contabiliza white-spaces
        if (c == '\n'){
            line[len-1] = '\0';
            break;
        }
    }
    // Retorna se linha só contém white-space
    if (len == wspace_count) return;
    printf("[%s]\n", line);

    // Separa e trata comandos digitados
    char *token, *rest;
    const char symbol[2] = "|";
    int i = -1;

    token = strtok_r(line, symbol, &rest);
    while(token!=NULL && (i++) < NUMBER_COMMANDS_MAX){
        shell->commands[i] = treat_command(trim(token));
        print_command(shell->commands[i]);
        token = strtok_r(rest, symbol, &rest);
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
