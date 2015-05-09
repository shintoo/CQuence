CC=gcc
CFLAGS = -c -Wall -std=c11 -lm
LIBDIR= /usr/lib
INCLUDE= /usr/include

all: libcquence.a

install:
	cp libcquence.a $(LIBDIR)

libcquence.a: cquence.o
	ar -cvq libcquence.a cquence.o

cquence.o: header
	$(CC) $(CFLAGS) cquence.c -o cquence.o 

header:
	cp cquence.h $(INCLUDE)

clean:
	rm *.o
	rm *.o
