/* sequence.c -- sequence ADT interface implementation file */
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "sequence.h"

struct sequence {
	char *id;
	char *desc;
	char *string;
	char type;
	int size;
};

const char *CODONTABLE = "FFLLSSSSYY**CC*WLLLLPPPPHHQQRRRRIIIMTTTTNNKKSSRRVVVVAAAADDEEGGGG";

static char * ToUpper(char *st);

/* creates a new sequence and returns the address */
Seq * Seq_new(char *type) {
	Seq *newSeq = malloc(sizeof(Seq));
	
	newSeq->type = toupper(type[0]);
	switch(newSeq->type) {
		case 'P':
			newSeq->string = (char *) malloc(MAXAA * sizeof(char));
			break;
		case 'D':
		case 'R':
			newSeq->string = (char *) malloc(MAXNT * sizeof(char));
			break;
		default:
			return false;
	}
	newSeq->id = (char *) malloc(MAXST * sizeof(char));
	newSeq->desc = (char *) malloc(MAXST * sizeof(char));
	newSeq->size = 0;
	return newSeq;
}

/* deletes a sequence from memory */
void Seq_delete(Seq *ps) {
	free(ps);
}

/* fetches sequence data from FASTA file */
bool Seq_fetch(Seq *ps, FILE *fp) {
	if (fgetc(fp) != '>') {                                       /* file must be FASTA    */
		return false;
	}
	if (ps->type != 'D' && ps->type != 'R' && ps->type != 'P') {  /* ps must be created    */
		return false;
	}
	int i;
	char ch = fgetc(fp);
	for (i = 0; ch != ' '; i++) {                                 /* fetch id              */
		ps->id[i] = ch;
		ch = fgetc(fp);
	}
	ch = fgetc(fp);
	for (i = 0; ch != '\n'; i++) {                                /* fetch description     */
		ps->desc[i] = ch;
		ch = fgetc(fp);
	}
	ch = fgetc(fp);
	for (i = 0; !feof(fp); i++) {                                 /* fetch string          */
		if (ch == '\n') {
			ch = fgetc(fp);
			continue;
		}
		ps->string[i] = ch;
		ch = fgetc(fp);
	}
	ps->size = i;
	return true;
}

/* transcribes DNA sequence into RNA */
bool Seq_transcribe(Seq *pdna, Seq *prna) {
	char ch;

	if (pdna->type != 'D' || prna->type != 'R') {
		return false;
	}
	strcpy(prna->id, pdna->id);
	strcpy(prna->desc, pdna->desc);
	prna->size = pdna->size;
	for (int i = 0; i < pdna->size; i++) {
		ch = pdna->string[i];
		if (ch == 'T') {
			prna->string[i] = 'U';
		}
		else {
			prna->string[i] = ch;
		}
	}

	return true;
}

/* translates RNA string into protein (amino acid) string */
bool Seq_translate(Seq *prna, Seq *pprt) {
	char codon[3];
	char ch;
	double value = 0;
	double m;
	int prtct = 0;

	if (prna->type != 'R' || pprt->type != 'P') {
		return false;
	}
	strcpy(pprt->id, prna->id);
	strcpy(pprt->desc, prna->desc);
	for (int i = 0; i < prna->size; i++) {
		for (int cindex = 0; cindex < 3; cindex++) {
			codon[i] = prna->string[i + cindex];
		}
		i += 3;
		for (int cindex = 0; cindex < 3; cindex++) {
			m = pow(4, cindex);
			switch(codon[cindex]) {
				case 'C':	value += 1 * m; break;
				case 'A':	value += 2 * m; break;
				case 'G':	value += 3 * m; break;
			}
		}
		pprt->string[prtct++] = CODONTABLE[(int)value];
	}
	pprt->size = prtct;
	return true;
}

static char * ToUpper(char *str) {
	while (*str++) {
		*str = toupper(*str);
	}
}
