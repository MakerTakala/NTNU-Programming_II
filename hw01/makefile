SRC = $(wildcard *.c)

all:$(SRC:.c=.o)
	gcc hw0101.o -o hw0101
	gcc hw0102.o -o hw0102
	make clean

.PHONY : new zip clean cleanexe

new:
	cp ../template.c hw0.c
	code hw0.c

zip:
	zip hw06 ./*.c ./*.pdf ./*.h makefile

clean:
	@-rm *.o

cleanexe:
	@-rm hw060?