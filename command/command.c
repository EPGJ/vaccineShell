#include "command.h"

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


void exec_fg_command(tCommand *cmd) {
	int pid;
	if ((pid = fork()) < 0)
	{
		printf("Could not execute command\n");
		exit(2); // codigo de erro
	}
	if (pid == 0)
	{	
		struct sigaction sa;
		sa.sa_handler = SIG_IGN;
		if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
			perror("Could not set SIG_IGN handler to default action");

		char **param = get_parameters_arr(cmd);

		execvp(cmd->command, param);
		printf("Could not execute command\n");
	} else {
		wait(NULL); // vsh espera execução do processo fg criado
	}
}

pid_t exec_bg_command(tCommand *cmd, int** fd, int command_id, int n_commands) {
	pid_t pid;
	if ((pid = fork()) < 0)
	{
		printf("Could not execute command\n");
		exit(2); // codigo de erro
	}
	if (pid == 0)
	{	
		// //Faz dup para redirecionar I/O
		// dup2(STDIN_FILENO, in);
		// dup2(STDOUT_FILENO, out);
		char **param = get_parameters_arr(cmd);

		execvp(cmd->command, param);
		printf("Could not execute command '%s'\n", cmd->command);
		raise(SIGKILL);
	}
	return pid; // retorna pid do processo filho criado
}

void print_command(tCommand *cmd)
{
	printf("command='%s' ", cmd->command);

	int i = 0, qtd_parameters = cmd->number_parameters;
	while (i < qtd_parameters)
	{
		printf("arg[%d]='%s' ", i, cmd->parameters[i]);
		i++;
	}
	printf("\n");
}