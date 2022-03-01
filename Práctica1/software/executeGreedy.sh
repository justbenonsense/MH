#!/bin/bash
# Título: executeGreedy
# Curso: 2020/21
# Autor: Carlota Valdivia Manzano

bin="bin"
input="input"
out_greedy="output/greedy.dat"

rm ${out_greedy}
touch ${out_greedy}

for i in {1..10}
do
 	echo "Ejecutando MDG-a_$i: "
 	${bin}/greedy ${input}/MDG-a_${i}_* >> ${out_greedy}
done

for i in {21..30}
do
	echo "Ejecutando MDG-b_$i: "
	${bin}/greedy ${input}/MDG-b_${i}_* >> ${out_greedy}
done

for i in {1,2,8,9,10,13,14,15,19,20}
do
	echo "Ejecutando MDG-c_$i: "
	${bin}/greedy ${input}/MDG-c_${i}_* >> ${out_greedy}
done

exit 0
