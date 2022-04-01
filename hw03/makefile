SRC = $(wildcard *.c)

all:$(SRC:.c=.o)
	gcc hw0301.o -o hw0301
	
	gcc hw0303.c -o hw0303 -lm
	-./hw0303 < hw0303_testcase.txt
	make clean

.PHONY : new zip clean cleanexe

new:
	cp ../template.c hw0.c
	code hw0.c

clean:
	@-rm *.o

cleanexe:
	@-rm hw060?