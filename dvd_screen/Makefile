.PHONY: setup build

CC=gcc

CFLAGS+=-Wall -Wmissing-declarations -Wshadow
CFLAGS+=-Wstrict-prototypes -Wmissing-prototypes
CFLAGS+=-Wpointer-arith -Wcast-qual -Wsign-compare
CFLAGS+=-lm -lraylib -lGL -lpthread -ldl -lrt -lX11
LDFLAGS+=-lm -lraylib -lGL -lpthread -ldl -lrt -lX11

BINARY_NAMR=dvd_screen

all: setup build

build:
	$(CC) $(CFLAGS) ./main.c -o $(BINARY_NAMR) $(LDFLAGS)

run: clean build
	./$(BINARY_NAMR)

clean:
	rm -rf *.o *.so $(BINARY_NAMR)
