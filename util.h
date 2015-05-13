#ifndef _UTIL_H_
#define _UTIL_H_

/* change these values as needed */
#define MAXNT 1500                /* Maximum number of nucleotides       */
#define MAXAA MAXNT/3             /* Maximum number of amino acids       */
#define MAXST 200                 /* Maximum size for ID and description */


struct sequence {
	char *id;
	char *desc;
	char *string;
	char type;
	int size;
};

typedef struct sequence Seq;

/* utility function prototypes */
char * ToUpper(char *st);
char Resolve_type(Seq *ps);
double dpow(double x, double y);
#endif
