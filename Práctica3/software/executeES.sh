#!/bin/bash
# Título: executeES
# Curso: 2020/21
# Autor: Carlota Valdivia Manzano

bin="bin"
input="input"
out_ES="output/ES.dat"
semilla=2

rm ${out_ES}
touch ${out_ES}

for i in {1..10}
do
 	echo "Ejecutando MDG-a_$i: "
	${bin}/ES ${input}/MDG-a_${i}_* ${semilla} >> ${out_ES}
done

for i in {21..30}
do
	echo "Ejecutando MDG-b_$i: "
	${bin}/ES ${input}/MDG-b_${i}_* ${semilla} >> ${out_ES}
done

for i in {1,2,8,9,10,13,14,15,19,20}
do
	echo "Ejecutando MDG-c_$i: "
	${bin}/ES ${input}/MDG-c_${i}_* ${semilla} >> ${out_ES}
done

exit 0
