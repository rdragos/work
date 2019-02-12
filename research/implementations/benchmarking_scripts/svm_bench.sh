#!/bin/bash

#nparallel=(10 100 1000 1000) # to 10
#nruns=(10 100 1000 10000)

nruns=(10)
nclasses=(100) # to 10
nfeatures=(128 2048)

progname='gc_linear_svm'

for nr in "${nruns[@]}"; do
    for nf in "${nfeatures[@]}"; do
        for nc in "${nclasses[@]}"; do
            ./compile.py $progname $((nr)) $((nc)) $((nf)) | tail >> logs/compile_$progname
            ./Scripts/bench_bmr_progs.sh $progname -$((nr))-$((nc))-$((nf))
        done
    done
done
