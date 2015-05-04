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
typedef struct sequence * Sequence;

/* operation:      Initialize a sequence to the specified type */
/* preconditions:  ps points to a sequence                     */
/*                 type is either 'd', 'D', 'r', 'R', 'p',     */
/*                 or 'P'                                      */
/* postconditions: If the type is a valid typle, the sequence  */
/*                 is initialized and the function returns     */
/*                 true; otherwise, if the type is not valid,  */
/*                 the function returns false                  */
bool SequenceInit(Sequence ps, char *type);

/* operation:      Fetch a sequence from a file                 */
/* preconditions:  ps points to a sequence                      */
/*                 fp points to a FASTA format file             */
/* postconditions: The sequence in fp is loaded into the        */
/*                 sequence pointed to by ps, returns true      */
bool SequenceFetch(Sequence ps, FILE *fp);

/* operation:      Transcribe a sequence of DNA into a sequence */
/*                 of RNA                                       */
/* preconditions:  pdna points to an initialized sequence of    */
/*                                                    type D    */
/*                 prna points to an initialized sequence of    */
/*                                                    type R    */
/* postconditions: The sequence pointed to by pdna is           */
/*                 transcribed into the sequence pointed to by  */
/*                 prna. Returns true if preconditions met,     */
/*                 false otherwise                              */

bool Transcribe(Sequence pdna, Sequence prna);


/* operation:      Translate a sequence of RNA into a protein   */
/*                 sequence                                     */
/* preconditions:  pdna points to an initialized sequence of    */
/*                                                    type D    */
/*                 pprt points to an iinitialized sequence of   */
/*                                                    type P    */
bool Translate(Sequence prna, Sequence pprt);

#endif
