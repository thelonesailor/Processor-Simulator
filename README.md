#-------MIPS-Processor-Simulator-------#

#----------How to Run----------#
1) Run command "make" to generate the executable file. 
2) Run using "./processor_simulator <input_HEX_file> <output_SVG_file>" (No result file printed) or
3) Run using "./processor_simulator <input_HEX_file> <output_SVG_file> <output_results_file>" (result file printed).

#---------Assumptions----------#
1) Hexadecimal numbers can have 'b' and but not 'B'.
2) If branch is the last instruction then 2 instruction penalty is counted if branch is taken,
	because it will continue to read from instruction stream.
3) Input instructions are hexadecimal numbers of length 8.
4) Program ends when all stages have invalid instuctions.
5) For a nop instruction(white in svg) signals highlighted should be ignored.
6) Any invalid input on terminal or input file will be reported.


#----------Commands----------#
1) Use "step" to go to next cycle.
2) Use "quit"/"exit" to end the program there, without any futher execution of hex program.
