#!/bin/bash
# Título: executeBMB
# Curso: 2020/21
# Autor: Carlota Valdivia Manzano

bin="bin"
input="input"
out_BMB="output/BMB.dat"
semilla=2

rm ${out_BMB}
touch ${out_BMB}

for i in {1..10}
do
 	echo "Ejecutando MDG-a_$i: "
	${bin}/BMB ${input}/MDG-a_${i}_* ${semilla} >> ${out_BMB}
done

for i in {21..30}
do
	echo "Ejecutando MDG-b_$i: "
	${bin}/BMB ${input}/MDG-b_${i}_* ${semilla} >> ${out_BMB}
done

for i in {1,2,8,9,10,13,14,15,19,20}
do
	echo "Ejecutando MDG-c_$i: "
	${bin}/BMB ${input}/MDG-c_${i}_* ${semilla} >> ${out_BMB}
done

exit 0
