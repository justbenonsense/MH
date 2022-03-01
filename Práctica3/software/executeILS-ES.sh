#!/bin/bash
# Título: executeILS-ES
# Curso: 2020/21
# Autor: Carlota Valdivia Manzano

bin="bin"
input="input"
out_ILS_ES="output/ILS-ES.dat"
semilla=2

rm ${out_ILS_ES}
touch ${out_ILS_ES}

for i in {1..10}
do
 	echo "Ejecutando MDG-a_$i: "
	${bin}/ILS-ES ${input}/MDG-a_${i}_* ${semilla} >> ${out_ILS_ES}
done

for i in {21..30}
do
	echo "Ejecutando MDG-b_$i: "
	${bin}/ILS-ES ${input}/MDG-b_${i}_* ${semilla} >> ${out_ILS_ES}
done

for i in {1,2,8,9,10,13,14,15,19,20}
do
	echo "Ejecutando MDG-c_$i: "
	${bin}/ILS-ES ${input}/MDG-c_${i}_* ${semilla} >> ${out_ILS_ES}
done

exit 0
