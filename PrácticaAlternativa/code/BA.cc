//////////////////////////////////////////////////////////////////
// Práctica Alternativa. Metaheurísticas.
// Bees Algorithm
//
// Carlota Valdivia Manzano
// NOTA: compilar g++ -g BA.cpp -o BA
/////////////////////////////////////////////////////////////////

extern "C" {
#include "cec17.h"
}
#include "cec17.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <chrono>
#include <vector>
#include <string>
#include <set>
#include <utility>
#include <algorithm>
#include <cstdlib>
#include <math.h>
#include <random>
#include <time.h>

using namespace std;


/*****************************************************************/
// Constantes y variables globales
/*****************************************************************/

const int archivos = 30;            // Número de archivos que ejecutaremos
const int ejecuciones = 10;         // Número de ejecuciones de cada archivo

const int dimension = 10;           // Dimensión del espacio, R^10 o R^30
const int num_abejas = 30;          // Nº de abejas de la población
const int num_sitiosSelec = 15;     // Nº de sitios seleccionados
const int num_mejorSitios = 7;      // Nº de los mejores sitios seleccionados
const int num_abejasMejores = 20;   // Nº de abejas recutadas para los mejores sitios
const int num_abejasOtros = 10;     // Nº de abejas reclutadas para el resto de 
const double alpha = 0.95;          // Constante de encogimiento del radio de las zonas
double tam_zona = 0.1;           // Tamaño inicial de la zona

const int max_it = dimension * 10000;    // Nº máximo de iteraciones

const double varMax = 100;             // Valor máximo del dominio
const double varMin = -100;            // Valor mínimo del dominio

vector<double> min(dimension, varMin);
vector<double> max(dimension, varMax);


/*****************************************************************/
// Clase de representación de una abeja 
/*****************************************************************/
class Bee {
    
    /*************************************************************/
    // Variables
    /*************************************************************/

    vector<double> pos;          // Posición de la abeja
    double calidad;              // Valor de la calidad de la zona


    public:

        /*************************************************************/
        // Métodos
        /*************************************************************/

        // Constructor sin parámetros
        Bee(){
            calidad = 0;
        }

        // Constructor con parámetros
        Bee(vector<double> posicion){
            pos = posicion;
            calidad = cec17_fitness(&pos[0]);
        }

        // Devuelve la calidad de la abeja
        double getCalidad(){
            return calidad;
        }

        // Devuelve la posición de la abeja
        vector<double> getPosicion(){
            return pos;
        }

        // Añade la calidad de la abeja
        void setCalidad(){
            calidad = cec17_fitness(&pos[0]);
        }

        // Añade la posición de la abeja
        void setPosicion(vector<double> posicion){
            pos = posicion;
        }

};


/*****************************************************************/
// Estructura de representación de una población de abejas
/*****************************************************************/
struct poblacion {

    int tam;                      // Tamaño de la población
    vector<Bee> bees;             // Vector de abejas
    int bestBee;                  // Índice de la mejor abeja
    float bestFit;                // Contribución de la mejor abeja 
};

/*****************************************************************/
// Distribución Uniforme
/*****************************************************************/
static default_random_engine generator(time(NULL));         // Semilla para la distribución

double uniformDistribution(double min, double max){

    uniform_real_distribution<double> distribution(min, max);

    return distribution(generator);
}

/*****************************************************************/
// Criterio de ordenación de abejas
// Se ordena según la calidad de forma ascendente
/*****************************************************************/
bool criterioOrdenacion(Bee & b1, Bee & b2) {
    return b1.getCalidad() < b2.getCalidad();
}


/*****************************************************************/
// Función de ligero movimiento de una abeja
/*****************************************************************/
vector<double> movimiento(Bee & b) {
    
    vector<double> nueva_pos = b.getPosicion();   // Nueva posición de la abeja
    
    // Generamos un número aleatorio para elegir que componente de la dimensión variar
    int aleatorio = rand() % dimension;

    // Generamos la nueva posición de la abeja
    nueva_pos[aleatorio] += uniformDistribution(-tam_zona,tam_zona); 

    return nueva_pos;
}


