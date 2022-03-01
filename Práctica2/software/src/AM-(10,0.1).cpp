//////////////////////////////////////////////////////////////////
// Práctica 2. Metaheurísticas.
// Problema de la Máxima Diversidad (MDP)
// Algoritmo Genético Memético para el MDP 
//
// Carlota Valdivia Manzano
// NOTA: compilar g++ AM-(10,1.0).cpp -o AM-(10,1.0)
//       ejecutar ./AM-(10,1.0) archivo.txt semilla
/////////////////////////////////////////////////////////////////

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

const int max_it = 100000;          // Nº máximo de evaluaciones de la función objetivo
const int max_it_bl = 400;          // Nº máximo de vecino evaluados en la BL
const int num_cromosomas = 50;      // Nº de cromosomas de la población
const float prob_cruce = 0.7;       // Probabilidad de cruce de dos individuos
const float prob_bl = 0.1;          // Probabilidad de hacer búsqueda local
int num_iteraciones = 0;            // Nº de evaluaciones actuales de la función objetivo
const int frec_generaciones = 10;   // Frecuencia de ejecución de la BL


/*****************************************************************/
// Estructura de representación de una solución (cromosoma)
/*****************************************************************/
struct solucion {

    vector<int> sel;        // Vector de 0s y 1s (1: elementos seleccionados)
    bool actualizada;       // Indica si tenemos actualizada su contribución
    float contribucion;     // Valor de la contribución de la solución
};


/*****************************************************************/
// Estructura de representación de una población
/*****************************************************************/
struct poblacion {

    int tam;                      // Tamaño de la población
    vector<solucion> C;           // Vector de soluciones (cromosomas)
    int mejorSol;                 // Mejor solución (cromosoma)
    float mejorContr;             // Contribución de la mejor solución 
};


/*****************************************************************/
// Criterio de ordenación de pares
// Se ordena según el segundo elemento, en este caso es la 
// contribución
/*****************************************************************/
bool criterioOrdenacion(pair<int,float> & elem1, pair<int,float> & elem2) {
  return elem1.second < elem2.second;

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

            // Lo añadimos
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
    p.mejorContr = 0;

    // Calculamos las soluciones aleatorias
    for (int i = 0; i < p.tam; i++){
       solucionAletoria(m,p.C[i],matriz);
       
       // Vemos si su contribución es la menor
       if(p.C[i].contribucion > p.mejorContr){

           // Guardamos la mejor solución
           p.mejorContr = p.C[i].contribucion;
           p.mejorSol = i;
       }
    }

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

    // Creamos dos vectores auxilirias
    vector<int> aux1, aux2;

    int num;

    // Elegimos los genes restantes del primer hijo
    for (unsigned i = 0; i < restos1.size(); i++){

        // Elegimos aleatoriamente el gen de uno de los dos padres
        num = rand()%2;

        if ( num == 0 )
            aux1.push_back(restos1[i]);
        else 
            aux1.push_back(restos2[i]);
    }

    // Elegimos los genes restantes del segundo hijo
    for (unsigned i = 0; i < restos2.size(); i++){

        // Elegimos aleatoriamente el gen de uno de los dos padres
        num = rand()%2;

        if ( num == 0 )
            aux2.push_back(restos1[i]);
        else 
            aux2.push_back(restos2[i]);
    }

    restos1 = aux1;
    restos2 = aux2;
}

