#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "unbounded_int.h"

////////////////////////////////////////
///////   FONCTIONS D'AFFICHAGE   //////
////////////////////////////////////////

static void print_ui(unbounded_int ui){ //affiche la valeur de l'ui (unbounded int)
	char * s = ui_to_string(ui);
	printf("%s\n",s);
}

static void n(){
	printf("\n");
}

int main(int argc, char * argv[]){

	unbounded_int ui;
	unbounded_int ui_;
	unbounded_int ui__;

	ui = string2unbounded_int("-987654"); //new_ui_string()
	print_ui(ui);
	ui = string2unbounded_int("456789");
	print_ui(ui);
	ui = string2unbounded_int("785gdfdhf");
	print_ui(ui);

	n();

	ui = ll2unbounded_int(-123456); //new_ui_ll()
	print_ui(ui);

	n();

	char * s = unbounded_int2string(ui); //ui_to_string()
	puts(s);

	n(); n();

	ui_ = new_ui_ll(123);
	ui__ = new_ui_ll(98765);


	int i = unbounded_int_cmp_unbounded_int(ui_,ui__); //est_plus_grand()
	printf("%i",i);

	n(); n();

	int j = unbounded_int_cmp_ll(ui_, 23);
	printf("%i",j);

	n(); n();

	ui = unbounded_int_somme(ui_, ui__);
	print_ui(ui);

	n();

	ui = unbounded_int_difference(ui_, ui__);
	print_ui(ui);

	n();

	ui = unbounded_int_produit(ui_, ui__);
	print_ui(ui);

	n();

	return 0;
}
