#!/bin/bash
progname=${1:-legendre}
lower=${2:-1}
upper=${3:-5}
suffix=${4:-}
args=${5:-}

for (( i=$lower; i<=$upper; i++ )); do
    n=$((2**$i))
    ./compile.py $progname$n$suffix $args | tail >> logs/compile_$progname
done
