#include "shell.h"

#define READ 0
#define WRITE 1

char *aligator[] = {
    "\n",
    "                  _  _\n",
    "        _ _      (0)(0)-._  _.-'^^'^^'^^'^^'^^'--.\n",
    "       (.(.)----'`        ^^'                /^   ^^-._\n",
    "       (    `                 \\             |    _    ^^-._\n",
    "        VvvvvvvVv~~`__,/.._>  /:/:/:/:/:/:/:/\\  (_..,______^^-.\n",
    "         `^^^^^^^^`/  /   /  /`^^^^^^^^^>^^>^`>  >        _`)  )\n",
    "                   (((`   (((`          (((`  (((`        `'--'^\n",
    "   I feel weird...\n"};

void handle_sigusr(int sig)
{
    for (int i = 0; i < 9; i++)
    {
        printf("%s", aligator[i]);
    }
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
        if (isspace(c))
            wspace_count++; // contabiliza white-spaces
        if (c == '\n')
        {
            line[len - 1] = '\0';
            break;
        }
    }
    // Retorna se linha só contém white-space
    if (len == wspace_count)
        return;

    // Separa e trata comandos digitados
    char *token, *rest;
    const char symbol[2] = "|";

    token = strtok_r(line, symbol, &rest);
    for (int i = 0; token != NULL && i < NUMBER_COMMANDS_MAX; i++)
    {
        shell->commands[i] = treat_command(trim(token));
        shell->number_commands++;
        // print_command(shell->commands[i]);
        token = strtok_r(rest, symbol, &rest);
    }
}

void type_prompt()
{
    printf("\033[0;32m"); // muda a cor da string para verde
    printf("vsh>");
    printf("\033[0m");
}

void exec_process(tShell *shell)
{
    if (shell->number_commands == 1)
    {
        exec_fg_command(shell->commands[0]);
    }
    else
    {
        exec_background_process(shell);
    }
}

void exec_background_process(tShell *shell)
{
    int pid = fork();
    if (pid == -1)
    {
        exit(1); // codigo de erro
    }
    // Esse novo processo criado sera responsavel por criar todos os outros e coloca-los em uma mesma sessao
    else if (pid == 0)
    {
        setsid();

        int n_commands = shell->number_commands;
        // Cria pipes
        int fd[n_commands-1][2];
        for (int i = 0; i < n_commands-1; i++) {
            pipe(fd[i]);
        }
        
        for(int i = 0 ; i < n_commands; i++) {
            exec_bg_command(shell->commands[i], fd, i,shell->number_commands);
        }
        
    }else{
        wait(NULL);
    }
}
