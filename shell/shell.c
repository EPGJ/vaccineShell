#include "shell.h"

char * aligator[] = {
           "\n",
           "                  _  _\n",
           "        _ _      (0)(0)-._  _.-'^^'^^'^^'^^'^^'--.\n",
           "       (.(.)----'`        ^^'                /^   ^^-._\n",
           "       (    `                 \             |    _    ^^-._\n",
           "        VvvvvvvVv~~`__,/.._>  /:/:/:/:/:/:/:/\  (_..,______^^-.\n",
           "         `^^^^^^^^`/  /   /  /`^^^^^^^^^>^^>^`>  >        _`)  )\n",
           "                   (((`   (((`          (((`  (((`        `'--'^\n",
           "   I feel weird...\n"
       };


void handle_sigusr1(int sig){
       for(int i = 0; i < 9; i++){
           printf("%s", aligator[i]);
       }
}
void handle_sigusr2(int sig){
    handle_sigusr1(sig);
}


void clean_screen()
{
    printf("\e[1;1H\e[2J");
}



void read_commands(tShell *shell)
{
    shell->number_commands = 0;
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

    // Separa e trata comandos digitados
    char *token, *rest;
    const char symbol[2] = "|";

    token = strtok_r(line, symbol, &rest);
    for (int i = 0; token!=NULL && i < NUMBER_COMMANDS_MAX; i++){
        shell->commands[i] = treat_command(trim(token));
        shell->number_commands++;
        // print_command(shell->commands[i]);
        token = strtok_r(rest, symbol, &rest);
    }
    exec_command(shell->commands[0], 0, 0);
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
