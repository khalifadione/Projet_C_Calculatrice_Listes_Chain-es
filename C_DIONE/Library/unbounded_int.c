#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "unbounded_int.h"

unbounded_int UI_NULL = {.signe = '*', .len = 0, .premier = NULL, .dernier = NULL};

////////////////////////////////////////
////   FONCTIONS DE VERIFICATION    ////
////////////////////////////////////////

static bool is_neg(unbounded_int ui){ //check si l'ui est négatif
	if(ui.signe == '-') return true;
	else return false;
}

////////////////////////////////////////
////   FONCTIONS DE CREATION-AJOUT  ////
////////////////////////////////////////

static chiffre * new_chiffre(int i){ //crée chiffre
	if(i < 0 || i >= 10) return NULL;
	chiffre * pchi = malloc(sizeof(chiffre));
	if(pchi == NULL) return NULL;
	else {
		chiffre chi = {NULL, i + '0', NULL};
		*pchi = chi;
		return pchi;
	}
}

static unbounded_int * new_ui_null(){
	unbounded_int * pui = malloc(sizeof(unbounded_int));
	if(pui == NULL) return NULL;
	else {
		pui->signe = '*';
		pui->len = 0;
		pui->premier = NULL;
		pui->dernier = NULL;
	}
	return pui;
}

static unbounded_int * new_ui_signe(int i){ //crée ui avec 1 signe
	unbounded_int * pui = new_ui_null();
	if(pui == NULL) return NULL;
	else {
		pui->signe = i < 0 ? '-' : '+' ;
		return pui;
	}
}

static bool add(unbounded_int * pui, int i){ // ajoute à la fin
	chiffre * pchi = new_chiffre(i);
	if(pchi == NULL) return false;
	if(pui->len == 0){
		if(pui->signe == '*') pui->signe = i < 0 ? '-' : '+';
		pui->premier = pchi;
		pui->dernier = pchi;
		pui->len = 1;
	} else {
		pchi->precedent = pui->dernier;
		pui->dernier->suivant = pchi;
		pui->dernier = pui->dernier->suivant;
		pui->len++;
	}
	return true;
}

static bool add_first(unbounded_int * pui, int i){ // ajoute au début
	chiffre * pchi = new_chiffre(i);
	if(pchi == NULL) return false;
	if(pui->len == 0){
		if(pui->signe == '*') pui->signe = i < 0 ? '-' : '+';
		pui->premier = pchi;
		pui->dernier = pchi;
		pui->len = 1;
	} else {
		pchi->suivant = pui->premier;
		pui->premier->precedent = pchi;
		pui->premier = pui->premier->precedent;
		pui->len++;
	}
	return true;
}

static void pop(unbounded_int * pui){
	if(pui->premier == NULL) return;
	if(pui->len == 1) {
		free(pui->premier);
		pui->signe = '*';
		pui->premier = NULL;
		pui->dernier = NULL;
		pui->len = 0;
	} else {
		pui->premier = pui->premier->suivant;
		free(pui->premier->precedent);
		pui->premier->precedent = NULL;
		pui->len--;
	}
}

static int get_fin(unbounded_int * pui, int i){
	chiffre * pchi = pui->dernier;
	for(int h=0; h<i; h++){
		if(pchi == NULL) return -1;
		pchi = pchi->precedent;
	}
	return pchi->c - '0';
}

static void set_fin(unbounded_int * pui, int i, int j){
	chiffre * pchi = pui->dernier;
		for(int h=0; h<i; h++){
			if(pchi == NULL) return;
			pchi = pchi->precedent;
		}
		pchi->c = j + '0';
}

static unbounded_int oppose(unbounded_int ui){ //change le signe
	unbounded_int ui_copy = {ui.signe, ui.len, ui.premier, ui.dernier};
	if(ui.signe == '-') ui_copy.signe = '+';
	if(ui.signe == '+') ui_copy.signe = '-';
	return ui_copy;
}

////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////

unbounded_int string2unbounded_int(const char *e){ //khalifa
	unbounded_int * pui = new_ui_null();
	if(*e == '\0') return UI_NULL;
	if(!isdigit(*e)){
		if(*e == '+') pui->signe = '+';
		if(*e == '-') pui->signe = '-';
		e++;
	} else pui->signe = '+';
	while(*e != '\0'){
		if(!isdigit(*e)) return UI_NULL;
		else {
			if(add(pui, *e-'0') == false) return UI_NULL;
		}
		e++;
	}
	return *pui;
}

unbounded_int ll2unbounded_int(long long i){
	unbounded_int * pui = new_ui_null();
	if(i < 0){
		pui->signe = '-';
		i = -i;
	} else pui->signe = '+';
	if(pui == NULL) return UI_NULL;
	while(i > 0){
		int reste = i % 10;
		if(add_first(pui, reste) == false) return UI_NULL;
		i = i/10;
	}
	return *pui;
}

char * unbounded_int2string(unbounded_int i) { //khalifa
	if(i.len == 0) return "UI_NULL";
	int l = i.signe == '-' ? i.len + 2 : i.len + 1;
	char * s = malloc(l * sizeof(char));
	int h = 0;
	chiffre * pchi = i.premier;
	if(i.signe == '-') { s[0] = '-'; h = 1; }
	while(pchi != NULL){
		s[h] = pchi->c;
		h++;
		pchi = pchi->suivant;
	}
	s[h] = '\0';
	return s;
}

