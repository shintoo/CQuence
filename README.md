# CQuence
CQuence is a very simple library for handling biological sequences.
### Interface
CQuence interacts with sequences stored in the FASTA file format.  

#### Examples
##### Simple demonstration
```
#include <stdio.h>
#include "sequence.h"

int main(int argc, char **argv) {
	Seq *dna = Seq_new("dna");
	Seq *rna = Seq_new("RNA");
	Seq *protein = Seq_new("protein");
	FILE *fasta = fopen(argv[1], "r");

	printf("Fetching sequence from %s...\n", argv[1]);
	Seq_fetch(dna, fasta);
	puts("Transcribing DNA into RNA...");
	Seq_transcribe(dna, rna);
	puts("Translating RNA into protein...");
	Seq_translate(rna, protein);
	puts("Done!");
	
	fclose(fasta);
	Seq_delete(dna);
	Seq_delete(rna);
	Seq_delete(protein);
	return 0;
}    
```
