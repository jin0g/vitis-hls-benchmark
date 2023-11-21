#!/bin/bash

timestamp=$(date +"%Y%m%d_%H%M%S")
hostname=$(hostname)

SECONDS=0
vitis_hls -f benchmark_vitis_hls.tcl
time_vitis=$SECONDS

SECONDS=0
vitis_hls -f benchmark_vivado.tcl
time_vivado=$SECONDS

rm -r test_${hostname}

result_file="result_${hostname}_${timestamp}.txt"
echo "name: $hostname" >> $result_file
echo "date: $(date)" >> $result_file
echo "benchmark_vitis.tcl execution time: $time_vitis" >> $result_file
echo "benchmark_vivado.tcl execution time: $time_vivado" >> $result_file
cat $result_file
