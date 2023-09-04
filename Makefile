#MIT License
#
#Copyright (c) 2023 shadai-rafael

CC=gcc

OBJECTS=compiler.o\
	cprocess.o\
	./utils/vector.o\
	./utils/buffer.o\
	lex_process.o\
	lexer.o

OBJECTS_TEST=./tests/cprocess_test.o

INCLUDE=-I./ -I./utils
INCLUDE_TEST= -I/usr/local/include/unity/

all: ${OBJECTS} ${OBJECTS_TEST}
	${CC} main.c ${INCLUDE} ${OBJECTS} -g -o main
	${CC} ./tests/maintest.c ${INCLUDE} ${INCLUDE_TEST} ${OBJECTS_TEST} ${OBJECTS} -lunity -g -o test

%.o: %.c
	$(CC) -c -o $@ $< ${INCLUDE_TEST}

.PHONY: clean
clean:
	rm -rf *.o
	rm -rf tests/*.o
	rm main 2>/dev/null
	rm test 2>/dev/null