#ifndef UNBOUNDED_INT_H_
#define UNBOUNDED_INT_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define new_ui_string string2unbounded_int
#define new_ui_ll ll2unbounded_int
#define ui_to_string unbounded_int2string
#define est_plus_grand unbounded_int_cmp_unbounded_int


typedef struct chiffre{
	struct chiffre *suivant;
	char c;
	struct chiffre *precedent;
} chiffre;

typedef struct{
	char signe; /* soit ’+’ soit ’-’ */
	size_t len; /* longueur de la liste */
	chiffre *premier; /* pointeur vers le premier élément de la liste*/
	chiffre *dernier; /*pointeur vers le dernier élément de la liste*/
} unbounded_int;

extern unbounded_int UI_NULL;

////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////

unbounded_int string2unbounded_int(const char *e); //khalifa

unbounded_int ll2unbounded_int(long long i);

char * unbounded_int2string(unbounded_int i); //khalifa

int unbounded_int_cmp_unbounded_int(unbounded_int a, unbounded_int b);

int unbounded_int_cmp_ll(unbounded_int a, long long b); //khalifa

unbounded_int unbounded_int_somme(unbounded_int a, unbounded_int b);

unbounded_int unbounded_int_difference(unbounded_int a, unbounded_int b); //khalifa

unbounded_int unbounded_int_produit(unbounded_int a, unbounded_int b);

#endif /* UNBOUNDED_INT_H_ */
