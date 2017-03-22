#calculate energy difference between two states
#!/bin/bash
rm diff_t -f
T=300
for i in `seq 1 11861`
do
   echo "Extracting from :: fes_${i}.dat"                                    
   F=$(awk 'BEGIN{tot=0}{fes=$2; if($1 >=3.5 && $1<=5.5 && fes<100) tot=tot+exp(-fes/2.5)}END{print (-2.5)*log(tot)}' fes_${i}.dat)
   U=$(awk 'BEGIN{tot=0}{fes=$2; if($1 >=.5 && $1<=2.5 && fes<100) tot=tot+exp(-fes/2.5)}END{print (-2.5)*log(tot)}' fes_${i}.dat)
   delta=`echo "(${F} - ${U}) / 4.1859" | bc -l`
   echo "$i $delta" >> diff_t
done
