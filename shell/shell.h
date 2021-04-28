#ifndef SHELL_H
#define SHELL_H
#define USR1_SIGNAL 10
#define USR2_SIGNAL 12

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include "../command/command.h"
#include "../utils/utils.h"
#include "../utils/list.h"


#define NUMBER_COMMANDS_MAX 5

typedef struct  {
    tCommand commands[NUMBER_COMMANDS_MAX];
    int number_commands;
    List* session_leaders;
} tShell;

/* Lê os comandos digitados;
 * inputs: ponteiro do tipo tShell;
 * output: nenhuma;
 * pre-condicao: ponteiro tShell válido;
 * pos-condicao: comandos e parâmetros lidos.
 */
void read_commands(tShell *); 

/* Limpa tela;
 * inputs: nenhum;
 * output: nenhum;
 * pre-condicao: nenhuma
 * pos-condicao: tela limpa.
 */
void clean_screen();

/* Imprime vsh> no teminal;
 * inputs: nenhum;
 * output: nenhum;
 * pre-condicao: nenhuma;
 * pos-condicao: vsh> digitado.
 */

void type_prompt();

/* Tatador de sinais da vsh;
 * inputs: nenhum;
 * output: nenhum;
 * pre-condicao: nenhuma;
 * pos-condicao: trata os sinais SIGUSR1 e SIGUSR2 e imprime o jacaré.
 */
void handle_sigusr_vsh();

/* Realiza o tratamento de todos os processos em background de uma mesma sessão, 
   matando os mesmos caso recebam os sinais SIGUSR1 e SIGUSR2;
 * inputs: nenhum;
 * output: nenhum;
 * pre-condicao: nehuma;
 * pos-condicao: todos os processos em background da sessão (caso existam) são finalizados.
 */
void handle_sigusr_background();

/* Executa os processos, caso haja algum comando, diferenciando entre foreground e background;
 * inputs: nenhum;
 * output: nenhum;
 * pre-condicao:  ponteiro do tipo tShell valido;
 * pos-condicao: o processo é executado.
 */
void exec_process(tShell *);

/* Executa todos os comandos salvos na struct do tipo tShell passada como parâmetro.
   Todos os processos são criados em background e em uma sessão diferente da do processo 
   que fez a chamada do subprograma;
 * inputs: ponteiro do tipo tShell;
 * output: nenhum;
 * pre-condicao: mais de um comando salvo na estrutura do tipo tShell apontada;
 * pos-condicao: comandos executados em background em uma sessão diferente, e o id dessa 
   sessão é salvo em uma lista dentro da struct passada como parâmetro.
 */
void exec_background_processes(tShell *);

/* Faz com que o shell libere todos os seus descendentes (diretos e indiretos,
   isto é, filhos, netos, bisnetos, etc.) que estejam no estado “Zombie” antes
   de exibir um novo prompt;
 * inputs: ponteiro do tipo tShell;
 * output: nenhum;
 * pre-condicao: ponteiro do tipo tShell valido;
 * pos-condicao: todos os processos zombies são liberados.
 */
void liberamoita(tShell* );

/* Termina a operação do shell, mas antes disso, ele deve matar todos os seus 
   descendentes (diretos e indiretos, isto é, filhos, netos, bisnetos, etc.) 
   que ainda estejam rodando;
 * inputs: ponteiro do tipo tShell;
 * output: nenhum;
 * pre-condicao: ponteiro para shell válido;
 * pos-condicao: o shell e todos os seus descendentes são finalizados.
 */
void armageddon(tShell* );

#endif