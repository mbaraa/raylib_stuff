.PHONY: setup build

CC=gcc

CFLAGS+=-Wall -Wshadow
CFLAGS+=-Wpointer-arith -Wcast-qual -Wsign-compare
CFLAGS+=-lm -lraylib -lGL -lpthread -ldl -lrt -lX11
LDFLAGS+=-lm -lraylib -lGL -lpthread -ldl -lrt -lX11

BINARY_NAMR=snake

all: setup build

objects:
	$(CC) $(CFLAGS) -c ./src/*.c $(LDFLAGS)

build: objects
	$(CC) $(CFLAGS) *.o ./main.c -o $(BINARY_NAMR) $(LDFLAGS)

run: clean build
	./$(BINARY_NAMR)

setup:
	echo "idk dude"

clean:
	rm -rf *.o *.so $(BINARY_NAMR)
