/* sequence.c -- sequence ADT interface implementation file */
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "sequence.h"

const char *CODONTABLE = "FFLLSSSSYY00CC0WLLLLPPPPHHQQRRRRIIIMTTTTNNKKSSRRVVVVAAAADDEEGGGG";

static char * ToUpper(char *st);

bool SequenceInit(Sequence ps, char *type) {
	if (ps->id != NULL) {
		return false;
	}

	type = ToUpper(type);
	if (strncmp("PROTEIN",type, 7) == 0) {
		ps->string = (char *) malloc(MAXAA * sizeof(char));
	}
	else if (strncmp("DNA", type, 3) == 0 || strncmp("RNA", type, 3) == 0) {
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

bool SequenceFetch(Sequence ps, FILE *fp) {
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
		ps->string[i] = ch;
		ch = fgetc(fp);
	}
	ps->size = i;
	return true;
}

bool Transcribe(Sequence pdna, Sequence prna) {
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

bool Translate(Sequence prna, Sequence pprt) {
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
