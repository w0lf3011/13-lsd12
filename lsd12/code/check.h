/* check.h
 *
 */

#ifndef CHECK_H_
#define CHECK_H_

#include <stdio.h>
#include "arbre.h"
#include "sym.h"
#define OK 1
#define KO 0

// Declaration fonctions
int check (ASTTREE tree, SYMTABLE tds);
/*
	objets utilises : tree = arbre genere par le compilateur, tds = table generee par le compilateur
	PRE : /
	POST : Renvoi 1 (OK) si toutes les expressions sont bien typées, 0 (KO) sinon
*/

int checkType (ASTTREE tree, int type, SYMTABLE tds);
/*
	objets utilises : tree = arbre genere par le compilateur, type = le type qu'on veut verifier, tds = table generee par 				  le compilateur
	PRE : L'arbre ne doit pas être cyclique 
	POST : Renvoi le type de l'expression (1 = Int, 2 = Bool, 3 = Matrix), renvoi 0 sinon
*/

#endif /*CHECK_H_*/
