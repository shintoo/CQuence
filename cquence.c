/* sequence.c -- sequence ADT interface implementation file */
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "cquence.h"

struct sequence {
	char *id;
	char *desc;
	char *string;
	char type;
	int size;
};

const char *CODONTABLE = "FFLLSSSSYY**CC*WLLLLPPPPHHQQRRRRIIIMTTTTNNKKSSRRVVVVAAAADDEEGGGG";

/* Local function prototypes */
static char * ToUpper(char *st);
static char Resolve_type(Seq *ps);

/*        MANAGEMENT FUNCTIONS        */

/* creates a new sequence and returns the address */
Seq * Seq_new(char *type) {
	Seq *newSeq = malloc(sizeof(Seq));
	
	newSeq->type = toupper(type[0]);
	switch(newSeq->type) {
		case 'P':
			newSeq->string = (char *) malloc(MAXAA * sizeof(char));
			break;
		case 'U':                                                 /* unknown */
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
	free(ps->id);
	free(ps->desc);
	free(ps->string);
	free(ps);
}

/*        I/O FUNCTIONS        */

/* fetches sequence data from FASTA file */
Seq *  Seq_read_fasta(FILE *fasta) {
	Seq *ps = Seq_new("unknown");


	int i;
	fgetc(fasta);                                                 /* skip over '>'         */
	char ch = fgetc(fasta);
	for (i = 0; ch != ' ' && ch != '\n' && i < MAXST - 1; i++) {  /* fetch id              */
		ps->id[i] = ch;
		ch = fgetc(fasta);
	}
	ps->id[i] = '\0';
	if (ch != '\n') {
		ch = fgetc(fasta);
		for (i = 0; ch != '\n' && i < MAXST - 1; i++) {           /* fetch id              */
			ps->desc[i] = ch;
			ch = fgetc(fasta);
		}
		ps->desc[i] = '\0';
	}
	ch = fgetc(fasta);
	for (i = 0; !feof(fasta); i++) {                              /* fetch string          */
		if (ch == '\n') {
			ch = fgetc(fasta);
			i--;
			continue;
		}
		ps->string[i] = toupper(ch);
		ch = fgetc(fasta);
	}
	ps->type = Resolve_type(ps);
	if (ps->type == 'P') {
		ps->string = realloc(ps->string, MAXAA);
	}
	ps->size = i;
	return ps;
}

/* write a sequence to a file */
void Seq_write_fasta(Seq *ps, FILE *fasta) {
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

/*        OPERATION FUNCTIONS        */

/* transcribes DNA sequence into RNA */
Seq * Seq_transcribe(Seq *pdna) {
	char ch;
	
	Seq *prna = Seq_new("RNA");
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

	return prna;
}

/* translates RNA string into protein (amino acid) string */
Seq * Seq_translate(Seq *pnt) {
	char codon[3];
	double value = 0;
	double m;
	int aact = 0;
	Seq *prna;
	Seq *paa = Seq_new("protein");

	if (pnt->type == 'D') {
		prna = Seq_new("RNA");
		strcpy(prna->id, pnt->id);
		strcpy(prna->desc, pnt->desc);
		prna = Seq_transcribe(pnt);
		
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

	return paa;
}

/* reverse complements a DNA sequence */
Seq * Seq_complement(Seq *pdna) {
	Seq *pcomp =  Seq_new("DNA");
	
	pcomp->size = pdna->size;
	strcpy(pcomp->id, pdna->id);
	strcpy(pcomp->desc, pdna->desc);

	for (int i = pdna->size - 1; i >= 0; i--) {
		switch (pdna->string[i]) {
			case 'A': pcomp->string[pdna->size - i - 1] = 'T'; break;
			case 'T': pcomp->string[pdna->size - i - 1] = 'A'; break;
			case 'G': pcomp->string[pdna->size - i - 1] = 'C'; break;
			case 'C': pcomp->string[pdna->size - i - 1] = 'G'; break;
		}
	}
	
	return pcomp;
}

/*        INFORMATION FUNCTIONS        */

/* get the GC content percentage of a DNA or RNA sequence */
double Seq_gc(Seq *ps) {
	double gc = 0;
	
	if (ps->type == 'P') {
		return -1;
	}
	for (int i = 0; i < ps->size; i++) {
		if (ps->string[i] == 'C' || ps->string[i] == 'G') {
			gc++;
		}
	}
	gc = gc / (double) ps->size;

	return gc;
}

/*        GET FUNCTIONS        */

/* get the id of a sequnce */
char * Seq_get_id(Seq *ps) {
	return ps->id;
}

/* get the description of a sequence */
char * Seq_get_description(Seq *ps) {
	return ps->desc;
}

/* get the string of a sequence */
char * Seq_get_string(Seq *ps) {
	return ps->string;
}

/* SET FUNCTIONS */

/* set the id of a sequence to a string */
void Seq_set_id(Seq *ps, char *id) {
	strncpy(ps->id, id, MAXST);
}

/* set the description of a sequence to a string */
void Seq_set_description(Seq *ps, char *desc) {
	strncpy(ps->desc, desc, MAXST);
}

/* set the AA/base string of a sequence to a string */
void Seq_set_string(Seq *ps, char *string) {
	string = ToUpper(string);
	ps->size = strlen(string);
	strncpy(ps->string, string, MAXST);

}


/*        LOCAL FUNCTIONS        */
static char * ToUpper(char *str) {
	int length = strlen(str);
	char *new =  (char *) malloc(sizeof(char) * strlen(str));

	for (int i = 0; i < length; i++) {
		new[i] = toupper(str[i]);
	}
	
	return new;
}

static char Resolve_type(Seq *ps) {
	for (int i = 0; i < ps->size; i++) {
		if (ps->string[i] == 'U') {
			return 'R';
		}
		if (strchr("acgt", ps->string[i]) == NULL) {
			return 'P';
		}
	}
	return 'D';
}
