#include "command.h"

#define READ 0
#define WRITE 1

tCommand treat_command(char *cmd_str)
{ // cmd_str = "comando arg1 ..."
	tCommand cmd;
	cmd.number_parameters = 0;

	// Lê comando
	char *token = strtok(cmd_str, " ");
	strcpy(cmd.command, token);

	// Lê parâmetros
	token = strtok(NULL, " ");
	for (int i = 0; token != NULL && i < QTD_PARAMETERS_MAX; i++)
	{
		strcpy(cmd.parameters[i], token);
		cmd.number_parameters++;
		token = strtok(NULL, " ");
	}

	return cmd;
}

char** get_parameters_arr(tCommand *cmd) {
	int n_param = cmd->number_parameters;
	char **param = malloc((2 + n_param) * sizeof(char *));
	// O primeiro argumento precisa ser o comando
	param[0] = cmd->command;
	for (int i = 1; i <= n_param; i++)
	{
		param[i] = cmd->parameters[i - 1];
	}
	// O último precisa ser NULL
	param[n_param + 1] = NULL;
	
	return param;
}


pid_t exec_fg_command(tCommand *cmd) {
	pid_t pid;
	if ((pid = fork()) < 0)
	{
		exit(2); // codigo de erro
	}
	if (pid == 0)
	{	
		// Vacina processo: processo passa a ignorar os sinais SIGUSR1 e SIGUSR2
		struct sigaction sa;
		sa.sa_handler = SIG_IGN;
		if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
			perror("Could not set SIG_IGN handler to default action");
		// Executa comando
		char **param = get_parameters_arr(cmd);
		if (execvp(cmd->command, param) < 0){
			perror("Could not execute command\n");
			exit(1);
		}
	}
	return pid;
}

pid_t exec_bg_command(tCommand *cmd, int** fd, int command_id, int n_commands) {
	pid_t pid;
	if ((pid = fork()) < 0)
	{
		perror("Erro ao criar processo");
		exit(1); // codigo de erro
	}
	if (pid == 0)
	{	
		// Redireciona entrada (se comando não for o primeiro)
		if (command_id-1 >= 0) {
			if (dup2(fd[command_id-1][READ], STDIN_FILENO) < 0) {
				perror("Erro no redirecionamento de entrada\n");
				exit(1);
			}
		}
		// Redireciona saída (se comando não for o último)
		if (command_id < n_commands-1) {
			if (dup2(fd[command_id][WRITE], STDOUT_FILENO) < 0) {
				printf("Erro no redirecionamento de saida\n");
				exit(1);
			}
		}
		// Fecha file descriptors
		for (int i = 0; i < n_commands-1; i++)
        {
			close(fd[i][READ]);
			close(fd[i][WRITE]);
        }
		// Executa comando
		char **param = get_parameters_arr(cmd);

		if (execvp(cmd->command, param) < 0) {
			printf("Could not execute command '%s'\n", cmd->command);
			exit(1);
		}
	}
	return pid; // retorna pid do processo filho criado
}

