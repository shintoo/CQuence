#ifndef _NA_H_
#define _NA_H_

struct sequence;
typedef struct sequence Seq;

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


/* operation:      Get the GC content of a DNA or RNA sequence  */
/* preconditions:  pnt points to a DNA or RNA sequence          */
/* postconditions: the GC content of the string is returned     */
double Seq_gc(Seq *pnt);

#endif
