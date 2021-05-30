all: p1

p1: acc_projeto.o consts.h utils.h serial.h acc_paralelo.h
	gcc -fopenacc acc_projeto.c utils.c serial.c acc_paralelo.c -o acc_projeto.o -lm