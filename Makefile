scheduling_policies_build = algorithms/build
scheduling_policies_source = algorithms/source
#target: dependecie
#action

#nlisti el contenu intaa directory source ou ncompilih ou nrodou .o bi nafs el ism ine3ou
# Compile all the files under the directory "source" to an executables files
scheduling_policies_executables: algorithms/source/*.c
	@for file in  ${shell ls -1 *.c ${scheduling_policies_source} | sed 's/\.[a-z]*//g'}; do gcc ${scheduling_policies_source}/$${file}.c -o ${scheduling_policies_build}/$${file} ; done

permissions:
	chmod 755 algorithms
	chmod 755 main.c
	chmod 755 process.h
	chmod 755 Makefile
	chmod 755 params.txt
