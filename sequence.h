/* sequence.h -- sequence ADT interface header file */
#ifndef _SEQUENCE_H_
#define _SEQUENCE_H_

#include <stdbool.h>

/* change these values as needed */
#define MAXNT 1500                /* Maximum number of nucleotides       */
#define MAXAA MAXNT/3            /* Maximum number of amino acids       */
#define MAXST 200                 /* Maximum size for ID and description */

/* DO NOT CHANGE ANYTHING BEYOND THIS POINT */

struct sequence;
typedef struct sequence Seq;

/*                     functions                               */

/* operation:      Create a new sequence                       */
/* preconditions:  type is any capitalization of "DNA", "RNA", */
/*                 or "protein"                                */
/* postconditions: If the type is a valid typle, the function  */
/*                 returns the address of the created sequence.*/
/*                 Otherwise, if the type is not valid, the    */
/*                 function returns NULL                       */
Seq * Seq_new(char *type);

/* operation:      delete a sequence from memory                */
/* precondition:   ps points to a sequence                      */
/* postconditions: the sequence pointed to by ps is deleted     */
void Seq_delete(Seq *ps);

/* operation:      Set the ID of a sequence to a string         */
/* precondition:   ps points to a created sequence              */
/* postconditions: the ID of the sequence pointed to by ps is   */
/*                 set to the string                            */
void Seq_set_id(Seq *ps, char *ID);

/* operation:      Set the description of a sequence            */
/* precondition:   ps points to a created sequence              */
/* postcondition:  the description of the sequence pointed to   */
/*                 by ps is set to the string                   */
void Seq_set_description(Seq *ps, char *description);

/* operation:      Set the string of a sequence to a string     */
/* precondition:   ps points to a created sequence              */
/* postcondition:  the string of the sequence pointed to by ps  */
/*                 is set to the string                         */
void Seq_set_string(Seq *ps, char *string);

/* operation:      Get the ID of a sequence                     */
/* preconditions:  ps points to a created sequence              */
/* postconditions: the ID of the sequence pointed to by ps is   */
/*                 returned as a string                         */
char * Seq_get_id(Seq *ps);

/* operation:      Get the description of a sequence            */
/* precondition:   ps points to a created sequence              */
/* postcondition:  the description of the sequence pointed to   */
/*                 by ps is returned as a string                */
char * Seq_get_description(Seq *ps);

/* operation:      Get the string of a sequence                 */
/* precondition:   ps points to a created sequence              */
/* postcondition:  the string of the sequence pointed to by ps  */
/*                 is returned as a string                      */
char * Seq_get_string(Seq *ps);

/* operation:      Fetch a sequence from a file                 */
/* preconditions:  fasta points to a fasta format file          */
/*                 index is the index of the sequence to be     */
/*                 fetched                                      */
/* postconditions: The sequence indicated in the fasta file (0  */
/*                 is the first) is loaded, and it's address is */
/*                 returned                                     */
Seq * Seq_read_fasta(FILE *fasta);

/* operation:      write a sequence to a file in FASTA format   */
/* preconditions:  ps points to a sequence that has been        */
/*                 fetched, transcribed to, or translated to    */
/* postconditions: file is written with the sequence            */
void Seq_write_fasta(Seq *ps, FILE *fasta);

/* operation:      Get the GC content of a DNA or RNA sequence  */
/* preconditions:  pnt points to a DNA or RNA sequence          */
/* postconditions: the GC content of the string is returned     */
double Seq_gc(Seq *pnt);

/* operation:      Transcribe a sequence of DNA into a sequence */
/*                 of RNA                                       */
/* preconditions:  pdna points to a sequence of type DNA        */
/* postconditions: the function returns the address of the RNA  */
/*                 sequence that has been transcribed from the  */
/*                 DNA sequence  pointed to by pdna             */
Seq * Seq_transcribe(Seq *pdna);

/* operation:      Translate a sequence of RNA or DNA into a    */
/*                 protein sequence                             */
/* preconditions:  pnt points to a sequence of type RNA or DNA  */
/* postconditions: the sequence pointed to by pnt is            */
/*                 translated into a protein sequence whose     */
/*                 address is returned                          */
Seq * Seq_translate(Seq *pnt);

/* operation:      Reverse complement a string of DNA           */
/* preconditions:  pdna_original points to a DNA sequence       */
/* postconditions: the address of the reverse complement of the */
/*                  sequence pointed to by pdna is returned     */
Seq * Seq_complement(Seq *pdna);

#endif
