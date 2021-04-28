#include "list.h"

List* init_list() {
	return NULL;
}

List* add_pid(List* list, int pid) {
	List* new = malloc(sizeof(List));
	new->pid = pid;
	new->next = list;
	return new;
}

List* free_list(List* list) {
	List* aux;
	for (List* p = list; p != NULL; ) {
		aux = p;
		p = p->next;
		free(aux);
	}
	return NULL;
}

void print_list(List* list) {
	for (List* p = list; p != NULL; p = p->next) {
		printf("[PID=%d]->", p->pid);
	}
	printf("NULL\n");
}