/*****************************************************************/
// Función para reparar los hijos después del cruce
/*****************************************************************/
void reparar(int m, solucion & hijo, vector<vector<float> > & matriz){

    int num = 0;

    // Vemos el nº de unos que tienen
    for (unsigned i = 0; i < hijo.sel.size(); i++){
        num += hijo.sel[i];
    }

    // Si el número de unos es mayor
    if (num > m){

        int max = 0;
        int contrMax = 0;
        int contr = 0;

        // Eliminamos los de mayor contribución hasta que sea factible
        do{

            // Calculamos la contribución de cada gen
            for (unsigned i = 0; i < hijo.sel.size(); i++){

                // Si es un gen seleccionado
                if (hijo.sel[i] == 1 ){
                
                    for (unsigned j = 0; j < hijo.sel.size(); j++){

                        // Tenemos en cuenta solamente los genes seleccionados
                        if ( hijo.sel[j] == 1 ){

                            if ( i < j ){
                                contr += matriz[i][j];   
                            }
                            else {
                                contr += matriz[j][i];   
                            }
                        }
                    }

                    // Vemos si la contribución es mejor
                    if (contr > contrMax){
                        contrMax = contr;
                        max = i;
                    }

                    // Reestablecemos la contribución
                    contr = 0;
                }
            }

            // Eliminamos el de mayor contribución
            hijo.sel[max] = 0;
            contrMax = 0;
            num--;

        } while(num > m);
    }

    // Si el número de unos es menor
    if (num < m){

        int max = 0;
        int contrMax = 0;
        int contr = 0;

        // Eliminamos los de mayor contribución hasta que sea factible
        do{
            // Calculamos la contribución de cada gen
            for (unsigned i = 0; i < hijo.sel.size(); i++){

                // Si es un gen seleccionado
                if (hijo.sel[i] == 0 ){
                
                    for (unsigned j = 0; j < hijo.sel.size(); j++){

                        // Tenemos en cuenta solamente los genes seleccionados
                        if ( hijo.sel[j] == 1 ){

                            if ( i < j ){
                                contr += matriz[i][j];   
                            }
                            else {
                                contr += matriz[j][i];   
                            }
                        }
                    }

                    // Vemos si la contribución es mejor
                    if (contr > contrMax){
                        contrMax = contr;
                        max = i;
                    }

                    // Reestablecemos la contribución
                    contr = 0;
                }
            }

            // Añadimos el de mayor contribución
            hijo.sel[max] = 1;
            contrMax = 0;
            num++;

        } while(num < m);
    }
}


/*****************************************************************/
// Operador de Cruce Uniforme 
/*****************************************************************/
void cruceUniforme(int m, int pos, poblacion & pPadres, vector<vector<float> > & matriz){

    int tam = pPadres.C[pos].sel.size();       // Nº de genes total

    // Creamos dos vectores para guardar los restos del cruce
    vector<int> restos1, restos2;

    // Creamos una solución para los hijos
    solucion hijo1, hijo2;
    hijo1.sel = vector<int> (tam,-1);       
    hijo2.sel = vector<int> (tam,-1);

    for (int i = 0; i < tam; i++){

        // Vemos si el gen es el mismo en ambos padres
        if (pPadres.C[pos].sel[i] == pPadres.C[pos+1].sel[i]){
            hijo1.sel[i] = pPadres.C[pos].sel[i];
            hijo2.sel[i] = pPadres.C[pos].sel[i];
        }
        else{
            restos1.push_back(pPadres.C[pos].sel[i]);
            restos2.push_back(pPadres.C[pos+1].sel[i]);      
        }
    }

    // Aleatorizamos los restos de un padre
    restosCruce(restos1,restos2);
    int cont = 0;
    
    // Sustuimos los restos aleatorios
    for(unsigned i = 0; i < tam && cont < restos1.size(); i++){
        
        // Si no está asignado todavía
        if (hijo1.sel[i] == -1){
            hijo1.sel[i] = restos1[cont];
            hijo2.sel[i] = restos2[cont];
            cont++;
        }
    }

    // Reparamos los hijos
    reparar(m,hijo1,matriz);
    reparar(m,hijo2,matriz);

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

    // Vemos si el mejor cromosoma de padres está en la última posición
    if ( pPadres.mejorContr == pPadres.C[num_cromosomas-1].contribucion){

        pPadres.C[num_cromosomas-2] = pActual.C[pActual.mejorSol];

        // Entonces guardarmos el mejor cromosoma anterior en la penúltima posición de padres
        if(pPadres.C[num_cromosomas-2].contribucion > pPadres.mejorContr){

            // Guardamos la mejor solución
            pPadres.mejorContr = pPadres.C[num_cromosomas-2].contribucion;
            pPadres.mejorSol = num_cromosomas-2;
        }       
    }
    else {

        // Entonces guardarmos el mejor cromosoma anterior en la última posición de padres
        pPadres.C[num_cromosomas-1] = pActual.C[pActual.mejorSol];

        // Vemos si su contribución es la mejor
        if(pPadres.C[num_cromosomas-1].contribucion > pPadres.mejorContr){

            // Guardamos la mejor solución
            pPadres.mejorContr = pPadres.C[num_cromosomas-1].contribucion;
            pPadres.mejorSol = num_cromosomas-1;
        }    
    }

    // Realizamos el cambio
    pActual.C.swap(pPadres.C);
    pActual.mejorContr = pPadres.mejorContr;
    pActual.mejorSol = pPadres.mejorSol;

    // Reestablecemos el valor de la mejor contribución de padres
    pPadres.mejorContr = 0;    
}


