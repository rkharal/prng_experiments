#!/bin/bash
exe=bin/
outs=outputs/
#pushd $outs
#algorithms="fnv1a_rng kiss_rng kissrd_rng m64_rng mm3_rng mrg_rng mt_rng rdrand_rng"
algorithms="fnv1a_rng"
#algorithms="kissrd_rng"

echo all the algorithsm are $algorithms 

#NOTE reseeding is OFF

args1="-n 10000000 -p 1 -r 1"
bits="$(for ((b=0;b<5;++b));do echo $b ; done)"
args2="-s 1000" #sum interval


#pushd $outs

for b in $bits; do
    for alg in $algorithms; do 
    echo Next Alg is ${alg}
     #args1=""
     #args2=""
        
        cmd="bin/./${alg}  ${args1} | ./parse_rng -b ${b} ${args2} | grep \"Sum\" | cut -d\" \" -f4,9 > outputs/${alg}/${alg}_${b}_reseed_test.txt"
        echo next command is: $cmd
        eval $cmd
                   
    done
done

#for ((b=32;b<64;++b)); do rm mrg*$b*.txt ; done
#for ((b=32;b<64;++b)); do rm mm3*$b*.txt ; done
#Plotting
#popd
#cmd2= ./plot_rng.py -o ${b}_test.png -b ${b}
#      echo plot command is: $cmd2
#     eval $cmd2









