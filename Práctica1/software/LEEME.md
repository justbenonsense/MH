# Autor: Carlota Valdivia Manzano

# Directorio raíz: 

En directorio software hay 5 directorios: 

* bin
* input
* output
* src 
* zip. 

y hay 5 ficheros:

* makefile
* execute
* executeGreedy
* executeBusquedaLocal
* LEEME.md


# Subdirectorios

## Directorio bin

En el directorio bin se almacenan los ejecutables de ambos programas.

## Directorio input

En el directorio input se encuentran los distintos ficheros con los datos que pasaremos como argumento a la hora de ejecutarlos.

## Directorio output

En el directorio output se crean archivos con la información de cada ejecución del algoritmo: el fichero usando, el tiempo empleado y la contribución de la solución.

## Directorio src

En el directorio src se encuentra el código fuente de ambos algoritmos, que han sido implementados en ficheros .cpp distintos.

## Directorio zip

En el directorio zip se crea un archivo comprimido del directorio software.


# Ficheros

## Makefile

En el makefile se han creado tres macros para poder ejecutar cada programa, tanto por separado como a la vez. Las macros **execute_greedy**  y **execute_bl** ejecutan por separado todas los ficheros de entrada usando el algoritmo greedy o el búsqueda local, para ejecutar los dos a la vez hay que utilizar la macro **execute_all**. 

Para borrar los archivos del directorio bin hay una macro llamada **clean**.

## Execute

Fichero para ejecutar el programa **greedy** y **busquedaLocal** con todos los casos del problema.


## ExecuteGreedy

Fichero para ejecutar el programa **greedy** con todos los casos del problema.


## ExecuteBusquedaLocal

Fichero para ejecutar el programa **busquedaLocal** con todos los casos del problema.

Hay una variable llamada **semilla** que se puede modificar su valor para cambiar la semilla.

## LEEME.md

Fichero con la información acerca de la estructura del directorio software.



# Semilla

Con respecto a la semilla empleada en la Búsqueda Local, se pasa como segundo argumento en la ejecución del programa, por lo que para modificarla en la ejecución haría falta modificar el fichero **executeBusquedaLocal** y cambiarle el valor a la variable semilla.

