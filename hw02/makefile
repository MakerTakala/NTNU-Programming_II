SRC = $(wildcard *.c)

all:$(SRC:.c=.o)
	gcc hw0201.o mymatch.o -o hw0201
	gcc hw0202.o -o hw0202
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