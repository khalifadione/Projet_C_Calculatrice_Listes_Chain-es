#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "unbounded_int.h"


typedef struct variable {
	char * nom;
	unbounded_int valeur;
	struct variable * next;
} variable;

typedef struct var_tab {
	variable * head;
} var_tab;

int len;
bool is_eof;
var_tab V = {.head = NULL}; //VARIABLE GLOBALE VAR_TAB

/////////////////////////////////////////////
/////////  FONCTIONS UTILITAIRES  ///////////
/////////////////////////////////////////////

void p_f(char * s){
	puts(s);
	fflush(stdout);
}

/////////////////////////////////////////////
/////////  FONCTIONS SUR VAR_TAB  ///////////
/////////////////////////////////////////////

void add_v(char * nom, unbounded_int valeur){
	variable * pvar = malloc(sizeof(variable));
	pvar->nom = nom;
	pvar->valeur = valeur;
	pvar->next = NULL;
	variable * ptmp = V.head;
	if(ptmp == NULL){
		V.head = pvar;
		return;
	}

	while(strcmp(ptmp->nom, nom) != 0){
		if(ptmp->next == NULL) {
			ptmp->next = pvar;
			return;
		}
		ptmp= ptmp->next;
	}
	ptmp->valeur = valeur;

}

variable * get_v(char * nom){
	variable * pvar = V.head;
	while(pvar != NULL){
		if(strcmp(pvar->nom, nom) == 0) return pvar;
		pvar = pvar->next;
	}
	return NULL;
}

void print_v(variable * pvar, FILE * dest){
	char * s = malloc(strlen(pvar->nom) + pvar->valeur.len + 10);
	s[0] = '\0';
	strcat(s, pvar->nom);
	strcat(s, " = ");
	strcat(s, ui_to_string(pvar->valeur));
	strcat(s, "\n");
	fputs(s, dest);
}



/////////////////////////////////////////////
///////////  FONCTIONS SUR ---  /////////////
/////////////////////////////////////////////

char * getMot(char * s){
	char * mot = malloc(len+1);
	int i_m = 0; int i_s = 0;

	while(isspace(s[i_s])) i_s++;

	if(s[i_s] == '='){
		len = len-i_s-1;
		memmove(s, s+i_s+1, len+1);
		return "=";
	}

	while(s[i_s] != '\0' && s[i_s] != '=' && !isspace(s[i_s])){
		mot[i_m++] = s[i_s++];
	}

	mot[i_m] = '\0';
	len = len-i_s;
	memmove(s, s+i_s, len+1);

	return mot;
}

char * getLigne(FILE * source){
	char * ligne = malloc(1);
	int i = 0; int size = 1;

	while(true){
		char c = getc(source);
		if(i == size){
			size = 2*size;
			ligne = realloc(ligne, size);
		}

		if(c == '\n' || c == EOF){
			is_eof = c == EOF ? true : false; //global
			len = i; //global
			ligne[i] = '\0';
			return ligne;
		}

		ligne[i++] = c;
	}
}

unbounded_int operation(char * val_1, char op, char * val_2){
	unbounded_int ui, ui_;
	if(isalpha(val_1[0])) {
		variable * var_1 = get_v(val_1);
		ui = var_1->valeur;
	} else ui = new_ui_string(val_1);

	if(isalpha(val_2[0])) {
		variable * var_2 = get_v(val_2);
		ui_ = var_2->valeur;
	} else ui_ = new_ui_string(val_2);


	if(op == '\0') return ui;
	if(op == '+') return unbounded_int_somme(ui, ui_);
	if(op == '-') return unbounded_int_difference(ui, ui_);
	if(op == '*') return unbounded_int_produit(ui, ui_);
	return UI_NULL;
}

void traduction(FILE * source, FILE * dest){

	while(is_eof == false){
		char * ligne = getLigne(source);
		char * mot_1 = getMot(ligne);

		if(mot_1[0] == '\0') continue;

		if(strcmp(mot_1, "print") == 0){ //print
			char * s = getMot(ligne);
			variable * pvar = get_v(s);
			print_v(pvar, dest);
		} else { //affectation/déclaration
			if(strcmp(getMot(ligne),"=") == 0){
				char * val_1 = getMot(ligne);
				char op = getMot(ligne)[0];
				char * val_2 = getMot(ligne);

				add_v(mot_1, operation(val_1, op, val_2));
			}
		}
	}
}



int main(int argc, char * argv[]){

//	setvbuf(stdout, NULL, _IONBF, 0);

	FILE * source = stdin;
	FILE * dest = stdout;

	for(int i=0; i<argc-1; i++){
		if(strcmp(argv[i],"-i") == 0) source = fopen(argv[++i], "r");
		if(strcmp(argv[i],"-o") == 0) dest = fopen(argv[++i], "w");
	}

	traduction(source, dest);

	fclose(source);
	fclose(dest);

	return 0;
}


