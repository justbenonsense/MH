#!/bin/bash
# Título: executeAGGposicion
# Curso: 2020/21
# Autor: Carlota Valdivia Manzano

bin="bin"
input="input"
out_AGGposicion="output/AGGposicion.dat"
semilla=2

rm ${out_AGGposicion}
touch ${out_AGGposicion}

for i in {1..10}
do
 	echo "Ejecutando MDG-a_$i: "
	${bin}/AGGposicion ${input}/MDG-a_${i}_* ${semilla} >> ${out_AGGposicion}
done

for i in {21..30}
do
	echo "Ejecutando MDG-b_$i: "
	${bin}/AGGposicion ${input}/MDG-b_${i}_* ${semilla} >> ${out_AGGposicion}
done

for i in {1,2,8,9,10,13,14,15,19,20}
do
	echo "Ejecutando MDG-c_$i: "
	${bin}/AGGposicion ${input}/MDG-c_${i}_* ${semilla} >> ${out_AGGposicion}
done

exit 0
