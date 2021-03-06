#!/bin/bash
# Título: executeAGEposicion
# Curso: 2020/21
# Autor: Carlota Valdivia Manzano

bin="bin"
input="input"
out_AGEposicion="output/AGEposicion.dat"
semilla=2

rm ${out_AGEposicion}
touch ${out_AGEposicion}

for i in {1..10}
do
 	echo "Ejecutando MDG-a_$i: "
	${bin}/AGEposicion ${input}/MDG-a_${i}_* ${semilla} >> ${out_AGEposicion}
done

for i in {21..30}
do
	echo "Ejecutando MDG-b_$i: "
	${bin}/AGEposicion ${input}/MDG-b_${i}_* ${semilla} >> ${out_AGEposicion}
done

for i in {1,2,8,9,10,13,14,15,19,20}
do
	echo "Ejecutando MDG-c_$i: "
	${bin}/AGEposicion ${input}/MDG-c_${i}_* ${semilla} >> ${out_AGEposicion}
done

exit 0
