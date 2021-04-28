# Makefile

all: compile

compile: main.o shell.o command.o utils.o list.o
	gcc -o vsh main.o shell.o command.o utils.o list.o

main.o: main.c ./shell/shell.h
	gcc -o main.o -c main.c

shell.o: ./shell/shell.c
	gcc -o shell.o -c ./shell/shell.c

command.o: ./command/command.c
	gcc -o command.o -c ./command/command.c

utils.o: ./utils/utils.c
	gcc -o utils.o -c ./utils/utils.c

list.o: ./utils/list.c
	gcc -o list.o -c ./utils/list.c

clean:
	rm -rf *.o *~ vsh