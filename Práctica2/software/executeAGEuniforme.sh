#!/bin/bash
# Título: executeAGEuniforme
# Curso: 2020/21
# Autor: Carlota Valdivia Manzano

bin="bin"
input="input"
out_AGEuniforme="output/AGEuniforme.dat"
semilla=2

rm ${out_AGEuniforme}
touch ${out_AGEuniforme}

for i in {1..10}
do
 	echo "Ejecutando MDG-a_$i: "
	${bin}/AGEuniforme ${input}/MDG-a_${i}_* ${semilla} >> ${out_AGEuniforme}
done

for i in {21..30}
do
	echo "Ejecutando MDG-b_$i: "
	${bin}/AGEuniforme ${input}/MDG-b_${i}_* ${semilla} >> ${out_AGEuniforme}
done

for i in {1,2,8,9,10,13,14,15,19,20}
do
	echo "Ejecutando MDG-c_$i: "
	${bin}/AGEuniforme ${input}/MDG-c_${i}_* ${semilla} >> ${out_AGEuniforme}
done

exit 0
