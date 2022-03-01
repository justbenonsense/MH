#!/bin/bash
# Título: execute
# Curso: 2020/21
# Autor: Carlota Valdivia Manzano

bin="bin"
input="input"
out_ES="output/ES.dat"
out_BMB="output/BMB.dat"
out_ILS="output/ILS.dat"
out_ILS_ES="output/ILS-ES.dat"
out_ES_geometrica="output/ES-geometrica.dat"
out_ILSrep="output/ILSrep.dat"
semilla=2

rm ${out_ES}
touch ${out_ES}
rm ${out_BMB}
touch ${out_BMB}
rm ${out_ILS}
touch ${out_ILS}
rm ${out_ILS_ES}
touch ${out_ILS_ES}
rm ${out_ES_geometrica}
touch ${out_ES_geometrica}
rm ${out_ILSrep}
touch ${out_ILSrep}


for i in {1..10}
do
 	echo "Ejecutando MDG-a_$i: "
	${bin}/ES ${input}/MDG-a_${i}_* ${semilla} >> ${out_ES}
	${bin}/BMB ${input}/MDG-a_${i}_* ${semilla} >> ${out_BMB}
	${bin}/ILS ${input}/MDG-a_${i}_* ${semilla} >> ${out_ILS}
	${bin}/ILS-ES ${input}/MDG-a_${i}_* ${semilla} >> ${out_ILS_ES}
	${bin}/ES-geometrica ${input}/MDG-a_${i}_* ${semilla} >> ${out_ES_geometrica}
	${bin}/ILSrep ${input}/MDG-a_${i}_* ${semilla} >> ${out_ILSrep}

done

for i in {21..30}
do
	echo "Ejecutando MDG-b_$i: "
	${bin}/ES ${input}/MDG-b_${i}_* ${semilla} >> ${out_ES}
	${bin}/BMB ${input}/MDG-b_${i}_* ${semilla} >> ${out_BMB}
	${bin}/ILS ${input}/MDG-b_${i}_* ${semilla} >> ${out_ILS}
	${bin}/ILS-ES ${input}/MDG-b_${i}_* ${semilla} >> ${out_ILS_ES}
	${bin}/ES-geometrica ${input}/MDG-b_${i}_* ${semilla} >> ${out_ES_geometrica}
	${bin}/ILSrep ${input}/MDG-b_${i}_* ${semilla} >> ${out_ILSrep}
done

for i in {1,2,8,9,10,13,14,15,19,20}
do
	echo "Ejecutando MDG-c_$i: "
	${bin}/ES ${input}/MDG-c_${i}_* ${semilla} >> ${out_ES}
	${bin}/BMB ${input}/MDG-c_${i}_* ${semilla} >> ${out_BMB}
	${bin}/ILS ${input}/MDG-c_${i}_* ${semilla} >> ${out_ILS}
	${bin}/ILS-ES ${input}/MDG-c_${i}_* ${semilla} >> ${out_ILS_ES}
	${bin}/ES-geometrica ${input}/MDG-c_${i}_* ${semilla} >> ${out_ES_geometrica}
	${bin}/ILSrep ${input}/MDG-c_${i}_* ${semilla} >> ${out_ILSrep}
done

exit 0
