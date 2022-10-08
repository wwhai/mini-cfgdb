cc = gcc
objects = cfgdb.o hashmap.o main.o

.PHONY : cfgdb
cfgdb : ${objects}
		${cc} -o cfgdb ${objects}

.PHONY : clean
clean :
		rm cfgdb ${objects}