/* sequence.c -- sequence ADT interface implementation file */
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "sequence.h"

const char *CODONTABLE = "FFLLSSSSYY**CC*WLLLLPPPPHHQQRRRRIIIMTTTTNNKKSSRRVVVVAAAADDEEGGGG";

static char * ToUpper(char *st);

bool SeqInit(Seq ps, char *type) {
//	if (ps->id != NULL) {
//		return false;
//	}

	type = ToUpper(type);
	int typelen = strlen(type);
	if (strncmp("PROTEIN",type, typelen) == 0) {
		ps->string = (char *) malloc(MAXAA * sizeof(char));
	}
	else if (strncmp("DNA", type, typelen) == 0 || strncmp("RNA", type, typelen) == 0) {
		ps->string = (char *) malloc(MAXNT * sizeof(char));
	}
	else {
		return false;
	}

	ps->id = (char *) malloc(MAXST * sizeof(char));
	ps->desc = (char *) malloc(MAXST * sizeof(char));
	ps->type = type[0];
	ps->size = 0;
	return true;
}

bool SeqFetch(Seq ps, FILE *fp) {
	if (fgetc(fp) != '>') {
		return false;
	}
	int i;
	char ch = fgetc(fp);
	for (i = 0; ch != ' '; i++) {
		ps->id[i] = ch;
		ch = fgetc(fp);
	}
	ch = fgetc(fp);
	for (i = 0; ch != '\n'; i++) {
		ps->desc[i] = ch;
		ch = fgetc(fp);
	}
	ch = fgetc(fp);
	for (i = 0; !feof(fp); i++) {
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

bool SeqTranscribe(Seq dna, Seq rna) {
	char ch;

	if (dna->type != 'D' || rna->type != 'R') {
		return false;
	}
	strcpy(rna->id, dna->id);
	strcpy(rna->desc, dna->desc);
	rna->size = dna->size;
	for (int i = 0; i < dna->size; i++) {
		ch = dna->string[i];
		if (ch == 'T') {
			rna->string[i] = 'U';
		}
		else {
			rna->string[i] = ch;
		}
	}

	return true;
}

bool SeqTranslate(Seq rna, Seq prt) {
	char codon[3];
	char ch;
	double value = 0;
	double m;
	int prtct = 0;

	if (rna->type != 'R' || prt->type != 'P') {
		return false;
	}
	strcpy(prt->id, rna->id);
	strcpy(prt->desc, rna->desc);
	for (int i = 0; i < rna->size; i++) {
		for (int cindex = 0; cindex < 3; cindex++) {
			codon[i] = rna->string[i + cindex];
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
		prt->string[prtct++] = CODONTABLE[(int)value];
	}
	prt->size = prtct;
	return true;
}

static char * ToUpper(char *str) {
	while (*str++) {
		*str = toupper(*str);
	}
}
