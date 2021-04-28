# Arquivo Makefile para compilar os programas que exemplificam
# o uso de threads.
#
# Esse arquivo Makefile foi criado para trabalhar tanto em Sistemas AIX
# quanto Ubuntu e Fedora.
#
# Criado por Prof. Andre' Leon S. Gradvohl, Dr.
# e-mail: gradvohl@ft.unicamp.br
# Ultima versao: Seg 25 Mar 18:42:22 CET 2019
#
# Determinando o ambiente onde estamos
# CC=gcc
# DIRETIVA_OPENMP=-pthread
# DIRETIVAS=$(DIRETIVA_OPENMP)

# #Arquivos
# FONTES=exemploSerial.c exemploParalelo.c
# OBJETOS=$(FONTES:.c=.o)

# #Dependencias de Compilacao
# all: $(OBJETOS)

# exemploSerial.o: exemploSerial.c
# 	@echo "Compilando arquivo: " $<
# 	$(CC) $(DIRETIVAS) $< -o $@ 
# 	@echo "Arquivo " $@ "gerado"

# exemploParalelo.o: exemploParalelo.c
# 	@echo "Compilando arquivo: " $<
# 	$(CC) $(DIRETIVAS) $< -o $@
# 	@echo "Arquivo " $@ "gerado"

# #Limpeza
# clean:
# 	rm -f $(OBJETOS)

all: p1 p2 p3 p4

p1: exemploSerial.o
	gcc exemploSerial.c -o exemploSerial.o

p2: exemploParalelo.o
	gcc -pthread exemploParalelo.c -o exemploParalelo.o

p3: exemploST.o
	gcc exemploST.c -o exemploST.o

p4: exemploPT.o
	gcc -pthread exemploPT.c -o exemploPT.o
