# Calculate FES and energy difference

#!/bin/bash

 T=300
 kt=`echo "${T} * 0.0083144621 " | bc -l`
 plumed sum_hills --hills HILLS_MTD.0  --kt ${kt} --stride 28480 --mintozero
 mkdir fesfiles
 mv fes_* fesfiles
# for file in fesfiles/fes_?.dat fesfiles/fes_??.dat fesfiles/fes_???.dat
# do
#  if [ -f ${file} ]
#  then
#    F=`awk 'BEGIN{tot=0}{fes=$2; if($1 >=3.5 && $1<=4.0) tot=tot+exp(-fes/kt)}END{print -kt*log(tot)}' kt=${kt} ${file}`
#    U=`awk 'BEGIN{tot=0}{fes=$2; if($1 >=1 && $1<=2) tot=tot+exp(-fes/kt)}END{print -kt*log(tot)}' kt=${kt} ${file}`
#    delta=`echo "(${U} - ${F})/${kt}" | bc -l`
#    echo $delta >> diff_t_norm300
#    echo "Extracting from file :: ${file}"  
#  fi
# done


### take out the "/ ${kt}" if you don't want the normalized version!
