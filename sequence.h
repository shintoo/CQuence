/* sequence.h -- sequence ADT interface header file */
#ifndef _SEQUENCE_H_
#define _SEQUENCE_H_

#include <stdbool.h>

/* change these values as needed */
#define MAXNT 400                /* Maximum number of nucleotides       */
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

/* operation:      Fetch a sequence from a file                 */
/* preconditions:  ps is the address of a created sequence      */
/*                 fp points to a FASTA format file             */
/* postconditions: The sequence in fp is loaded into the        */
/*                 sequence pointed to by ps                    */
/*                 returns true if successful, otherwise false  */
bool Seq_fetch(Seq *ps, FILE *fp);

/* operation:      write a sequence to a file in FASTA format   */
/* preconditions:  ps points to a sequence that has been        */
/*                 fetched, transcribed to, or translated to    */
/* postconditions: file is written with the sequence            */
void Seq_write(Seq *ps, FILE *fp);

/* operation:      Transcribe a sequence of DNA into a sequence */
/*                 of RNA                                       */
/* preconditions:  pdna points to a sequence of type DNA        */
/*                 prna points to a sequence of type RNA        */
/* postconditions: the sequence pointed to by pdna is           */
/*                 transcribed into rna                         */
/*                 returns true if sueccessful, otherwise false */
bool Seq_transcribe(Seq *pdna, Seq *prna);


/* operation:      Translate a sequence of RNA into a protein   */
/*                 sequence                                     */
/* preconditions:  prna points to a sequence of type RNA        */
/*                 pprt points to a sequence of type PROTEIN    */
/* postconditions: the sequence pointed to by prna is           */
/*                 translated into the sequence pointed to by   */
/*                 pprt                                         */
/*                 returns true if successful, otherwise false  */
bool Seq_translate(Seq *prna, Seq *pprt);

#endif
