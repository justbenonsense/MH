//////////////////////////////////////////////////////////////////
// Práctica 2. Metaheurísticas.
// Problema de la Máxima Diversidad (MDP)
// Algoritmo Genético Estacionario para el MDP 
// (Operador de cruce basado en posición)
//
// Carlota Valdivia Manzano
// NOTA: compilar g++ -g AGEposicion.cpp -o AGEposicion
//       ejecutar ./AGEposicion archivo.txt semilla
/////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <chrono>
#include <limits>
#include <algorithm>    

using namespace std;

/*****************************************************************/
// Constantes y variables globales
/*****************************************************************/

const int max_it = 100000;          // Nº máximo de evaluaciones de la función objetivo
const int num_cromosomas = 50;      // Nº de cromosomas de la población
const float prob_cruce = 0.7;       // Probabilidad de cruce de dos individuos
int num_iteraciones = 0;            // Nº de evaluaciones actuales de la función objetivo


/*****************************************************************/
// Estructura de representación de una solución (cromosoma)
/*****************************************************************/
struct solucion {

    vector<int> sel;        // Vector de 0s y 1s (1: gen seleccionado, 0: gen no seleccionado)
    bool actualizada;       // Indica si tenemos actualizada su contribución
    float contribucion;     // Valor de la contribución de la solución
};


/*****************************************************************/
// Estructura de representación de una población
/*****************************************************************/
struct poblacion {

    int tam;                        // Tamaño de la población
    vector<solucion> C;             // Vector de soluciones (cromosomas) 
};


/*****************************************************************/
// Criterio de ordenación de soluciones
// Se ordena según la contribución de forma descendiente
/*****************************************************************/
bool criterioOrdenacion(solucion & s1, solucion & s2) {
  return s1.contribucion > s2.contribucion;
}

/*****************************************************************/
// Imprimir una solución
/*****************************************************************/
void imprimirSolucion(solucion & s){

    cout << "[ ";

    for(unsigned int i=0; i < s.sel.size(); i++){

        if ( i + 1 == s.sel.size())
            cout << s.sel[i] << "]"; 
        else
            cout << s.sel[i] << ", "; 
    }

    cout << endl << endl;
}


/*****************************************************************/
// Imprimir una población
/*****************************************************************/
void imprimirPoblacion(poblacion & p){

    for (int i = 0; i < p.tam; i++){
        
       imprimirSolucion(p.C[i]);        
        cout << endl;
    }
}


/*****************************************************************/
// Función para imprimir una matriz.
/*****************************************************************/
void imprimirMatriz(vector<vector<float> > & matriz){

    for(unsigned int i=0; i < matriz.size(); i++){

        for(unsigned int j=0; j < matriz[i].size(); j++){

            cout << " " << matriz[i][j];
        }
        
        cout << endl;
    }
}


/*****************************************************************/
// Función para calcular la contribución de una solución
/*****************************************************************/
void contribucion(solucion & s, vector<vector<float> > & matriz){

    // Reestablecemos la contribución
    s.contribucion = 0;

    // Pasamos a codificación de enteros
    vector<int> elegidos;

    for (unsigned i = 0; i < s.sel.size(); i++){

        // Añadimos aquellos genes que si han sido seleccionados
        if ( s.sel[i] == 1 ){
            elegidos.push_back(i);
        }
    }

    // Calculamos la contribución a partir de la codificación de enteros
    for (vector<int>::iterator it1 = elegidos.begin(); it1 != elegidos.end(); it1++){

        for (vector<int>::iterator it2 = it1; it2 != elegidos.end(); it2++){

            if ( (*it1) < (*it2) ){

                s.contribucion += matriz[(*it1)][(*it2)];
            }
            else {

                s.contribucion += matriz[(*it2)][(*it1)];
            }
        }     
    }

    // Señalamos que hemos actualizado la contribución
    s.actualizada = true;

    // Contabilizamos una evaluación de la función objetivo
    num_iteraciones++;
}


