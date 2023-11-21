# benchmark_vitis_hls.tcl
set hostname [exec hostname]

open_project test_$hostname
set_top kernel
add_files benchmark_kernel.cc
open_solution "solution1" -flow_target vivado
set_part xck26-sfvc784-2LV-c
create_clock -period 1.3 -name default
config_export -format ip_catalog -rtl verilog
set_clock_uncertainty 0
csynth_design
close_project
exit
