#!/bin/bash
# Título: executeAM-(10,0.1mej)
# Curso: 2020/21
# Autor: Carlota Valdivia Manzano

bin="bin"
input="input"
out_AM01mej="output/AM-(10,0.1mej).dat"
semilla=2

rm ${out_AM01mej}
touch ${out_AM01mej}

for i in {1..10}
do
 	echo "Ejecutando MDG-a_$i: "
	${bin}/AM01mej ${input}/MDG-a_${i}_* ${semilla} >> ${out_AM01mej}
done

for i in {21..30}
do
	echo "Ejecutando MDG-b_$i: "
	${bin}/AM01mej ${input}/MDG-b_${i}_* ${semilla} >> ${out_AM01mej}
done

for i in {1,2,8,9,10,13,14,15,19,20}
do
	echo "Ejecutando MDG-c_$i: "
	${bin}/AM01mej ${input}/MDG-c_${i}_* ${semilla} >> ${out_AM01mej}
done

exit 0
