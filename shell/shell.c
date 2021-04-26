#include "shell.h"

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
        tCommand *cmd = &shell->commands[0];
        if (strcmp(cmd->command, "liberamoita") == 0)
        {
            printf("Executa liberamoita\n"); // TODO: implementar comando interno
            return;
        }
        if (strcmp(cmd->command, "armageddon") == 0)
        {
            printf("Executa armageddon\n"); // TODO: implementar comando interno
            return;
        }
        exec_fg_command(cmd);
    }
    else
    {
        exec_background_process(shell);
    }
}

void exec_background_process(tShell *shell)
{
    pid_t pid = fork();
    if (pid == -1)
    {
        exit(1); // codigo de erro
    }
    // Esse novo processo criado sera responsavel por criar todos os outros e coloca-los em uma mesma sessão
    else if (pid == 0)
    {
        setsid(); // troca processo de seção

        int i, n_commands = shell->number_commands;
        printf("%d\n", n_commands);

        // Cria n_commands-1 pipes
        int **fd = malloc((n_commands - 1) * sizeof(int *));

        for (i = 0; i < (n_commands - 1); i++)
        {
            fd[i] = malloc(2 * sizeof(int));
            pipe(fd[i]);
            close(fd[i][0]);
            close(fd[i][1]);
        }
        // Executa cada comando
        for (i = 0; i < n_commands; i++)
        {
            pid_t pid_c = exec_bg_command(&shell->commands[i], fd, i, n_commands);
            printf("[PID=%d] PROCESS(%d/%d)='%s'\n", pid_c, i+1, n_commands, shell->commands[i].command);
        }
        for (i = 0; i < n_commands - 1; i++)
        {
            free(fd[i]); // libera matriz fd
        }
        free(fd);
        // Espera fim da execução dos filhos criados
        while (1)
        {
            if (((waitpid(-1, NULL, WNOHANG)) == -1) && (errno == ECHILD))
                break;
        }
        exit(0);
    }
    printf("[Ghost pid=%d]\n", pid);
}
