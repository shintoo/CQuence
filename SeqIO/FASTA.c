#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "FASTA.h"
#include "../Seq/General.h"
#include "../util.h"

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
