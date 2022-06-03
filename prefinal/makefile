SRC = $(wildcard *.c)

all:$(SRC:.c=.o)
	-gcc prefin01.o file_processing.o -o prefin01
	-gcc img_hide.o file_processing.o -o img_hide
	./img_hide -e -b 8 output.bmp secret.txt
	make clean

.PHONY : new zip clean cleanexe

new:
	cp ../template.c hw0.c
	code hw0.c

clean:
	@-rm *.o

cleanexe:
	@-rm fin0?