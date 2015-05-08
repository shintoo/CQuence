# CQuence
CQuence is a very simple library for handling biological sequences.
### Interface
CQuence interacts with sequences stored in the FASTA file format.  

```  
Seq *seq;
FILE *fin = fopen("infile", "r");
FILE *fout = fopen("outfile", "w");

/* Read a sequence from a fasta file */
seq = Seq_read_fasta(fin);

/* Write a sequence to a fasta file */
Seq_write_fasta(seq, fout);

/* Create a new sequence from scratch */
Seq *dna = Seq_new("DNA");
Seq *rna = Seq_new("RNA");
Seq *protein = Seq_new("protein");

/* Set a sequence ID */
Seq_set_id(dna, "dna_ID");

/* Set a sequence description */
Seq_set_description(seq, "dna description");

/* Set a sequence string */
Seq_set_string(dna, "ACTGACTG");

/* Get a sequence ID */
char *id;
id = Seq_get_id(seq);

/* Get a sequence description */
char *description;
description = Seq_get_description(seq);

/* Get a sequence string */
char *string;
string = Seq_get_string(seq);

/* Transcribe a sequence */
rna = Seq_transcribe(dna);

/* Translate a DNA sequence */
protein = Seq_translate(dna);

/* Translate an RNA sequence */
protein = Seq_translate(rna);

/* Get the GC content of a DNA or RNA sequence */
double dna_gc;
dna_gc = Seq_gc(dna);

/* Get the reverse complement of a DNA sequence */
Seq * dna_revc;
dna_revc = Seq_complement(dna);  

/* Delete a sequence from memory */
Seq_delete(seq)
```  

#### Examples
##### Simple demonstration
```
#include <stdio.h>
#include "sequence.h"

int main(int argc, char **argv) {
	FILE *infasta = fopen(argv[1], "r");
	FILE *outfasta = fopen(argv[2], "w");
	Seq *dna;
	Seq *rna;
	Seq *protein1;
	Seq *protein2;
	Seq *newdna;
	Seq *newdna_revc;

	/* Read a sequence from a fasta */
	dna = Seq_read_fasta(infasta);

	/* Transcribe DNA to RNA */
	rna = Seq_transcribe(dna);
	
	/* Translate from RNA to protein */
	protein1 = Seq_translate(rna);

	/* Translate from DNA to protein */
	protein2 = Seq_translate(dna);

	/* Change the ID and description of rna and proteins.     */
	/* ID and description default to the ID and description   */
	/* of the sequences they were transcribed/translated from.*/
	Seq_set_id(rna, "sample_rna");
	Seq_set_description(rna, "sample rna description");

	Seq_set_id(protein1, "sample_protein1");
	Seq_set_description(protein1, "sample protein1 description");

	Seq_set_id(protein2, "sample_protein2");
	Seq_set_description(protein2, "sample protein2 description");

	/* write RNA and protein to fasta file */
	Seq_write_fasta(rna, outfasta);
	Seq_write_fasta(protein1, outfasta);

	/* Create new DNA sequence */
	newdna = Seq_new("DNA");
	Seq_set_id(newdna, "sample2_dna");
	Seq_set_description(newdna, "sample2 dna description");
	Seq_set_string(newdna, "ACATGTCGA");

	/* Write newdna to fastaout */
	Seq_write_fasta(newdna, outfasta);

	/* Create a reverse complement of newdna */
	newdna_revc = Seq_complement(newdna);
	Seq_set_id(newdna_revc, "sample2_dna_reverse_complement");
	Seq_set_description(newdna_revc, "sample2 dna reverse complement description");
	Seq_write_fasta(newdna_revc, outfasta);
	
	/* Clean up */
	Seq_delete(dna);
	Seq_delete(rna);
	Seq_delete(protein1);
	Seq_delete(protein2);
	Seq_delete(newdna);
	Seq_delete(newdna_revc);
	fclose(infasta);
	fclose(outfasta);
	
	return 0;
}  
```
With the input file:
```
>sample_id sample description
TGTCAGAATTGTATTTCAGGCCGAGAAGCCACTACTGCCGAACGAGGCTCAATTTGTAAT
CAGTGTATACACCCTATAACTATTTCTCTTATTAAGGAAGACGCTAACGACACTCATGCT
ACCATTTGTGCTAATATGGCCAAGGAACGTGAAGCTCTTCTATACGGTCGTGAAGCTACT
```
Creates the output file:  
```
>sample_rna sample rna description
UGUCAGAAUUGUAUUUCAGGCCGAGAAGCCACUACUGCCGAACGAGGCUCAAUUUGUAAU
CAGUGUAUACACCCUAUAACUAUUUCUCUUAUUAAGGAAGACGCUAACGACACUCAUGCU
ACCAUUUGUGCUAAUAUGGCCAAGGAACGUGAAGCUCUUCUAUACGGUCGUGAAGCUACU
>sample_protein1 sample protein1 description
CQNCISGREATTAERGSICNQCIHPITISLIKEDANDTHATICANMAKEREALLYGREAT
>sample2_dna sample2 dna description
ACATGTCGA
>sample2_dna_reverse_complement sample2 dna reverse complement description
TCGACATGT  
```
