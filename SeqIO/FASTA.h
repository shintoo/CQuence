#ifndef _FASTA_H_
#define _FASTA_H_

struct sequence;
typedef struct sequence Seq;

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

#endif
