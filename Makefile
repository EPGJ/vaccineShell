# Makefile

all: compile

compile: main.o shell.o command.o
	gcc -o vsh main.o shell.o command.o

main.o: main.c ./shell/shell.h
	gcc -o main.o -c main.c

shell.o: ./shell/shell.c
	gcc -o shell.o -c ./shell/shell.c

command.o: ./command/command.c
	gcc -o command.o -c ./command/command.c

clean:
	rm -rf *.o *~ vsh