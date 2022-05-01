SRC = $(wildcard *.c)

all:$(SRC:.c=.o)
	-gcc hw0401.o file_processing.o -o hw0401
	-gcc hw0402.o file_processing.o -o hw0402
	-gcc hw0403.o file_processing.o -o hw0403
	-gcc hw0404.o -o hw0404

	make clean

.PHONY : new zip clean cleanexe

new:
	cp ../template.c hw0.c
	code hw0.c

clean:
	@-rm *.o

cleanexe:
	@-rm hw040?