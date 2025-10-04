.PHONY: setup build

CC=gcc

CFLAGS+=-Wall -Wshadow
CFLAGS+=-Wpointer-arith -Wcast-qual -Wsign-compare
CFLAGS+=-lsqlite3 -lm -lraylib -lGL -lpthread -ldl -lrt -lX11
LDFLAGS+=-lsqlite3 -lm -lraylib -lGL -lpthread -ldl -lrt -lX11

BINARY_NAMR=pong

all: setup build

build:
	$(CC) $(CFLAGS) ./main.c -o $(BINARY_NAMR) $(LDFLAGS)

run: clean build
	./$(BINARY_NAMR)

setup:
	echo "idk dude"

clean:
	rm -rf *.o *.so $(BINARY_NAMR)
