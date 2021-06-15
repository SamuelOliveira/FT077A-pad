# mpi_projeto: mpi_projeto.c

# 	mpicc mpi_projeto.c -o mpi_projeto.o

all: mpi_projeto

mpi_projeto: mpi_projeto.o consts.h utils.h serial.h
	gcc mpi_projeto.c utils.c serial.c -o mpi_projeto.o -lm