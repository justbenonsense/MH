# Autor: Carlota Valdivia Manzano

# Directorio raíz: 

En directorio software hay 5 directorios: 

* bin
* input
* output
* src 
* zip. 

y hay 7 ficheros:

* makefile
* execute
* executeES
* executeBMB
* executeILS
* executeILS-ES
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

En el makefile se han creado tres macros para poder ejecutar cada programa, tanto por separado como a la vez. Las macros **execute_ES**, **execute_BMB**, **execute_ILS** y **execute_ILS_ES** ejecutan por separado todas los ficheros de entrada usando cada respectivo algoritmo, para ejecutar todos a la vez hay que utilizar la macro **execute_all**. 

Para borrar los archivos del directorio bin hay una macro llamada **clean**.

## Execute

Fichero para ejecutar el programa **ES**, **BMB**, **ILS** e **ILS-ES** con todos los casos del problema.


## ExecuteES

Fichero para ejecutar el programa **ES** con todos los casos del problema.

Hay una variable llamada **semilla** que se puede modificar su valor para cambiar la semilla.


## ExecuteBMB

Fichero para ejecutar el programa **BMB** con todos los casos del problema.

Hay una variable llamada **semilla** que se puede modificar su valor para cambiar la semilla.


## ExecuteILS

Fichero para ejecutar el programa **ILS** con todos los casos del problema.

Hay una variable llamada **semilla** que se puede modificar su valor para cambiar la semilla.


## ExecuteILS-ES

Fichero para ejecutar el programa **ILS-ES** con todos los casos del problema.

Hay una variable llamada **semilla** que se puede modificar su valor para cambiar la semilla.


## LEEME.md

Fichero con la información acerca de la estructura del directorio software.



# Semilla

Con respecto a la semilla empleada en cada algoritmo, se pasa como segundo argumento en la ejecución del programa, por lo que para modificarla en la ejecución haría falta modificar su respectivo fichero **execute** y cambiarle el valor a la variable semilla.

