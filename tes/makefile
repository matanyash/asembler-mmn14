my_program:	 test.o function.o binDataString.o global.o function.h define.h typedef.h test.h
	gcc -g -ansi -Wall -pedantic test.o function.o binDataString.o global.o -o my_program.o

test.o:	 test.c function.h binDataString.h global.h test.h
	gcc -c -ansi -Wall -pedantic test.c -o test.o

function.o: function.c function.h global.h
	gcc -c -ansi -Wall -pedantic function.c -o function.o

binDataString.o: binDataString.c lib.h binDataString.h
	gcc -c -ansi -Wall -pedantic binDataString.c -o binDataString.o

global.o: global.c global.h
	gcc -c ansi -Wall -pedantic  global.c -o global.o
