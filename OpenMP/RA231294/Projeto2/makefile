all: p1

# https://stackoverflow.com/questions/15440183/makefile-include-header
p1: omp_projeto.o consts.h utils.h serial.h omp_paralelo.h
	gcc -fopenmp omp_projeto.c utils.c serial.c omp_paralelo.c -o omp_projeto.o -lm
