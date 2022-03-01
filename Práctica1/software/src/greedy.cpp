//////////////////////////////////////////////////////////////////
// Práctica 1. Metaheurísticas.
// Problema de la Máxima Diversidad (MDP)
// Solución Greedy
//
// Carlota Valdivia Manzano
// NOTA: compilar g++ -g greedy.cpp -o greedy
//       ejecutar ./greedy archivo.txt
/////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <chrono>

using namespace std;

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
// Función para imprimir un set de pares
/*****************************************************************/

void imprimirSet(set<int> & S){

    for (set<int>::iterator it = S.begin(); it != S.end(); it++){

        cout << *it << ", ";
    }
}

/*****************************************************************/
// Distancia acumulada entre un elemento de S y el resto
/*****************************************************************/

float distAc(int indice, set<int> & S, vector<vector<float> > & matriz){

    float dist = 0;

    for (set<int>::iterator it = S.begin(); it != S.end(); it++){

        if ( *it < indice ){
            dist += matriz[*it][indice];
        }
        else if ( *it > indice ){
            dist += matriz[indice][*it];
        }
        
    }

    return dist;
}

/*****************************************************************/
// Distancia mínima entre un elemento de S y los de Sel
/*****************************************************************/

float dist(int indice, set<int> & Sel, vector<vector<float> > & matriz){

    float min = numeric_limits<float>::max(), 
           dist = 0;

    for (set<int>::iterator it = Sel.begin(); it != Sel.end(); it++){

        if ( *it < indice ){
            dist = matriz[*it][indice];
        }
        else if ( *it > indice ){
            dist = matriz[indice][*it];
        }

        if (dist < min) {
            min = dist;
        }
    }

    return min;
}

/*****************************************************************/
// Algoritmo Greedy para MDP
/*****************************************************************/

void greedy(set<int> & S, set<int> & Sel, vector<vector<float> > & matriz, int m){

    int max = -1;
    float dist_max = -1,
           dist_actual = 0;

    // Calculamos la distancia acumulada de cada elemento al resto
    for (set<int>::iterator it = S.begin(); it != S.end(); it++){

        dist_actual = distAc(*it,S,matriz);

        if (dist_actual > dist_max) {
            max = *it;
            dist_max = dist_actual;
        }
    }

    // Nos quedamos con el que maximice en Sel
    Sel.insert(max);

    // Lo eliminamos de S
    S.erase(max);

    while (Sel.size() < (unsigned) m){

        dist_max = -1;

        // Calculamos las distancias de los elementos de S a los de Sel
        for (set<int>::iterator it = S.begin(); it != S.end(); it++){

            dist_actual = dist(*it,Sel,matriz);

            if (dist_actual > dist_max) {
                max = *it;
                dist_max = dist_actual;
            }
        }

        // Incluimos el elemento que maximice en Sel
        Sel.insert(max);

        // Lo eliminamos de S
        S.erase(max);

    }
    
}

float solucionMDP(set<int> & Sel, vector<vector<float> > & matriz){

    float diversidad = 0;

    for (set<int>::iterator it1 = Sel.begin(); it1 != Sel.end(); it1++){

        for (set<int>::iterator it2 = it1; it2 != Sel.end(); it2++){

            diversidad += matriz[*it1][*it2];
        }     
    }

    return diversidad;
}


int main(int argc, char *argv[]){

    if(argc < 2){
  	    cout << "ERROR, Modo de ejecución: " << argv[0] << " <archivo.txt>" << endl;
		exit(-1);
    }

    string fichero = argv[1];       // Fichero de entrada     

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

    vector<vector<float>> matriz_distancias(n,vector<float>(n,0));
    set<int> S, Sel;

    pair<int,int> nodos;   // Par con los nodos de los cuales sabemos su distancia
    float distancia;       // Distancia entre los dos nodos del par

    // Rellenamos la matriz de distancias
    for (int i=0; i < n-1; i++){

        S.insert(i);

        for (int j=i+1; j < n; j++){

            fentrada >> nodos.first >> nodos.second >> distancia ;
            matriz_distancias[nodos.first][nodos.second] = distancia;
        }
    }

    S.insert(n-1);

    // Cerramos el fichero de entrada
    fentrada.close();

    typedef std::chrono::high_resolution_clock Clock; 
    typedef std::chrono::milliseconds milliseconds; 
    Clock::time_point t0 = Clock::now();


    greedy(S, Sel, matriz_distancias, m);
    float solucion = solucionMDP(Sel,matriz_distancias);

    Clock::time_point t1 = Clock::now(); 
    milliseconds ms = std::chrono::duration_cast<milliseconds>(t1 - t0); 
    //imprimirSet(Sel);

    cout << "Fichero: " << fichero << endl;
    cout << "Contribucion: " << solucion << endl;
    cout << "Tiempo: " << ms.count() << "ms\n" << endl;
    
    return 0;
}