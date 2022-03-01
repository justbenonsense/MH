#!/bin/bash
# Título: executeAM-(10,1.0)
# Curso: 2020/21
# Autor: Carlota Valdivia Manzano

bin="bin"
input="input"
out_AM1="output/AM-(10,1.0).dat"
semilla=2

rm ${out_AM1}
touch ${out_AM1}

for i in {1..10}
do
 	echo "Ejecutando MDG-a_$i: "
	${bin}/AM1 ${input}/MDG-a_${i}_* ${semilla} >> ${out_AM1}
done

for i in {21..30}
do
	echo "Ejecutando MDG-b_$i: "
	${bin}/AM1 ${input}/MDG-b_${i}_* ${semilla} >> ${out_AM1}
done

for i in {1,2,8,9,10,13,14,15,19,20}
do
	echo "Ejecutando MDG-c_$i: "
	${bin}/AM1 ${input}/MDG-c_${i}_* ${semilla} >> ${out_AM1}
done

exit 0
