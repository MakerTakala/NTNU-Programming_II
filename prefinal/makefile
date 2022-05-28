SRC = $(wildcard *.c)

all:$(SRC:.c=.o)
	-gcc prefin01.o file_processing.o -o prefin01
	./prefin01 < prefin01_input.txt
	make clean

.PHONY : new zip clean cleanexe

new:
	cp ../template.c hw0.c
	code hw0.c

clean:
	@-rm *.o

cleanexe:
	@-rm fin0?