SRC = $(wildcard *.c)

all:$(SRC:.c=.o)
	gcc hw0301.o -o hw0301
	gcc hw0302.o -o hw0302
	gcc hw0303.o -o hw0303 -lm
	gcc hw0304.o -o hw0304
	gcc hw0305.c -o hw0305
	gcc hw0306_example.c -o hw0306_example -lm
	gcc hw0306_sample.c -o hw0306_sample -lm
	make clean

.PHONY : new zip clean cleanexe

new:
	cp ../template.c hw0.c
	code hw0.c

clean:
	@-rm *.o

cleanexe:
	@-rm hw060?