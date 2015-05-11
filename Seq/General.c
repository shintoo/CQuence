#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "General.h"
#include "../util.h"

/*        MANAGEMENT FUNCTIONS        */

/* creates a new sequence and returns the address */
Seq * Seq_new(char *type) {
	Seq *newSeq = malloc(sizeof(Seq));
	
	newSeq->type = toupper(type[0]);
	switch(newSeq->type) {
		case 'P':
			newSeq->string = (char *) malloc(MAXAA * sizeof(char));
			break;
		case 'U':                                                 /* unknown */
		case 'D':
		case 'R':
			newSeq->string = (char *) malloc(MAXNT * sizeof(char));
			break;
		default:
			return NULL;
	}
	newSeq->id = (char *) malloc(MAXST * sizeof(char));
	newSeq->desc = (char *) malloc(MAXST * sizeof(char));
	newSeq->size = 0;
	return newSeq;
}

/* deletes a sequence from memory */
void Seq_delete(Seq *ps) {
	free(ps->id);
	free(ps->desc);
	free(ps->string);
	free(ps);
}
/*        GET FUNCTIONS        */

/* get the id of a sequnce */
char * Seq_get_id(Seq *ps) {
	return ps->id;
}

/* get the description of a sequence */
char * Seq_get_description(Seq *ps) {
	return ps->desc;
}

/* get the string of a sequence */
char * Seq_get_string(Seq *ps) {
	return ps->string;
}

/* SET FUNCTIONS */

/* set the id of a sequence to a string */
void Seq_set_id(Seq *ps, char *id) {
	strncpy(ps->id, id, MAXST);
}

/* set the description of a sequence to a string */
void Seq_set_description(Seq *ps, char *desc) {
	strncpy(ps->desc, desc, MAXST);
}

/* set the AA/base string of a sequence to a string */
void Seq_set_string(Seq *ps, char *string) {
	string = ToUpper(string);
	ps->size = strlen(string);
	strncpy(ps->string, string, MAXST);

}
