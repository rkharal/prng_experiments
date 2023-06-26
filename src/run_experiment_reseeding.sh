#!/bin/bash
#   Experiment: Reseeding option is turned ON
#               All PRNGs listed in 'algorithms' are tested
#               Testing bitwise randomness behaviour for bit positions [0..15]
#               Output files are generated
exe=../bin/
outs=outputs/
nbits=16

algorithms="fnv1a_rng xorsh_rng m64_rng mm3_rng mrg_rng mt_rng rdrand_rng"


echo all the algorithms are: $algorithms 
# Reseeding occurs every 10000 numbers (see run_rng.cpp)

args1="-n 10000000 -p 1 -r 1"
bits="$(for ((b=0;b<${nbits};++b));do echo $b ; done)"
args2="-s 1000"  #sum every 1000 numbers

for b in $bits; do

   
    for new in $algorithms; do 
        echo new is ${new}
        mkdir -p outputs/${new}  # create the directory if it doesn't exist 
     
        cmd="${exe}./${new}  ${args1} | ${exe}./parse_rng -b ${b} ${args2} | grep \"Sum\" | cut -d\" \" -f4,9 > outputs/${new}/${new}_${b}_reseed.txt"
        echo next command is: $cmd
        eval $cmd

    done
done

# REMOVE EXTRA OUTPUT FILES in 32-bit PRNGs IF THERE ARE BIT POSITIONS HIGHER THAN 31

if [ "${b}" -gt 31 ]; then
  cd outputs/mrg_rng/
  for ((b=32;b<64;++b)); do rm mrg*$b*.txt ; done

  cd ../mm3_rng/
  for ((b=32;b<64;++b)); do rm mm3*$b*.txt ; done
fi








