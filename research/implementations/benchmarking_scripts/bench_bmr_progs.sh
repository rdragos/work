#!/bin/bash
progname=${1:-legendre}
suffix=${2:-}
nruns=${3:-5} # number of times to run + average each program over

# script only works for 2 parties; for multiple parties change tail - argument
# reason for this is to avoid including the trusted party timings

for (( j=1; j<=$nruns; j++ )); do
    echo "Benchmarking $progname$suffix $j"
    # Extract the time printed from "Time2"
    extra="$suffix rivest.cs shamir.cs"
    eval_times[$j]=$(Scripts/bmr-program-run-remote.sh $progname$extra 2>&1 | tee -a logs/bmr-$progname | awk '/Evaluation timer 0/ { print $6 }' | tail -2)
    prf_times[$j]=$(cat logs/bmr-$progname | awk '/PRF timer 0/ { print $6 }' | tail -2)
    echo "eval_times=${eval_times[$j]}"
    echo "prf_times=${prf_times[$j]}"

done
# take average of nruns times
prf_time=$(echo ${prf_times[@]} | awk '{sum=0; for(i=1; i<=NF; i++){sum+=$i}; sum/=NF; print sum}')
eval_time=$(echo ${eval_times[@]} | awk '{sum=0; for(i=1; i<=NF; i++){sum+=$i}; sum/=NF; print sum}')

echo $progname$suffix $prf_time $eval_time >> logs/results_$progname
