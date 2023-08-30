my_program:	 test.o function.o binDataString.o global.o MacrosTable.o PreAssembler.o utils.o utils.h PreAssembler.h MacrosTable.c data.h  function.h define.h typedef.h transitions.h
	gcc -g -ansi -Wall -pedantic PreAssembler.o utils.o MacrosTable.o test.o function.o binDataString.o global.o  -o my_program.o

test.o:	 transitions.c function.h binDataString.h global.h transitions.h
	gcc -c -ansi -Wall -pedantic test.c -o test.o

function.o: function.c function.h global.h
	gcc -c -ansi -Wall -pedantic function.c -o function.o

binDataString.o: binDataString.c lib.h binDataString.h
	gcc -c -ansi -Wall -pedantic binDataString.c -o binDataString.o

global.o: global.c global.h
	gcc -c -ansi -Wall -pedantic  global.c -o global.o

MacrosTable.o:	MacrosTable.c data.h
	gcc -c -ansi -Wall -pedantic MacrosTable.c -o MacrosTable.o

PreAssembler.o:	PreAssembler.h PreAssembler.c transitions.h data.h
	gcc -c -ansi -Wall -pedantic PreAssembler.c -o PreAssembler.o

utils.o:	utils.c utils.h data.h
	gcc -c -ansi -Wall -pedantic utils.c -o utils.o