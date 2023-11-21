# benchmark_vivado.tcl
set hostname [exec hostname]

open_project test_$hostname
open_solution "solution1" -flow_target vivado
config_export -format ip_catalog -rtl verilog -vivado_clock 1.3 -vivado_phys_opt all
export_design -flow impl -rtl verilog -format ip_catalog
close_project
exit