/*****************************************************************/
// Función para generar una solución aleatoria
/*****************************************************************/
void solucionAletoria(int m, solucion & s, vector<vector<float> > & matriz){

    int n = matriz[0].size();
    int aleatorio = 0;
    int cont = 0;

    // Rellenamos con ceros el vector solución
    s.sel = vector<int> (n, 0);

    while (cont < m){

        // Calculamos un nº aleatorio
        aleatorio = rand()%n;

        // Si no lo hemos seleccionado todavía
        if (s.sel[aleatorio] == 0){

            // Lo seleccionamos
            s.sel[aleatorio] = 1;
            cont++;
        }
    }

    // Calculamos la contribución de la solución
    contribucion(s,matriz);
}


/*****************************************************************/
// Función para generar una población aleatoria
/*****************************************************************/
void poblacionAleatoria(int m, poblacion & p, vector<vector<float> > & matriz){

    // Establecemos el tamaño de la población
    p.tam = num_cromosomas;
    p.C.resize(p.tam);

    // Calculamos las soluciones aleatorias
    for (int i = 0; i < p.tam; i++){
       solucionAletoria(m,p.C[i],matriz);
    }

    // Ordenamos la poblacion por contribución de forma descendente
    sort(p.C.begin(), p.C.end(), criterioOrdenacion);
}


/*****************************************************************/
// Operador de Selección de los padres de la población actual
// Usamos el torneo binario
/*****************************************************************/
int seleccion(poblacion & p){

    int aleatorio1 = 0; 
    int aleatorio2 = 0;

    // Repetimos mientras los dos nº aleatorios sean iguales
    do{
        // Generamos dos números aleatorios
        aleatorio1 = rand()%p.tam;
        aleatorio2 = rand()%p.tam;

    } while(aleatorio1 == aleatorio2);

    // Nos quedamos con aquel de mayor contribución
    int seleccionado = aleatorio1;

    if (p.C[aleatorio1].contribucion < p.C[aleatorio2].contribucion){
        seleccionado = aleatorio2;
    }

    return seleccionado;
}


/*****************************************************************/
// Función para ordenar aleatoriamente los restos de un cruce
/*****************************************************************/
void restosCruce(vector<int> & restos1, vector<int> & restos2){

    random_shuffle(restos1.begin(),restos1.end());
    random_shuffle(restos2.begin(),restos2.end());
}

/*****************************************************************/
// Operador de Cruce basado en posición
/*****************************************************************/
void crucePosicion(int pos, poblacion & pPadres){

    int tam = pPadres.C[pos].sel.size();

    // Creamos dos vectores para guardar los restos del padre1
    vector<int> restos1, restos2;

    // Creamos dos soluciones para los hijos
    solucion hijo1, hijo2;
    hijo1.sel = vector<int> (tam,-1);
    hijo2.sel = vector<int> (tam,-1);

    for (int i = 0; i < tam; i++){

        // Vemos si el gen es el mismo en ambos padres
        if (pPadres.C[pos].sel[i] == pPadres.C[pos+1].sel[i]){
            hijo1.sel[i] = pPadres.C[pos].sel[i];
            hijo2.sel[i] = pPadres.C[pos].sel[i];
        }
        // Sino lo guardamos el gen del padre1 en los restos
        else{
            restos1.push_back(pPadres.C[pos].sel[i]);
            restos2.push_back(pPadres.C[pos].sel[i]);      
        }
    }

    // Aleatorizamos los restos de un padre
    restosCruce(restos1,restos2);

    unsigned cont = 0;
    
    // Sustuimos los restos aleatorios
    for(int i = 0; i < tam && cont < restos1.size(); i++){
        
        // Si no está asignado todavía
        if (hijo1.sel[i] == -1){
            hijo1.sel[i] = restos1[cont];
            hijo2.sel[i] = restos2[cont];
            cont++;
        }
    }

    // Cambiamos los padres por los hijos
    pPadres.C[pos] = hijo1;
    pPadres.C[pos+1] = hijo2;

    // Señalamos que tenemos que actualizar las contribuciones
    pPadres.C[pos].actualizada = false;
    pPadres.C[pos+1].actualizada = false;
}


