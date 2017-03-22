#generate tpr files for replicas in PTmetad
#!/bin/bash


count=0
for temp in 300.0 323.3 349.3 378.7 412.1 450.00; do
  cp nvt.mdp $count.mdp
  perl -pi -e "s/XXX/$temp/g" $count.mdp
  cp plumed.dat plumed.dat.$count
  perl -pi -e "s/XXX/$temp/g" plumed.dat.$count
  gmx grompp  -f $count.mdp -c ../2.wtesetup/confout$count.gro -p topol.top
  mv topol.tpr topol$count.tpr
  (( count++ ))
  rm -rf mdout.mdp 
done;

for ((i=0;i<$count;i++)); do 
  touch HILLS.$i; 
done;
