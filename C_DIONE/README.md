# Projet Langage C

Le projet a été réalisé par Hector BROUSSALIS et Khalifa Ababacar DIONE, dans le groupe de projet 23

# Comment exécuter

`make all` crée les deux fichiers `test_unbounded` et `calc_unbounded_int`

Pour les exécuter, faire `./test_unbounded` ou `./calc_unbounded_int <-i source.txt> <-o dest.txt>`

On peut créer les deux fichiers indépendamment avec `make test` et `make calc`

La commande `make clean` supprime les deux fichiers

Le dossier Library contient les fichiers `unbounded_int.h` et `unbounded_int.c`

Le fichier `test_unbounded` (Partie 1) affiche les résultats de toutes les fonctions qui ont été testées

Le fichier `calc_unbounded_int` (Partie 2) fonctionne comme demandé

# Fonctionnalités

Toutes les fonctions demandées pour `test_unbounded` ont été implémentées à part le quotient

Toutes les fonctions demandées pour `calc_unbounded_int` ont été implémentées, notamment :
- les lignes n'ont pas de limite de longueur
- les variables n'ont pas de limite de longueur et on peut en déclarer autant qu'on veut