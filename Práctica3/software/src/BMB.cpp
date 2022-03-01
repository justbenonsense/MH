//////////////////////////////////////////////////////////////////
// Práctica 3. Metaheurísticas.                                 //
// Problema de la Máxima Diversidad (MDP)                       //
// Algoritmo de Búsqueda Multiarranque Básica                   //
//                                                              //
// Carlota Valdivia Manzano                                     //
// NOTA: compilar g++ -g BMB.cpp -o BMB                         //
//       ejecutar ./BMB archivo.txt semilla                     //
//////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <random>
#include <chrono>
#include <limits>
#include <algorithm>    

using namespace std;

/*****************************************************************/
// Constantes y variables globales
/*****************************************************************/

const int max_ev = 10000;
const int max_it = 10;

/*****************************************************************/
// Estructura de representación de una solución
/*****************************************************************/
struct solucion {

    vector<pair<int,float>> Sel;        // Elementos seleccionados
    set<int> S;                         // Elementos sin seleccionar
    float contribucion;   // Valor de la contribución de la solución
};


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
// Función para imprimir un set de enteros
/*****************************************************************/
void imprimirSet(set<int> & S){

    for (set<int>::iterator it = S.begin(); it != S.end(); it++){

        cout << *it << ", ";
    }
}


/*****************************************************************/
// Función para imprimir un vector de pares<float,int>
/*****************************************************************/
void imprimirVectorPair(vector<pair<int,float>> & S){

    for (vector<pair<int,float>>::iterator it = S.begin(); it != S.end(); it++){

        cout << "(" << (*it).first << ", " << (*it).second << "), ";
    }
}

/*****************************************************************/
// Criterio de ordenación de pares
// Se ordena según el segundo elemento, en este caso es la 
// contribución
/*****************************************************************/
bool criterioOrdenacion(pair<int,float> & elem1, pair<int,float> & elem2) {
  return elem1.second < elem2.second;

}


/*****************************************************************/
// Función para comprobar si un intercambio produce mejora
/*****************************************************************/
bool mejoraIntercambio(float & diferencia, int elemento, int nuevo_elemento, vector<pair<int, float> > & Sel, vector<vector<float> > & matriz){
  
  diferencia = -Sel[elemento].second;

  for (vector<pair<int,float> >::iterator it = Sel.begin(); it != Sel.end(); it++){
    
    // Comprobamos
    if (*it != Sel[elemento]) {

        if (nuevo_elemento < (*it).first){
            diferencia += matriz[nuevo_elemento][(*it).first];
        }
        else if (nuevo_elemento > (*it).first){
            diferencia += matriz[(*it).first][nuevo_elemento];
        }
    }
  }

  return diferencia > 0;
}


/*********************************************************************/
// Función para actualizar la contribución cuando insertas un elemento
/*********************************************************************/
void actualizarContribuciones(pair<int,float> & elemento_in, pair<int,float> & elemento_out, vector<pair<int,float>> & Sel, vector<vector<float> > & matriz){       
    
    vector<pair<int,float>>::iterator it_out = find(Sel.begin(),Sel.end(),elemento_out);

    Sel.erase(it_out);

    // Actualizamos la contribución de los anteriores
    for (unsigned int i = 0; i < Sel.size(); i++){

        if ( Sel[i].first < elemento_out.first ){

            Sel[i].second -= matriz[Sel[i].first][elemento_out.first];
        }
        else if ( Sel[i].first > elemento_out.first ){
            
            Sel[i].second -= matriz[elemento_out.first][Sel[i].first];
        }

        if ( Sel[i].first < elemento_in.first ){

            Sel[i].second += matriz[Sel[i].first][elemento_in.first];
        }
        else if ( Sel[i].first > elemento_in.first ){
            
            Sel[i].second  += matriz[elemento_in.first][Sel[i].first];
        }
    }

    // Añadimos el que mejora en la última posición
    Sel.push_back(elemento_in);
  
    sort(Sel.begin(),Sel.end(),criterioOrdenacion);
}


/*****************************************************************/
// Función para generar una solución aleatoria
/*****************************************************************/
void solucionAletoria(int m, set<int> & S, vector<pair<int,float>> & Sel, vector<vector<float> > & matriz){

    int n = matriz[0].size();
    pair<int,float> aleatorio;

    while (Sel.size() < (unsigned) m){
        aleatorio.first = rand()%n;

        if (find(Sel.begin(),Sel.end(),aleatorio) == Sel.end()){
            Sel.push_back(aleatorio);
            S.erase(aleatorio.first);
        }
    }
    
    for (unsigned int i = 0; i < Sel.size(); i++){
        for (unsigned int j = 0; j < Sel.size(); j++){
            if (Sel[i].first < Sel[j].first ){
                Sel[i].second += matriz[Sel[i].first][Sel[j].first];
            }
            else if (Sel[i].first > Sel[j].first){
                Sel[i].second += matriz[Sel[j].first][Sel[i].first];
            }
           
        }
    }

    // Ordenamos el vector
    sort(Sel.begin(),Sel.end(),criterioOrdenacion);
}


