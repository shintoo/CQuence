#ifndef _GENERAL_H_
#define _GENERAL_H_

struct sequence;
typedef struct sequence Seq;

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

#endif
