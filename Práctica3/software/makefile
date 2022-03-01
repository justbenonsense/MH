# Autor: Carlota Valdivia Manzano
# Curso: 2020/21

PROJECT=Practica3-MH
BIN=./bin
SRC=./src
IN=./input
OUT=./output
ZIP=./zip
OPT=-Wall -O2 # Opciones de compilación ( -Wall muestra todas las advertencias, -O2 para optimizacion)


# ********************* Macros ************************* #
all: $(BIN)/ES $(BIN)/BMB $(BIN)/ILS $(BIN)/ILS-ES $(BIN)/ES-geometrica $(BIN)/ILSrep

execute_all: $(BIN)/ES $(BIN)/BMB $(BIN)/ILS $(BIN)/ILS-ES $(BIN)/ES-geometrica $(BIN)/ILSrep
	./execute.sh

execute_ES: $(BIN)/ES 
	./executeES.sh

execute_BMB: $(BIN)/BMB 
	./executeBMB.sh

execute_ILS: $(BIN)/ILS 
	./executeILS.sh

execute_ILS-ES: $(BIN)/ILS-ES 
	./executeILS-ES.sh

execute_ES-geometrica: $(BIN)/ES-geometrica 
	./executeES-geometrica.sh

execute_ILSrep: $(BIN)/ILSrep
	./executeILSrep.sh


# ******************** Compilación  ********************* #

$(BIN)/ES :
	g++ $(OPT) $(SRC)/ES.cpp -o $(BIN)/ES

$(BIN)/BMB :
	g++ $(OPT) $(SRC)/BMB.cpp -o $(BIN)/BMB

$(BIN)/ILS :
	g++ $(OPT) $(SRC)/ILS.cpp -o $(BIN)/ILS

$(BIN)/ILS-ES :
	g++ $(OPT) $(SRC)/ILS-ES.cpp -o $(BIN)/ILS-ES

$(BIN)/ES-geometrica :
	g++ $(OPT) $(SRC)/ES-geometrica.cpp -o $(BIN)/ES-geometrica

$(BIN)/ILSrep :
	g++ $(OPT) $(SRC)/ILSrep.cpp -o $(BIN)/ILSrep


# ************ Compresión de los archivos *************** #

zip: zipdir | $(BIN)/ES $(BIN)/BMB $(BIN)/ILS $(BIN)/ILS-ES $(BIN)/ES-geometrica $(BIN)/ILSrep
	rm -rf zip/*
	rm -rf bin/*
	zip -r zip/$(PROJECT).zip *

zipdir:
	@-mkdir -p zip

# ******************** Limpieza  *********************** #
clean:
	rm -f $(BIN)/*

