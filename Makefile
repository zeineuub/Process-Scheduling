scheduling_policies_build = algorithms/build
scheduling_policies_source = algorithms/source
#target: dependecie
#action
#les fichiers objets eli netjin an amaliyet
#anytime the .o algo change we gonna recompile the files
#The sed command removes (that is, it replaces with the empty string) any string .png found at the end of a filename.
scheduling_policies_executables: algorithms/build/*.o
	@for file in  ${shell ls -1 *.o ${scheduling_policies_build} | sed 's/\.[a-z]*//g'}; do gcc ${scheduling_policies_build}/$${file}.o -o ${scheduling_policies_build}/$${file} ; done

#nlisti el contenu intaa directory source ou ncompilih ou nrodou .o bi nafs el ism ine3ou
# -c mean don't try a make an exe just compile it in to an object/ keep the name of the file
scheduling_policies.o: algorithms/source/*.c
	@for file in  ${shell ls -1 *.c ${scheduling_policies_source} | sed 's/\.[a-z]*//g'}; do gcc -c ${scheduling_policies_source}/$${file}.c -o ${scheduling_policies_build}/$${file}.o ; done

	
