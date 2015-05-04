/* sequence.h -- sequence ADT interface header file */
#ifndef _SEQUENCE_H_
#define _SEQUENCE_H_

#include <stdbool.h>

/* change these values as needed */
#define MAXNT 300                /* Maximum number of nucleotides       */
#define MAXAA MAXNT/3            /* Maximum number of amino acids       */
#define MAXST 50                 /* Maximum size for ID and description */


struct sequence {
	char *id;
	char *desc;
	char *string;
	char type;
	int size;
};
typedef struct sequence * Seq;

/* operation:      Initialize a sequence to the specified type */
/* preconditions:  sequence is a sequence                      */
/*                 type is any capitalization of "DNA", "RNA", */
/*                 or "protein"                                */
/* postconditions: If the type is a valid typle, the sequence  */
/*                 is initialized and the function returns     */
/*                 true; otherwise, if the type is not valid,  */
/*                 the function returns false                  */
bool SeqInit(Seq sequence, char *type);

/* operation:      Fetch a sequence from a file                 */
/* preconditions:  sequence is an initialized sequenc           */
/*                 fp points to a FASTA format file             */
/* postconditions: The sequence in fp is loaded into the        */
/*                 sequence, returns true                       */
bool SeqFetch(Seq sequence, FILE *fp);

/* operation:      Transcribe a sequence of DNA into a sequence */
/*                 of RNA                                       */
/* preconditions:  dna is an initialized sequence of type DNA   */
/*                 rna is an initialized sequence of type RNA   */
/* postconditions: dna is transcribed into rna                  */
bool SeqTranscribe(Seq dna, Seq rna);


/* operation:      Translate a sequence of RNA into a protein   */
/*                 sequence                                     */
/* preconditions:  pdna points to an initialized sequence of    */
/*                 type DNA                                     */
/*                 pprt is an iinitialized sequence of type     */
/*                 PROTEIN                                      */
bool SeqTranslate(Seq rna, Seq prt);

#endif
