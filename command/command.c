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

void exec_command(tCommand command, int in, int out)
{
	int pid;
	if ((pid = fork()) < 0)
	{
		printf("Could not execute command\n");
	}
	if (pid == 0)
	{
		//TODO: faz dup para redirecionar I/O primeiro se for preciso
		//TODO: vacina se for fg

		int n_param = command.number_parameters;
		char **param = malloc((2 + n_param) * sizeof(char *));
		param[0] = command.command;
		for (int i = 1; i <= n_param; i++)
		{
			param[i] = command.parameters[i - 1];
		}
		param[n_param + 1] = NULL;

		execvp(command.command, param);

		printf("Could not execute command\n");
	}
}

void print_command(tCommand command)
{
	printf("command='%s' ", command.command);

	int i = 0, qtd_parameters = command.number_parameters;
	while (i < qtd_parameters)
	{
		printf("arg[%d]='%s' ", i, command.parameters[i]);
		i++;
	}
	printf("\n");
}