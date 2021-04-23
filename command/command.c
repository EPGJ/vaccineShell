#include "command.h"


tCommand treat_command(char* cmd_str) { // cmd_str = "comando arg1 ..."
	tCommand cmd;
	cmd.number_parameters = 0;

	// Lê comando
	char *token = strtok(cmd_str, " ");
	strcpy(cmd.command, token);

	// Lê parâmetros
	token = strtok(NULL, " ");
	for (int i = 0; token != NULL; i++) {
		strcpy(cmd.parameters[i], token);
		cmd.number_parameters++;
		token = strtok(NULL, " ");
	}
 	return cmd;
}

void print_command(tCommand command) {
	printf("command='%s' ", command.command);

	int i = 0, qtd_parameters = command.number_parameters;
	while (i < qtd_parameters) {
		printf("arg[%d]='%s' ", i, command.parameters[i]);
		i++;
	}
	printf("\n");
}