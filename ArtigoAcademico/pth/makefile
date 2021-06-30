#Compilador
COMPILADOR=gcc
DIRETIVA_OPENMP=-pthread
#Nome do seu executavel
NOME_EXECUTAVEL=compress
#Diretorio dos arquivos binarios
BIN=./
#Diretorio dos arquivos .h e .hpp
INCLUDE=../Headers
#Diretorio dos arquivos-objetos
OBJ=./
#Diretorio dos arquivos .c e .cpp
SRC=./
#Diretorio dos arquivos de bibliotecas
LIB=./

#Para otimizar e mostrar mais avisos
FLAGS= -O3 -Wall
#Para encontrar as bibliotecas utilizadas(em "-lm", apenas um exemplo, caso seu compilador nao faca isso por voce)
LIBS= -lm -L $(LIB)

#Pega todos arquivos .cpp e muda os nomes para .o
#Fontes .c
FONTES=$(wildcard $(SRC)/*.c)
#Retirar prefixo e sufixo
OBJLIMPAR=$(notdir $(basename $(FONTES)))
#Adicionar novo prefixo e sufixo
OBJETOS=$(addprefix $(OBJ)/, $(addsuffix .o, $(OBJLIMPAR)))

.PHONY: all cleanObjetos clean tar

all: compilar $(NOME_EXECUTAVEL)

#Arquivos .o do projeto
compilar: $(OBJETOS)

#Compilar e criar os arquivos-objetos
$(OBJ)/%.o: $(SRC)/%.cpp $(INCLUDE)/%.hpp
	$(COMPILADOR) $(FLAGS) -c $< -I $(INCLUDE) -o $@

#Linkar e criar o executavel
$(NOME_EXECUTAVEL): $(OBJETOS)
	$(COMPILADOR) $(DIRETIVAS) $(FLAGS) $(OBJETOS) $(LIBS) -o $(BIN)/$@

#Executar programa
run:
	$(BIN)/$(NOME_EXECUTAVEL)

#Limpar arquivos .o
cleanObjetos:
	rm -f $(OBJ)/*.o

#Limpar executavel
clean:
	rm -f $(BIN)/$(NOME_EXECUTAVEL)

