#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdio.h>

typedef struct node List;

struct node {
	int pid;
	List* next;
};

List* init_list();
List* add_pid(List* list, int pid);
List* free_list(List* list);
void print_list(List* list);

#endif