# Autor: Carlota Valdivia Manzano
# Curso: 2020/21

PROJECT=Practica2-MH
BIN=./bin
SRC=./src
IN=./input
OUT=./output
ZIP=./zip
OPT=-Wall -O2 # Opciones de compilación ( -Wall muestra todas las advertencias, -O2 para optimizacion)


# ********************* Macros ************************* #
all: $(BIN)/AGGposicion $(BIN)/AGGuniforme $(BIN)/AGEposicion $(BIN)/AGEuniforme $(BIN)/AM-(10,1.0) $(BIN)/AM-(10,0.1) $(BIN)/AM-(10,0.1mej)

execute_all: $(BIN)/AGGposicion $(BIN)/AGGuniforme $(BIN)/AGEposicion $(BIN)/AGEuniforme $(BIN)/AM-(10,1.0) $(BIN)/AM-(10,0.1) $(BIN)/AM-(10,0.1mej) 
	./execute.sh

execute_AGGposicion: $(BIN)/AGGposicion 
	./executeAGGposicion.sh

execute_AGGuniforme: $(BIN)/AGGuniforme 
	./executeAGGuniforme.sh

execute_AGEposicion: $(BIN)/AGEposicion 
	./executeAGEposicion.sh

execute_AGEuniforme: $(BIN)/AGEuniforme 
	./executeAGEuniforme.sh

execute_AM-(10,1.0): $(BIN)/AM1 
	./executeAM-\(10\,1.0\)).sh

execute_AM-(10,0.1): $(BIN)/AM01 
	./executeAM-\(10\,0.1\)).sh

execute_AM-(10,0.1mej): $(BIN)/AM01mej 
	./executeAM-\(10\,0.1mej\)).sh


# ******************** Compilación  ********************* #
$(BIN)/AGGposicion :
	g++ $(OPT) $(SRC)/AGGposicion.cpp -o $(BIN)/AGGposicion

$(BIN)/AGGuniforme :
	g++ $(OPT) $(SRC)/AGGuniforme.cpp -o $(BIN)/AGGuniforme

$(BIN)/AGEposicion :
	g++ $(OPT) $(SRC)/AGEposicion.cpp -o $(BIN)/AGEposicion

$(BIN)/AGEuniforme :
	g++ $(OPT) $(SRC)/AGEuniforme.cpp -o $(BIN)/AGEuniforme

$(BIN)/AM-(10,1.0) :
	g++ $(OPT) $(SRC)/AM-\(10\,1.0\).cpp -o $(BIN)/AM1

$(BIN)/AM-(10,0.1) :
	g++ $(OPT) $(SRC)/AM-\(10\,0.1\).cpp -o $(BIN)/AM01

$(BIN)/AM-(10,0.1mej) :
	g++ $(OPT) $(SRC)/AM-\(10\,0.1mej\).cpp -o $(BIN)/AM01mej


# ************ Compresión de los archivos *************** #

zip: zipdir | $(BIN)/AGGposicion $(BIN)/AGGuniforme $(BIN)/AGEposicion $(BIN)/AGEuniforme $(BIN)/AM-(10,1.0) $(BIN)/AM-(10,0.1) $(BIN)/AM-(10,0.1mej)
	rm -rf zip/*
	rm -rf bin/*
	zip -r zip/$(PROJECT).zip *

zipdir:
	@-mkdir -p zip

# ******************** Limpieza  *********************** #
clean:
	rm -f $(BIN)/*