/*****************************************************************/
// Función para actualizar las contribuciones de una poblacion
/*****************************************************************/
void actualizarContribuciones(poblacion & p, vector<vector<float> > & matriz){

    for (int i = 0; i < num_cromosomas; i++){

        // Si no está actualizada su contribución la volvemos a calcula
        if ( p.C[i].actualizada == false ){

            contribucion(p.C[i],matriz);
        }

        // Vemos si su contribución es la mejor
        if(p.C[i].contribucion > p.mejorContr){

            // Guardamos la mejor solución
            p.mejorContr = p.C[i].contribucion;
            p.mejorSol = i;
        }
    }
}

/*****************************************************************/
// Función para comprobar si un intercambio produce mejora
/*****************************************************************/
bool mejoraIntercambio(float & diferencia, int elemento, int nuevo_elemento, vector<pair<int, float> > & Sel, vector<vector<float> > & matriz){
  
  diferencia = -Sel[elemento].second;

  for (vector<pair<int,float> >::iterator it = Sel.begin(); it != Sel.end(); it++){
    
    // Comprobamos que no sea el elemento
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
void actualizarContribucionesBL(pair<int,float> & elemento_in, pair<int,float> & elemento_out, vector<pair<int,float>> & Sel, vector<vector<float> > & matriz){       
    
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

    while (cont < max_it_bl && (unsigned) indice < Sel.size()) {

        pair<int,float> min = Sel[indice];

        elemento_act.first = *it;
        elemento_act.second = 0;
        diferencia = 0;

        // Vemos si mejora la contribución
        if (mejoraIntercambio(diferencia,indice,*it,Sel,matriz)){

            // Actualizamos su contribución
            elemento_act.second = Sel[indice].second + diferencia;

            // Actualizamos el resto de contribuciones y borramos el peor
            actualizarContribucionesBL(elemento_act,min,Sel,matriz);

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
        num_iteraciones++;
    }
}


/*****************************************************************/
// Función para aplicar búsqueda local a una población
/*****************************************************************/
void memetico(int m, solucion & s, vector<vector<float> > & matriz){

    vector<pair<int,float>> Sel;
    set<int> S;

    for (unsigned j = 0; j < s.sel.size(); j++){

        // Si está seleccionado
        if ( s.sel[j] == 1){
            Sel.push_back(make_pair(j,0.0));
        }

        // Si no está seleccionado
        if ( s.sel[j] == 0){
            S.insert(j);
        }
    }

    // Calculamos las contribuciones parciales
        for (unsigned k = 0; k < Sel.size(); k++){

            for (unsigned j = 0; j < Sel.size(); j++){

                if (Sel[k].first < Sel[j].first ){
                    Sel[k].second += matriz[Sel[k].first][Sel[j].first];
                }
                else if (Sel[k].first > Sel[j].first){
                    Sel[k].second += matriz[Sel[j].first][Sel[k].first];
                }
            
            }
        }

    // Ordenamos el vector
    sort(Sel.begin(),Sel.end(),criterioOrdenacion);

    // Aplicamos búsqueda local
    busquedaLocal(m,S,Sel,matriz);

    s.sel.clear();
    s.sel = vector<int> (matriz[0].size(),0);

    // Pasamos de entero a binario
    for (unsigned j = 0; j < Sel.size(); j++){

        s.sel[Sel[j].first] = 1;
    }

    // Señalamos que tenemos que actualizar su contribución
    s.actualizada = false;
}


/*****************************************************************/
// Algoritmo Genético Generacional 
// con operador de cruce uniforme
/*****************************************************************/
void AM(int m, poblacion & pActual, vector<vector<float> > & matriz){

    int indice = 0;           // Variable para ir seleccionando cromosomas
    int generaciones = 0;     // Nº de generaciones

    // Inicializamos la población, la rellenamos de soluciones aleatorias
    poblacionAleatoria(m,pActual,matriz);

    // Creamos una población de padres
    poblacion pPadres;
    pPadres.C.resize(pActual.tam);

    // Calculamos el número de cruces y de mutaciones
    int num_cruces = prob_cruce * num_cromosomas;
    int num_mutaciones = 0.1 * num_cromosomas;
    int num_bl = prob_bl * num_cromosomas;

    int aleatorio = 0;      // Nº aleatorio
    int num = 0;            // Nº aleatorio en módulo

    // Realizamos el bucle mientras el número de evaluaciones de la función objetivo 
    // no sobrepase el máximo establecido
    do {
        // SELECCIÓN

        // Realizamos la selección de padres en la población actual
        for (int i = 0; i < pActual.tam; i++){

            // Escogemos un cromosoma de la población actual
            indice = seleccion(pActual);

            // Lo añadimos a la población de padres
            pPadres.C[i] = pActual.C[indice];
        }


        // CRUCE UNIFORME

        // Realizamos el cruce uniforme
        for (int i = 0; i < num_cruces; i=i+2){
            cruceUniforme(m,i,pPadres,matriz);
        }


        // MUTACIÓN

        // Generamos un nº aleatorio para mutar
        aleatorio = rand()%num_cromosomas;

        // Realizamos las mutaciones
        for (int i = 1; i < num_mutaciones+1; i++){

            num = (aleatorio*i)%num_cromosomas;

            mutacion(pPadres.C[num]);

            // Señalamos que tenemos que actualizar la contribución
            pPadres.C[num].actualizada = false;
        }


        // BÚSQUEDA LOCAL

        generaciones++;

        // Si hemos hecho 10 generaciones
        if (generaciones == frec_generaciones){

            // Generamos un nº aleatorio para hacer BL
            aleatorio = rand()%num_cromosomas;
        
            for (int i = 1; i < num_bl+1; i++){
                num = (aleatorio*i)%num_cromosomas;

                memetico(m,pPadres.C[num],matriz);
            }

            generaciones = 0;
        }


        // ACTUALIZACIÓN

        // Procedemos a calcular las contribuciones
        actualizarContribuciones(pPadres, matriz);


        // REEMPLAZAMIENTO

        // Realizamos el reemplazamiento con elitismo
        reemplazamiento(pPadres,pActual);
        
        
        //cout << "Contribucion: " << pActual.C[pActual.mejorSol].contribucion << "      " << pActual.mejorSol << endl;

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

    AM(m,pActual,matriz_distancias);

    Clock::time_point t1 = Clock::now(); 
    milliseconds ms = std::chrono::duration_cast<milliseconds>(t1 - t0); 

    cout << "Fichero: " << fichero << endl;
    cout << "Contribucion: " << pActual.C[pActual.mejorSol].contribucion << endl;
    cout << "Tiempo: " << ms.count() << "ms\n" << endl;
    
    return 0;
}