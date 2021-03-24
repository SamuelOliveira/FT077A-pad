# Arquivo Makefile para compilar os programas que exemplificam
# o uso de threads.
#
# Esse arquivo Makefile foi criado para trabalhar tanto em Sistemas AIX
# quanto Ubuntu e Fedora.
#
# Criado por Prof. Andre' Leon S. Gradvohl, Dr.
# e-mail: gradvohl@ft.unicamp.br
# Ultima versao: Sab 30 Jan 2016 12:43:56 BRST
# 
#
# Determinando o ambiente onde estamos
UNAME := $(shell uname)
ifeq ($(UNAME), AIX) #Se o Sistema Operacional for AIX (Cluster Power / IBM)
    CC=xlc
    DIRETIVA_PTHREAD=-lpthread
    DIRETIVA_OPENMP=-qsmp
    DIRETIVAS= -lm $(DIRETIVA_PTHREAD) $(DIRETIVA_OPENMP)
else #Senao deve ser uma distribuicao do Linux
    SO:= $(shell  lsb_release -si)
    CC=gcc
    ifeq ($(SO), Ubuntu) #Se a distribuicao for Ubuntu (Cluster Beowulf).
        DIRETIVA_PTHREAD= -pthread
    else
        DIRETIVA_PTHREAD= -lpthread
    endif
    DIRETIVA_OPENMP=-fopenmp
    DIRETIVAS= -Wall -lm $(DIRETIVA_PTHREAD) $(DIRETIVA_OPENMP)
endif

#Arquivos
FONTES=generateRandomMatrix.c MatrixIO.c
OBJETOS=$(FONTES:.c=.o)

#Dependencias de Compilacao
all: $(OBJETOS)

generateRandomMatrix.o: generateRandomMatrix.c MatrixIO.c MatrixIO.h
	@echo "Compilando arquivo: " $<
ifeq ($(CC), xlc)
	$(CC) MatrixIO.c generateRandomMatrix.c -Wall
	mv a.out $@
else
	$(CC)  MatrixIO.c generateRandomMatrix.c -o $@ -Wall
endif
	@echo "Arquivo " $@ "gerado"

#Limpeza
clean:
	rm -f $(OBJETOS)
