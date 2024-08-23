.PHONY: test calc

all: test calc

test: Partie_1/src/test_unbounded.c Library/unbounded_int.c
	gcc -o test_unbounded -Wall -g -pedantic Partie_1/src/test_unbounded.c Library/unbounded_int.c -I Library
	
calc: Partie_2/src/calc_unbounded_int.c Library/unbounded_int.c
	gcc -o calc_unbounded_int -Wall -g -pedantic Partie_2/src/calc_unbounded_int.c Library/unbounded_int.c -I Library
		
clean: 
	rm -f test_unbounded calc_unbounded_int