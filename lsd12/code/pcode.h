/* pcode.h
 *
 */

#ifndef PCODE_H_
#define PCODE_H_

#include "ast.h"
#include "sym.h"

// Declaration fonctions

void pcodeGenAddress(TREE tree, SYMTABLE s, SYMTABLE function);
/*
	objets utilises : tree = arbre genere par le compilateur, s = variable recherchee, function = la fonction courante
	PRE : s ne doit pas être NULL et function ne doit pas être NULL.
	POST : Génère le p-code qui récupère l'adresse de la variable.
*/

void pcodeGenValue(TREE tree, SYMTABLE s);
/*
	objets utilises : tree = arbre genere par le compilateur, s = element de l'environnement courant
	PRE : /
	POST : Génère le p-code associé au noeud en train d'être analysé
*/

void calculatePositionMatrix(TREE tree,SYMTABLE node,SYMTABLE s,int lvl);
/*
	objets utilises : tree = arbre genere par le compilateur, node = matrice courante, s = element de l'environnement 				  courant, lvl = difference d'imbrication entre la matrice et l'environnement courant
	PRE : tree,node et s ne doivent pas être NULL.
	POST : Calcule la position réelle d'une valeur dans la matrice.
*/

void checkOverflow(TREE tree,SYMTABLE node, SYMTABLE s, int lvl);
/*
	objets utilises : tree = arbre genere par le compilateur, node = matrice courante, s = element de l'environnement 				  courant, lvl = difference d'imbrication entre la matrice et l'environnement courant
	PRE : tree,node et s doivent pas être NULL.
	POST : verifie si les parametres de colonne et ligne entres ne depassent pas les indices de la matrice.
*/

#endif /*PCODE_H_*/