int unbounded_int_cmp_unbounded_int(unbounded_int a, unbounded_int b){
	if(a.signe != b.signe) return is_neg(a) ? -1 : 1;
	if(is_neg(a) && is_neg(b)) return -unbounded_int_cmp_unbounded_int(oppose(a), oppose(b));
	if(a.len != b.len) return a.len < b.len ? -1 : 1;
	chiffre * a_pchi = a.premier;
	chiffre * b_pchi = b.premier;
	while(a_pchi != NULL){
		if(a_pchi->c < b_pchi->c) return -1;
		if(a_pchi->c > b_pchi->c) return 1;
		a_pchi = a_pchi->suivant;
		b_pchi = b_pchi->suivant;
	}
	return 0;
}

int unbounded_int_cmp_ll(unbounded_int a, long long b){//khalifa
	if(a.signe == '+' && b < 0) return 1;
	if(a.signe == '-' && b >= 0) return -1;
	if(a.signe == '-' && b < 0) return -unbounded_int_cmp_ll(oppose(a), b);
	chiffre * a_pchi = a.dernier;
	int b_chi = b % 10;
	int cmp;
	while(true){
		if(a_pchi->c-'0' > b_chi) cmp = 1;
		if(a_pchi->c-'0' < b_chi) cmp = -1;
		if(a_pchi->c-'0' == b_chi) cmp = 0;

		a_pchi = a_pchi->precedent;

		b = b/10;
		b_chi = b % 10;

		if(a_pchi == NULL && b_chi == 0) return cmp;
		if(a_pchi == NULL) return -1;
		if(b_chi == 0) return 1;
	}
}

unbounded_int unbounded_int_somme(unbounded_int a, unbounded_int b){
	if(is_neg(a) && is_neg(b)) return oppose(unbounded_int_somme(oppose(a), oppose(b))); //-2 -1 -> - (2+1)
	if(is_neg(a)){
		if(est_plus_grand(b, oppose(a)) == 1) return unbounded_int_somme(b, a); // -1 +2 -> +2 -1
		else return oppose(unbounded_int_somme(oppose(a), oppose(b))); // -2 +1 -> -(2-1)
	}
	if(is_neg(b) && est_plus_grand(oppose(b), a) == 1) return oppose(unbounded_int_somme(oppose(b), oppose(a))); // +1 -2 -> - (2-1)
	if(est_plus_grand(b,a) == 1) return unbounded_int_somme(b,a); // 1+2 -> 2+1

	if(is_neg(b)){ //soustraction
		unbounded_int * pui = new_ui_signe(+1);
		if(pui == NULL) return UI_NULL;

		chiffre * a_pchi = a.dernier;
		chiffre * b_pchi = b.dernier;

		int retenue = 0;
		while(a_pchi != NULL){
			int a_c = a_pchi == NULL ? 0 : a_pchi->c - '0';
			int b_c = b_pchi == NULL ? 0 : b_pchi->c - '0';
			add_first(pui, (10 + a_c - b_c - retenue ) % 10);
			if(a_c < b_c) retenue = 1;
			else retenue = 0;
			a_pchi = a_pchi->precedent;
			if(b_pchi != NULL) b_pchi = b_pchi->precedent;
		}

		while(pui->premier->c == '0') pop(pui);

		return *pui;

	} else { //addition
		unbounded_int * pui = new_ui_signe(+1);
		if(pui == NULL) return UI_NULL;

		chiffre * a_pchi = a.dernier;
		chiffre * b_pchi = b.dernier;

		int retenue = 0;
		while(a_pchi != NULL || retenue != 0){
			int a_c = a_pchi == NULL ? 0 : a_pchi->c - '0';
			int b_c = b_pchi == NULL ? 0 : b_pchi->c - '0';
			add_first(pui, (a_c + b_c) % 10 + retenue);
			if(a_c + b_c >= 10) retenue = 1;
			else retenue = 0;
			if(a_pchi != NULL) a_pchi = a_pchi->precedent;
			if(b_pchi != NULL) b_pchi = b_pchi->precedent;
		}
		return *pui;
	}
}

unbounded_int unbounded_int_difference(unbounded_int a, unbounded_int b){ //khalifa
	return unbounded_int_somme(a, oppose(b));
}

unbounded_int unbounded_int_produit(unbounded_int a, unbounded_int b){
	if(a.signe != b.signe) return oppose(unbounded_int_produit(oppose(a), b));
	if(a.len < b.len) return unbounded_int_produit(b, a);

	unbounded_int * pui = new_ui_signe(+1);
	for(int i=0; i<a.len+b.len+1;i++) {
		if(!add(pui, 0)) { pui = NULL; break; }
	}
	if(pui == NULL) return UI_NULL;

	for(int i=0; i<a.len; i++){
		int retenue = 0;
		if(get_fin(&a, i) == 0) continue;
		for(int j=0; j<b.len; j++){
			int v = get_fin(pui, i+j) + get_fin(&a, i)*get_fin(&b, j) + retenue;
			set_fin(pui, i+j, v%10);
			retenue = v/10;
		}
		set_fin(pui, i+b.len, retenue);
	}

	if(pui->premier->c == '0') pop(pui);

	return *pui;
}
