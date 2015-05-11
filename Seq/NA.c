#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#include "NA.h"
#include "General.h"
#include "../util.h"
extern char *CODONTABLE;

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
			case '-': pcomp->string[pdna->size - i - 1] = '-'; break;	
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
