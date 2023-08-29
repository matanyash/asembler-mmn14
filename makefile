my_program:	 test.o function.o binDataString.o lib.h function.h define.h typedef.h 
	gcc -g -ansi -Wall -pedantic test.o function.o binDataString.o -o my_program.o

test.o:	 test.c function.h lib.h binDataString.h
	gcc -c -ansi -Wall -pedantic test.c -o test.o

function.o: function.c function.h lib.h
	gcc -c -ansi -Wall -pedantic function.c -o function.o

binDataString.o: binDataString.c lib.h binDataString.h
	gcc -c -ansi -Wall -pedantic binDataString.c -o binDataString.o