/*****************************************************************/
// Operador de Mutación
/*****************************************************************/
void mutacion(solucion & s){

    // Generamos dos números aleatorios cuyo gen sea contrario
    int gen1 = rand()%s.sel.size();
    int gen2 = 0;

    do {
        gen2 = rand()%s.sel.size();
    } while(s.sel[gen1] == s.sel[gen2]);

    // Intercambiamos el valor de los genes que hemos seleccionado
    int aux = s.sel[gen1];
    s.sel[gen1] = s.sel[gen2];
    s.sel[gen2] = aux;
}


/*****************************************************************/
// Función realizar el reemplazamiento con elistismo
/*****************************************************************/
void reemplazamiento(poblacion & pPadres, poblacion & pActual){

    // Vemos si el primer hijo es mejor que el segundo
    if ( pPadres.C[1].contribucion < pPadres.C[0].contribucion){

        // Si el peor hijo es mejor que segundo peor cromosoma de pActual 
        if ( pActual.C[pActual.tam-2].contribucion < pPadres.C[1].contribucion){

            // Ambos hijos mejoran a los peores de pActual
            pActual.C[pActual.tam-2] = pPadres.C[1];
            pActual.C[pActual.tam-1] = pPadres.C[0];

            // Ordenamos la poblacion por contribución de forma descendente
            sort(pActual.C.begin(), pActual.C.end(), criterioOrdenacion);
        }
        // Si el mejor hijo es mejor que el peor cromosoma de pActual
        else if (pActual.C[pActual.tam-1].contribucion < pPadres.C[0].contribucion){

            pActual.C[pActual.tam-1] = pPadres.C[0];

            // Ordenamos la poblacion por contribución de forma descendente
            sort(pActual.C.begin(), pActual.C.end(), criterioOrdenacion);
        }
    }

    // Vemos si el segundo hijo es mejor que el primero 
    if ( pPadres.C[0].contribucion < pPadres.C[1].contribucion){

        // Si el peor hijo es mejor que segundo peor cromosoma de pActual 
        if ( pActual.C[pActual.tam-2].contribucion < pPadres.C[0].contribucion){

            // Ambos hijos mejoran a los peores de pActual
            pActual.C[pActual.tam-2] = pPadres.C[0];
            pActual.C[pActual.tam-1] = pPadres.C[1];

            // Ordenamos la poblacion por contribución de forma descendente
            sort(pActual.C.begin(), pActual.C.end(), criterioOrdenacion);
        }
        // Si el mejor hijo es mejor que el peor cromosoma de pActual
        else if (pActual.C[pActual.tam-1].contribucion < pPadres.C[1].contribucion){
            
            pActual.C[pActual.tam-1] = pPadres.C[1];

            // Ordenamos la poblacion por contribución de forma descendente
            sort(pActual.C.begin(), pActual.C.end(), criterioOrdenacion);
        }
    }
}

/*****************************************************************/
// Función para actualizar las contribuciones de una poblacion
/*****************************************************************/
void actualizarContribuciones(poblacion & p, vector<vector<float> > & matriz){

    for (int i = 0; i < 2; i++){

        // Si no está actualizada su contribución la volvemos a calcular
        if ( p.C[i].actualizada == false ){
            contribucion(p.C[i],matriz);
        }
    }
}


