#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "util.h"

char *CODONTABLE = "FFLLSSSSYY**CC*WLLLLPPPPHHQQRRRRIIIMTTTTNNKKSSRRVVVVAAAADDEEGGGG";

/*        LOCAL FUNCTIONS        */
char * ToUpper(char *str) {
	int length = strlen(str);
	char *new =  (char *) malloc(sizeof(char) * strlen(str));

	for (int i = 0; i < length; i++) {
		new[i] = toupper(str[i]);
	}
	
	return new;
}

char Resolve_type(Seq *ps) {
	for (int i = 0; i < ps->size; i++) {
		if (ps->string[i] == 'U') {
			return 'R';
		}
		if (strchr("ACGT", ps->string[i]) == NULL) {
			return 'P';
		}
	}
	return 'D';
}
