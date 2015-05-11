CC=gcc
CFLAGS = -c -Wall -std=c11
LIBFLAGS = -lm
LIBDIR= /usr/lib
INCLUDE= /usr/include

SRCFILES= Seq/NA.c Seq/General.c SeqIO/FASTA.c util.c
OBJ= NA.o General.o FASTA.o util.o
HEADERS= Seq/NA.h Seq/General.h SeqIO/FASTA.h util.h

all: libcq.a

uninstall:
	rm -rf $(INCLUDE)/cq
	rm $(LIBDIR)/libcq.a

install: libcq.a $(HEADERS)
	cp libcq.a $(LIBDIR)
	mkdir $(INCLUDE)/cq
	cp cq.h $(INCLUDE)/cq
	cp util.h $(INCLUDE)/cq
	cp Seq.h $(INCLUDE)/cq
	cp SeqIO.h $(INCLUDE)/cq
	mkdir $(INCLUDE)/cq/Seq
	cp Seq/General.h $(INCLUDE)/cq/Seq
	cp Seq/NA.h $(INCLUDE)/cq/Seq
	mkdir $(INCLUDE)/cq/SeqIO
	cp SeqIO/FASTA.h $(INCLUDE)/cq/SeqIO
	
libcq.a: $(OBJ)
	ar -cvq libcq.a $(OBJ)

$(OBJ): $(HEADERS) 
	$(CC) $(CFLAGS) $(SRCFILES) $(LIBFLAGS);



clean:
	rm *.o
	rm *.a