/*****************************************************************/
// Función para generar una población aleatoria
/*****************************************************************/
void poblacionAleatoria(poblacion & p){

    // Establecemos el tamaño de la población
    p.tam = num_abejas;
    p.bestFit = 0;

    // Vamos generando las abejas
    for(int i = 0; i < num_abejas; i++){        
        
        vector<double> pos(dimension);

        // Determinamos de forma aleatoria su posición
        for(int j = 0; j < dimension; j++){
            pos[j] = uniformDistribution(varMin,varMax);
        }
        
        // La añadimos al vector de abejas
        Bee nuevaAbeja = Bee(pos);
        p.bees.push_back(nuevaAbeja);
    }

    // Ordenamos la poblacion por contribución de forma ascendente
    sort(p.bees.begin(), p.bees.end(), criterioOrdenacion);

    // Seleccionamos la mejor abeja
    p.bestBee = 0;
    p.bestFit = p.bees[0].getCalidad();
}


/*****************************************************************/
// Bees Algorithm 
/*****************************************************************/
vector<double> BA(const char * algoritmo, int file){
    cec17_init(algoritmo,file,dimension);
    // Creamos la población de abejas y la inicializamos
    poblacion p;
    poblacionAleatoria(p);
    int num_iteraciones = num_abejas;     // Contador

    Bee newBee = Bee();
    Bee bestBee = Bee();

    vector<double> nueva_pos;

    while (num_iteraciones < max_it){
        // Mejores sitios seleccionados
        for (int i = 0; i < num_mejorSitios; i++){

            for (int j = 0; j < num_abejasMejores; j++){
                // Creamos una nueva abeja ligeramente movida
                nueva_pos = movimiento(p.bees[i]);
                newBee.setPosicion(nueva_pos);
                newBee.setCalidad();
                // Vemos si es la mejor
                if (bestBee.getCalidad() < newBee.getCalidad()){
                    bestBee = newBee;
                }

                num_iteraciones += 1;
            }

            // Vemos es mejor que la mejor de la población
            if (p.bestFit < bestBee.getCalidad()){
                p.bees[p.bestBee] = bestBee;
            }
        }

        // Sitios seleccionados que no son los mejores
        for (int i = num_mejorSitios; i < num_sitiosSelec; i++){

            for (int j = 0; j < num_abejasOtros; j++){

                // Creamos una nueva abeja ligeramente movida
                newBee.setPosicion(movimiento(p.bees[i]));
                newBee.setCalidad();

                // Vemos si es la mejor
                if (bestBee.getCalidad() < newBee.getCalidad()){
                    bestBee = newBee;
                }

                num_iteraciones += 1;
            }

            // Vemos es mejor que la mejor de la población
            if (p.bestFit < bestBee.getCalidad()){
                p.bees[p.bestBee] = bestBee;
            }
        }

        // Sitios no seleccionados
        for (int i = num_sitiosSelec; i < num_abejas; i++){
            vector<double> pos(dimension);

            // Determinamos de forma aleatoria su posición
            for(int j = 0; j < dimension; j++){
                pos[j] = uniformDistribution(varMin,varMax);
            }
            
            // La añadimos al vector de abejas
            p.bees[i] = Bee(pos);

            num_iteraciones++;
        }

        // Ordenamos la poblacion por contribución de forma ascendente
        sort(p.bees.begin(), p.bees.end(), criterioOrdenacion);

        // Seleccionamos la mejor abeja
        p.bestBee = 0;
        p.bestFit = p.bees[0].getCalidad();

        // Reducimos el radio de las zonas
        tam_zona *= alpha;
    }

    return p.bees[0].getPosicion();
}


int main(int argc, char *argv[]){
    // Inicializamos la semilla
    srand(time(NULL));

    vector<double> solucion;         // Vector con la solución
    double fitness;                  // Fitness de la solución

    // Vamos a ejecutar un número de archivos, y cada uno un determinado número de ejecuciones
    for (int i = 1; i <= archivos ; i++){

        for (int j = 1; j <= ejecuciones; j++){

            solucion = BA("BA", i);
            fitness = cec17_fitness(&solucion[0]);
            cout << "Fitness[F" << i <<"]: " << scientific << cec17_error(fitness) << endl;
        }
    }

    return 0;
}