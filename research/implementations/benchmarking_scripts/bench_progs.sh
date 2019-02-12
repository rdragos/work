#!/bin/bash
progname=${1:-legendre}
lower=${2:-0}
upper=${3:-5}
suffix=${4:-}
nruns=${5:-3} # number of times to run + average each program over

for (( i=$lower; i<=$upper; i++ )); do
	n=$((2**$i))
	#echo $n >> logs/bench_$oramtype
	#./compile.py localpath$n--6 -p 128 -m 8192 | tail >> logs/bench_localpath
	for (( j=1; j<=$nruns; j++ )); do
        echo "Benchmarking $progname$n$suffix $i, $j"
        # Extract the time printed from "Time2"
		times[$j]=$(Scripts/bench-online.sh $progname$n$suffix 128 128 2>&1 | grep Time2 | tee -a logs/bench_$progname | awk '/Time2/ { print $3 }')
        #times[$i]=$(awk '/Time/ { print $3 }' $file)
        echo "time = ${times[$j]}"
	done
    # take average of nruns times
    time=$(echo ${times[@]} | awk '{sum=0; for(i=1; i<=NF; i++){sum+=$i}; sum/=NF; print sum}')
    echo $progname$n$suffix $time >> logs/results_$progname
done
