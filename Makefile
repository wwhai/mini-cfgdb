cc = gcc
objects = cfgdb.o main.o 
cfgdb : ${objects}
	 ${cc} -o cfgdb ${objects}

.PHONY : clean
clean :
	-rm cfgdb ${objects}