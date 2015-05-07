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
			return NULL;
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
bool Seq_fetch(Seq *ps, FILE *fasta) {
	if (fgetc(fasta) != '>') {                                       /* file must be FASTA    */
		return false;
	}
	if (ps->type != 'D' && ps->type != 'R' && ps->type != 'P') {  /* ps must be created    */
		return false;
	}
	int i;
	char ch = fgetc(fasta);
	for (i = 0; ch != ' ' && ch != '\n' && i < MAXST - 1; i++) {  /* fetch id              */
		ps->id[i] = ch;
		ch = fgetc(fasta);
	}
	ps->id[i] = '\0';
	if (ch != '\n') {
		ch = fgetc(fasta);
		for (i = 0; ch != '\n' && i < MAXST - 1; i++) {  /* fetch id              */
			ps->desc[i] = ch;
			ch = fgetc(fasta);
		}
		ps->desc[i] = '\0';
	}
	ch = fgetc(fasta);
	for (i = 0; !feof(fasta); i++) {                                 /* fetch string          */
		if (ch == '\n') {
			ch = fgetc(fasta);
			i--;
			continue;
		}
		ps->string[i] = toupper(ch);
		ch = fgetc(fasta);
	}
	ps->size = i;
	return true;
}

/* write a sequence to a file */
void Seq_write(Seq *ps, FILE *fasta) {
	int i;

	fprintf(fasta, ">%s %s\n", ps->id, ps->desc);
	for (i = 0; i < ps->size; i++) {
		fputc(ps->string[i], fasta);
		if ((i + 1) % 60 == 0) {
			fputc('\n', fasta);
		}
	}
	if (i % 60 != 0) {
		fputc('\n', fasta);
	}
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
bool Seq_translate(Seq *pnt, Seq *paa) {
	char codon[3];
	char ch;
	double value = 0;
	double m;
	int aact = 0;
	Seq *prna;

	if ((pnt->type != 'R' && pnt->type != 'D') || paa->type != 'P') {
		return false;
	}
	if (pnt->type == 'D') {
		prna = Seq_new("RNA");
		strcpy(prna->id, pnt->id);
		strcpy(prna->desc, pnt->desc);
		Seq_transcribe(pnt, prna);
	}
	else {
		prna = pnt;
	}
	strcpy(paa->id, prna->id);
	strcpy(paa->desc, prna->desc);
	for (int i = 0; i < prna->size + 1 && i < MAXNT; i++) {
		for (int cindex = 0; cindex < 3; cindex++) {
			codon[cindex] = prna->string[i + cindex];
		}
		i += 2;
		for (int cindex = 0; cindex < 3; cindex++) {
			m = pow(4, cindex);
			switch(codon[2 - cindex]) {
				case 'C': value += 1 * m; break;
				case 'A': value += 2 * m; break;
				case 'G': value += 3 * m; break;
			}
		}
		paa->string[aact] = CODONTABLE[(int)value];
		aact++;
		value = 0;
	}
	paa->size = aact - 1;
	return true;
}
