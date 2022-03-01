#!/bin/bash
# Título: executeILSrep
# Curso: 2020/21
# Autor: Carlota Valdivia Manzano

bin="bin"
input="input"
out_ILSrep="output/ILSrep.dat"
semilla=2

rm ${out_ILSrep}
touch ${out_ILSrep}

for i in {1..10}
do
 	echo "Ejecutando MDG-a_$i: "
	${bin}/ILSrep ${input}/MDG-a_${i}_* ${semilla} >> ${out_ILSrep}
done

for i in {21..30}
do
	echo "Ejecutando MDG-b_$i: "
	${bin}/ILSrep ${input}/MDG-b_${i}_* ${semilla} >> ${out_ILSrep}
done

for i in {1,2,8,9,10,13,14,15,19,20}
do
	echo "Ejecutando MDG-c_$i: "
	${bin}/ILSrep ${input}/MDG-c_${i}_* ${semilla} >> ${out_ILSrep}
done

exit 0
