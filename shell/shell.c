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

void handle_sigusr_vsh(int sig)
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

    while (1)
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
    if (len == wspace_count) return;

    // Separa e trata comandos digitados
    char *token, *rest;
    const char symbol[2] = "|";

    token = strtok_r(line, symbol, &rest);
    for (int i = 0; token != NULL && i < NUMBER_COMMANDS_MAX; i++)
    {
        shell->commands[i] = treat_command(trim(token));
        shell->number_commands++;
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
            liberamoita(shell);
            return;
        }
        if (strcmp(cmd->command, "armageddon") == 0)
        {
            armageddon(shell);
            return;
        }
        exec_fg_command(cmd);
        wait(NULL);//waitpid(pid, NULL, 0);
        return;
    }
    exec_background_processes(shell);
}

void exec_background_processes(tShell *shell)
{
    pid_t pid = fork(); //cria processo ghost
    if (pid == -1){
        exit(1); 
    }
    if (pid == 0) {
        pid_t sid = setsid(); //muda processo ghost de sessão

        int i, n_commands = shell->number_commands;

        // Cria n_commands-1 pipes
        int **fd = malloc((n_commands - 1) * sizeof(int *));
        for (i = 0; i < n_commands; i++) {
            fd[i] = malloc(2 * sizeof(int));
            pipe(fd[i]);
        }
        // Executa comandos
        for (i = 0; i < n_commands; i++)
        {
            pid_t pid_c = exec_bg_command(&shell->commands[i], fd, i, n_commands);
        }
        // Fecha pipes
        for (i = 0; i < n_commands - 1; i++)
        {
            close(fd[i][0]);
            close(fd[i][1]);
            free(fd[i]);  
        }
        free(fd);
        // Espera filhos terminarem a execução
        int status;
        while (1)
        {
            if (((waitpid(-1, &status, WNOHANG)) == -1) && (errno == ECHILD))
                break; 

            if(status == 10 || status == 12){
                handle_sigusr_background();
            } 
        }

        exit(0); //encerra execução do processo ghost
    }
}

/**
 * Faz com que o shell libere todos os seus descendentes (diretos e indiretos,
 * isto é, filhos, netos, bisnetos, etc.) que estejam no estado “Zombie” antes
 * de exibir um novo prompt.
*/
void liberamoita(tShell* shell) {
    int status;
    while(waitpid(-1, &status, WNOHANG) > 0);
}

/**
 * Termina a operação do shell, mas antes disso, ele deve matar todos os seus 
 * descendentes (diretos e indiretos, isto é, filhos, netos, bisnetos, etc.) 
 * que ainda estejam rodando.
*/
void armageddon(tShell* shell) {
    printf("Executa armageddon\n"); // TODO: implementar comando interno
    exit(0);
}


void handle_sigusr_background(){
    
    pid_t group_id = getpgid(getpid());
    killpg(group_id, SIGKILL);

}