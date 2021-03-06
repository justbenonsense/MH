#!/bin/bash
# Título: executeAGGuniforme
# Curso: 2020/21
# Autor: Carlota Valdivia Manzano

bin="bin"
input="input"
out_AGGuniforme="output/AGGuniforme.dat"
semilla=2

rm ${out_AGGuniforme}
touch ${out_AGGuniforme}

for i in {1..10}
do
 	echo "Ejecutando MDG-a_$i: "
	${bin}/AGGuniforme ${input}/MDG-a_${i}_* ${semilla} >> ${out_AGGuniforme}
done

for i in {21..30}
do
	echo "Ejecutando MDG-b_$i: "
	${bin}/AGGuniforme ${input}/MDG-b_${i}_* ${semilla} >> ${out_AGGuniforme}
done

for i in {1,2,8,9,10,13,14,15,19,20}
do
	echo "Ejecutando MDG-c_$i: "
	${bin}/AGGuniforme ${input}/MDG-c_${i}_* ${semilla} >> ${out_AGGuniforme}
done

exit 0
