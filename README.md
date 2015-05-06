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
	Seq *dna = Seq_new("DNA");
	Seq *rna = Seq_new("RNA");
	Seq *protein = Seq_new("protein");
	FILE *fastain = fopen(argv[1], "r");
	FILE *fastaout = fopen(argv[2], "w");

	printf("Fetching sequence from %s...\n", argv[1]);
	Seq_fetch(dna, fastain);

	puts("Transcribing DNA into RNA...");
	Seq_transcribe(dna, rna);
	Seq_write(rna, fastaout);

	puts("Translating RNA into protein...");
	Seq_translate(rna, protein);
	Seq_write(protein, fastaout);
	
	puts("Done!");
	
	fclose(fastain);
	fclose(fastaout);
	Seq_delete(dna);
	Seq_delete(rna);
	Seq_delete(protein);
	return 0;
}  
```  
With an input file of:  
```
>sample_id sample description
TGTCAGAATTGTATTTCAGGCCGAGAAGCCACT  
```  
The output file created:  
```  
>sample_id sample description  
UGUCAGAAUUGUAUUUCAGGCCGAGAAGCCACU  
>sample_id sample description  
CQNCISGREAT  
```
