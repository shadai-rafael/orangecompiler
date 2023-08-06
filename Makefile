CC=gcc
OBJECTS=compiler.o\
	cprocess.o\
	./utils/vector.o\
	./utils/buffer.o
INCLUDE=-I./ -I./utils

all: ${OBJECTS}
	${CC} main.c ${INCLUDE} ${OBJECTS} -g -o ./main

%.o: %.c
	$(CC) -c -o $@ $< 

.PHONY: clean
clean:
	rm -rf *.o
	rm ./main
