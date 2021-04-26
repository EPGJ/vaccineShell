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


void exec_fg_command(tCommand *cmd) {
	int pid;
	if ((pid = fork()) < 0)
	{
		exit(2); // codigo de erro
	}
	if (pid == 0)
	{	
		struct sigaction sa;
		sa.sa_handler = SIG_IGN;
		if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
			perror("Could not set SIG_IGN handler to default action");

		char **param = get_parameters_arr(cmd);
		if(execvp(cmd->command, param)<0){
			perror("Could not execute command\n");
		}
		exit(0);
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
		// Redireciona entrada (se comando não for o primeiro)
		if (command_id-1 >= 0) {
			if (dup2(fd[command_id-1][READ], STDIN_FILENO) < 0) {
				printf("erro dup entrada\n");
				exit(1);
			}
		}
		// Redireciona saída (se comando não for o último)
		if (command_id < n_commands-1) {
			if (dup2(fd[command_id][WRITE], STDOUT_FILENO) < 0) {
				printf("erro dup saida\n");
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

/*
// Redireciona entrada
		if (command_id-1 >= 0) { 	
			dup2(fd[command_id-1][READ], STDIN_FILENO);
			close(fd[command_id-1][READ]);
		}
		// Redireciona saída
		if (command_id < n_commands-1) {
			dup2(fd[command_id][WRITE], STDOUT_FILENO);
			close(fd[command_id][WRITE]);
		}	
		
		// Fecha outros pipes
		close(fd[0][READ]); 			// fecha leitura do pipe de saída do primeiro comando
		if (n_commands-2 != 0) {
			close(fd[n_commands-2][WRITE]);	// fecha escrita do pipe de entrada do último comando
		}
		for (int i = 0; i < n_commands-2; i++)
        {
			close(fd[i][READ]);
			close(fd[i-1][WRITE]);
			if (i != command_id) {
				close(fd[i-1][READ]);
				close(fd[i][WRITE]);
			}
        }
*/