#!/bin/bash
# Título: execute
# Curso: 2020/21
# Autor: Carlota Valdivia Manzano

bin="bin"
input="input"
out_AGGposicion="output/AGGposicion.dat"
out_AGGuniforme="output/AGGuniforme.dat"
out_AGEposicion="output/AGEposicion.dat"
out_AGEuniforme="output/AGEuniforme.dat"
out_AM1="output/AM-(10,1.0).dat"
out_AM01="output/AM-(10,0.1).dat"
out_AM01mej="output/AM-(10,0.1mej).dat"
semilla=2

rm ${out_AGGposicion}
touch ${out_AGGposicion}
rm ${out_AGGuniforme}
touch ${out_AGGuniforme}
rm ${out_AGEposicion}
touch ${out_AGEposicion}
rm ${out_AGEuniforme}
touch ${out_AGEuniforme}
rm ${out_AM1}
touch ${out_AM1}
rm ${out_AM01}
touch ${out_AM01}
rm ${out_AM01mej}
touch ${out_AM01mej}


for i in {1..10}
do
 	echo "Ejecutando MDG-a_$i: "
 	${bin}/AGGposicion ${input}/MDG-a_${i}_* ${semilla} >> ${out_AGGposicion}
	${bin}/AGGuniforme ${input}/MDG-a_${i}_* ${semilla} >> ${out_AGGuniforme}
	${bin}/AGEposicion ${input}/MDG-a_${i}_* ${semilla} >> ${out_AGEposicion}
	${bin}/AGEuniforme ${input}/MDG-a_${i}_* ${semilla} >> ${out_AGEuniforme}
	${bin}/AM1 ${input}/MDG-a_${i}_* ${semilla} >> ${out_AM1}
	${bin}/AM01 ${input}/MDG-a_${i}_* ${semilla} >> ${out_AM01}
	${bin}/AM01mej ${input}/MDG-a_${i}_* ${semilla} >> ${out_AM01mej}
done

for i in {21..30}
do
	echo "Ejecutando MDG-b_$i: "
	${bin}/AGGposicion ${input}/MDG-b_${i}_* ${semilla} >> ${out_AGGposicion}
	${bin}/AGGuniforme ${input}/MDG-b_${i}_* ${semilla} >> ${out_AGGuniforme}
	${bin}/AGEposicion ${input}/MDG-b_${i}_* ${semilla} >> ${out_AGEposicion}
	${bin}/AGEuniforme ${input}/MDG-b_${i}_* ${semilla} >> ${out_AGEuniforme}
	${bin}/AM1 ${input}/MDG-b_${i}_* ${semilla} >> ${out_AM1}
	${bin}/AM01 ${input}/MDG-b_${i}_* ${semilla} >> ${out_AM01}
	${bin}/AM01mej ${input}/MDG-b_${i}_* ${semilla} >> ${out_AM01mej}
done

for i in {1,2,8,9,10,13,14,15,19,20}
do
	echo "Ejecutando MDG-c_$i: "
	${bin}/AGGposicion ${input}/MDG-c_${i}_* ${semilla} >> ${out_AGGposicion}
	${bin}/AGGuniforme ${input}/MDG-c_${i}_* ${semilla} >> ${out_AGGuniforme}
	${bin}/AGEposicion ${input}/MDG-c_${i}_* ${semilla} >> ${out_AGEposicion}
	${bin}/AGEuniforme ${input}/MDG-c_${i}_* ${semilla} >> ${out_AGEuniforme}
	${bin}/AM1 ${input}/MDG-c_${i}_* ${semilla} >> ${out_AM1}
	${bin}/AM01 ${input}/MDG-c_${i}_* ${semilla} >> ${out_AM01}
	${bin}/AM01mej ${input}/MDG-c_${i}_* ${semilla} >> ${out_AM01mej}
done

exit 0