/*****************************************************************/
// Algoritmo Búsqueda Local del Primero Mejor para MDP
/*****************************************************************/
void busquedaLocal(int m, set<int> & S, vector<pair<int,float>> & Sel, vector<vector<float> > & matriz){

    int cont = 0,
        indice = 0;

    float diferencia;

    set<int>::iterator it = S.begin();
    pair<int,float> elemento_act;

    while (cont < max_ev && (unsigned) indice < Sel.size()) {

        pair<int,float> min = Sel[indice];

        elemento_act.first = *it;
        elemento_act.second = 0;
        diferencia = 0;

        // Vemos si mejora la contribución
        if (mejoraIntercambio(diferencia,indice,*it,Sel,matriz)){

            // Actualizamos su contribución
            elemento_act.second = Sel[indice].second + diferencia;

            // Actualizamos el resto de contribuciones y borramos el peor
            actualizarContribuciones(elemento_act,min,Sel,matriz);

            // Actualizamos los elementos no seleccionados
            S.erase(it);
            S.insert(min.first);

            // Reestablecemos los índices
            indice = 0;            
            it = S.begin();
        }
        else{
            it++;
        }

        // Si no hemos encontrado ninguna mejora
        if (it == S.end()){
            indice++;
            it = S.begin();
        }

        cont++;
    }
}


/*****************************************************************/
// Función objetivo para calcular el fitness de una solución
/*****************************************************************/
float contribucion(vector<pair<int,float>> & Sel, vector<vector<float> > & matriz){

    float diversidad = 0;

    for (vector<pair<int,float>>::iterator it1 = Sel.begin(); it1 != Sel.end(); it1++){

        for (vector<pair<int,float>>::iterator it2 = it1; it2 != Sel.end(); it2++){

            if ( (*it1).first < (*it2).first ){

                diversidad += matriz[(*it1).first][(*it2).first];
            }
            else {

                diversidad += matriz[(*it2).first][(*it1).first];
            }
        }     
    }

    return diversidad;
}


/*****************************************************************/
// Algoritmo de Búsqueda Multiarranque Básica 
/*****************************************************************/
void BMB(int m, set<int> & S, solucion & mejorSol, vector<vector<float> > & matriz){

    int it = 1;

    // Creamos una solución
    solucion sol;
    sol.S = S;

    // Calculamos una solución aleatoria
    solucionAletoria(m,sol.S,sol.Sel,matriz);

    // Aplicamos Búsqueda Local
    busquedaLocal(m,sol.S,sol.Sel,matriz);

    // Calculamos su contribución
    sol.contribucion = contribucion(sol.Sel,matriz);

    do {

        // Vaciamos la solucion actual
        sol.contribucion = 0;
        sol.S.clear();
        sol.Sel.clear();
        sol.S = S;

        // Calculamos una solución aleatoria
        solucionAletoria(m,sol.S,sol.Sel,matriz);

        // Aplicamos Búsqueda Local
        busquedaLocal(m,sol.S,sol.Sel,matriz);

        // Calculamos su contribución
        sol.contribucion = contribucion(sol.Sel,matriz);

        // Vemos si la solución nueva es la mejor
        if ( sol.contribucion > mejorSol.contribucion ){
            mejorSol = sol;
        }

        it++;

    } while( it < max_it );

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

    vector<vector<float>> matriz_distancias(n,vector<float>(n,0));        // Matriz de distancias 
    set<int> S;                                                           // Elementos sin seleccionar
    solucion mejorSol;

    pair<int,int> nodos;    // Par con los nodos de los cuales sabemos su distancia
    float distancia;       // Distancia entre los dos nodos del par

    // Rellenamos la matriz de distancias
    for (int i=0; i < n-1; i++){

        S.insert(i);

        for (int j=i+1; j < n; j++){

            fentrada >> nodos.first >> nodos.second >> distancia;
            matriz_distancias[nodos.first][nodos.second] = distancia;
        }
    }

    S.insert(n-1);

    // Cerramos el fichero de entrada
    fentrada.close();


    // Inicializamos la semilla
    srand(semilla);

    //solucionAletoria(m,S,Sel,matriz_distancias);

    typedef std::chrono::high_resolution_clock Clock; 
    typedef std::chrono::milliseconds milliseconds; 
    Clock::time_point t0 = Clock::now();

    BMB(m,S,mejorSol,matriz_distancias);

    Clock::time_point t1 = Clock::now(); 
    milliseconds ms = std::chrono::duration_cast<milliseconds>(t1 - t0); 

    cout << "Fichero: " << fichero << endl;
    cout << "Contribucion: " << mejorSol.contribucion << endl;
    cout << "Tiempo: " << ms.count() << "ms\n" << endl;
    
    return 0;
}