/*****************************************************************/
// Algoritmo Genético Estacionario 
// con operador de cruce basado en posición
/*****************************************************************/
void AGEposicion(int m, poblacion & pActual, vector<vector<float> > & matriz){

    int indice = 0;         // Variable para ir seleccionando cromosomas

    // Inicializamos la población, la rellenamos de soluciones aleatorias
    poblacionAleatoria(m,pActual,matriz);

    // Creamos una población de padres de tamaño 2
    poblacion pPadres;
    pPadres.C.resize(2);

    float prob_mutacion = 0.1;      //Probabilidad de mutación
    float aleatorio = 0.0;          // Nº aleatorio

    // Realizamos el bucle mientras el número de evaluaciones de la función objetivo 
    // no sobrepase el máximo establecido
    do {

        // SELECCIÓN

        // Realizamos la selección de padres en la población actual
        for (int i = 0; i < 2; i++){

            // Escogemos un cromosoma de la población actual
            indice = seleccion(pActual);

            // Lo añadimos a la población de padres
            pPadres.C[i] = pActual.C[indice];
        }


        // CRUCE BASADO EN POSICIÓN

        // Realizamos el cruce basado en posición
        crucePosicion(0,pPadres);
        

        // MUTACIÓN

        // Realizamos las mutaciones
        for (int i = 0; i < 2; i++){

            // Generamos un nº aleatorio para mutar entre 0 y 1
            aleatorio = (float) (rand()%100)/100;

            // Si la probabilidad es menor o igual mutamos
            if (aleatorio <= prob_mutacion){
                mutacion(pPadres.C[i]);
            }            
        }


        // ACTUALIZACIÓN

        // Procedemos a calcular las contribuciones
        actualizarContribuciones(pPadres, matriz);


        // REEMPLAZAMIENTO

        // Realizamos el reemplazamiento con elitismo
        reemplazamiento(pPadres,pActual);
        
        //cout << "Contribucion: " << pActual.C[0].contribucion << endl;

    } while(num_iteraciones < max_it);
}


int main(int argc, char *argv[]){

    // Comprobamos si el nº de parámetros es correcto
    if(argc < 3){
  	    cout << "ERROR, Modo de ejecución: " << argv[0] << " <archivo.txt> <semilla>" << endl;
		exit(-1);
    }

    string fichero = argv[1];          // Fichero de entrada 
    int semilla = stoi(argv[2]);       // Semilla aleatoria 

    // Abrimos el fichero de entrada
    ifstream fentrada(fichero);

    // Si hay un error al abrir el fichero
    if(!fentrada){
        cout<<"\nERROR al abrir el fichero: " << fichero << endl;
        exit(-1);
    }

    int n,   // nº de elementos
        m;   // nº de elementos seleccionados


    // Tomamos el nº de elementos y el nº elementos seleccionados
    fentrada >> n;
    fentrada >> m;

    poblacion pActual;      // Población actual 

    vector<vector<float>> matriz_distancias(n,vector<float>(n,0));        // Matriz de distancias 

    pair<int,int> nodos;    // Par con los nodos de los cuales sabemos su distancia
    float distancia;        // Distancia entre los dos nodos del par

    // Rellenamos la matriz de distancias
    for (int i = 0; i < n-1; i++){

        for (int j = i+1; j < n; j++){

            fentrada >> nodos.first >> nodos.second >> distancia;
            matriz_distancias[nodos.first][nodos.second] = distancia;
        }
    }

    // Cerramos el fichero de entrada
    fentrada.close();

    // Inicializamos la semilla
    srand(semilla);

    typedef std::chrono::high_resolution_clock Clock; 
    typedef std::chrono::milliseconds milliseconds; 
    Clock::time_point t0 = Clock::now();

    AGEposicion(m,pActual,matriz_distancias);

    Clock::time_point t1 = Clock::now(); 
    milliseconds ms = std::chrono::duration_cast<milliseconds>(t1 - t0); 

    cout << "Fichero: " << fichero << endl;
    cout << "Contribucion: " << pActual.C[0].contribucion << endl;
    cout << "Tiempo: " << ms.count() << "ms\n" << endl;
    
    return 0;
}