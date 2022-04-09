SRC = $(wildcard *.c)

all:$(SRC:.c=.o)
	gcc mid01.o mystring.o -o mid01
	gcc mid02.o mid_helper.o -o mid02
	gcc mid03.o mid_helper.o -o mid03 -lm
	gcc mid04.o mid_helper.o -o mid04
	make clean

.PHONY : new zip clean cleanexe

clean:
	@-rm *.o

cleanexe:
	@-rm mid0?