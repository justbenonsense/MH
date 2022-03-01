#!/bin/bash
# Título: executeES-geometrica
# Curso: 2020/21
# Autor: Carlota Valdivia Manzano

bin="bin"
input="input"
out_ES_geometrica="output/ES-geometrica.dat"
semilla=2

rm ${out_ES_geometrica}
touch ${out_ES_geometrica}

for i in {1..10}
do
 	echo "Ejecutando MDG-a_$i: "
	${bin}/ES-geometrica ${input}/MDG-a_${i}_* ${semilla} >> ${out_ES_geometrica}
done

for i in {21..30}
do
	echo "Ejecutando MDG-b_$i: "
	${bin}/ES-geometrica ${input}/MDG-b_${i}_* ${semilla} >> ${out_ES_geometrica}
done

for i in {1,2,8,9,10,13,14,15,19,20}
do
	echo "Ejecutando MDG-c_$i: "
	${bin}/ES-geometrica ${input}/MDG-c_${i}_* ${semilla} >> ${out_ES_geometrica}
done

exit 0
