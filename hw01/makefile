SRC = $(wildcard *.c)

all:$(SRC:.c=.o)
	gcc hw0101.o -o hw0101
	gcc hw0102.o -o hw0102
	gcc hw0103.o mystring.o -o hw0103
	gcc hw0104.o mystring.o -o hw0104
	gcc hw0105.o mysplit.o -o hw0105
	gcc hw0106.c -o hw0106
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