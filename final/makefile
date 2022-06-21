SRC = $(wildcard *.c)

all:$(SRC:.c=.o)
	-gcc fin01.o file_processing.o -o fin01
	-gcc fin02.o file_processing.o -o fin02
	
	make clean

.PHONY : new zip clean cleanexe

new:
	cp ../template.c hw0.c
	code hw0.c

clean:
	@-rm *.o

cleanexe:
	@-rm fin0?