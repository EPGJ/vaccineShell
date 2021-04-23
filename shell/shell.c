#include "shell.h"

void clean_screen()
{
    printf("\e[1;1H\e[2J");
}

void type_prompt()
{
    printf("\033[0;32m"); // muda a cor da string para verde
    printf("vsh>");
    printf("\033[0m");
}

void read_command(tShell *shell)
{

    char line[1024];
    char *commands;
    const char s[2] = " ";
    int count = 0, i = 0;
    for (;;)
    {
        int c = fgetc(stdin);
        line[count++] = (char)c;
        if (c == '\n')
            break;
    }
    if (count == 1)
    {
        return;
    }

    commands = strtok(line, "\n");
    commands = strtok(line, " ");

    while (commands != NULL)
    {
        shell->parameters[i++] = commands;
        commands = strtok(NULL, " ");
    }
    // printf("(%s)\n", shell->parameters[0]);

    strcpy(shell->command, shell->parameters[0]);
}

void exec_program(tShell *shell)
{

    execvp(shell->command, shell->parameters);
}
int is_exit_command(tShell *shell)
{
    if (strcmp(shell->command, "exit") == 0)
    {
        return 1;
    }
    else
        return 0;
}
