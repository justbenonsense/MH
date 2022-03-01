# Autor: Carlota Valdivia Manzano
# Curso: 2020/21

PROJECT=Practica1-MH
BIN=./bin
SRC=./src
IN=./input
OUT=./output
ZIP=./zip
OPT=-Wall -O2 # Opciones de compilación ( -Wall muestra todas las advertencias, -O2 para optimizacion)


# ********************* Macros ************************* #
all: $(BIN)/greedy $(BIN)/busquedaLocal 

execute_all: $(BIN)/greedy $(BIN)/busquedaLocal 
	./execute.sh

execute_greedy: $(BIN)/greedy 
	./executegreedy.sh

execute_bl: $(BIN)/busquedaLocal 
	./executeBusquedaLocal.sh


# ******************** Compilación  ********************* #
$(BIN)/greedy :
	g++ $(OPT) $(SRC)/greedy.cpp -o $(BIN)/greedy

$(BIN)/busquedaLocal :
	g++ $(OPT) $(SRC)/busquedaLocal.cpp -o $(BIN)/busquedaLocal

# ************ Compresión de los archivos *************** #

zip: zipdir | $(BIN)/greedy $(BIN)/busquedaLocal
	rm -rf zip/*
	rm -rf bin/*
	zip -r zip/$(PROJECT).zip *

zipdir:
	@-mkdir -p zip

# ******************** Limpieza  *********************** #
clean:
	rm -f $(BIN)/*

