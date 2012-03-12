/* sym.h
 *
 */

#ifndef SYM_H_
#define SYM_H_

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"


struct SYMBOLETABLE {

	char * id; // Nom variable
	int address; // Position de la variable en mémoire
	int varType; // Type de variable : entier, boolean, matrix
	int levelNode; // Niveau d'imbrication
	int state; // Etat : D = {variable,function,argument} : 0 variable, 1 function, 2 argument, 3 D\{function}
	int ref; // arg par copie ou pas
	
	struct SYMBOLETABLE* next; // Pointeur vers le prochain symbole
	struct SYMBOLETABLE* previous; // Pointeur vers le symbole précedent
	struct SYMBOLETABLE* up; // Pointeur vers le symbole parent
	struct SYMBOLETABLE* down; // Pointeur vers le symbole enfant
};

// Definition des structures
typedef struct SYMBOLETABLE NOEUD;
typedef NOEUD * SYMTABLE;


// Declaration des fonctions
SYMTABLE creaNode();
/*
	PRE : /
	POST : Crée un symbole dans la table des symboles.
*/

void printSymbolTableGraphViz(SYMTABLE s);

SYMTABLE checkSymbolLevel(SYMTABLE s, char* name, int state);
/*
	objets utilises : s = element de l'environnement analyse, name = nom de la variable a rechercher,state = etat de 				  l'element (variable (0), fonction (1) ou argument (2))
	PRE : name != NULL
	POST : renvoie NULL si le symbole n'existe pas dans l'environnement courant, sinon
		renvoie l'adresse du symbole.
*/

SYMTABLE alreadyIsSymbolLevel(SYMTABLE s, char* name,int state);
/*
	objets utilises : s = element de l'environnement analyse, name = nom de la variable a rechercher,state = etat de 				  l'element (variable (0), fonction (1) ou argument (2))
	PRE : /
	POST : se positionne à la fin de l'environnement courant et retourne le résultat de checkSymbolLevel.
*/

SYMTABLE alreadyIsSymbol(SYMTABLE s, char* name, int state);
/*	
	objets utilises : s = element de l'environnement courant, name = nom de la variable a rechercher,state = etat de 				  l'element (variable (0), fonction (1) ou argument (2))
	PRE : /
	POST : Renvoi l'adresse du symbole recherché sur l'environnement courant ou l'un de
		ses environnements appelants.
*/

SYMTABLE addToSymbolTable(SYMTABLE s, char* name, int state, int type);
/*
	objets utilises : s = element de l'environnement courant, name = nom de la variable a rechercher,state = etat de 				  l'element (variable (0), fonction (1) ou argument (2)), type = type de l'element
	PRE : s != NULL, state compris entre 0 et 2, type compris entre 0 et 4.
	POST : Mets à jour le dernier symbole et initialise un nouveau symbole sur le pointeur "next".
	       Si state vaut 1, il initialise le pointeur "down"
*/

void freeSymbolTable(SYMTABLE s);
/*
	objet utilise : s = table generee par le compilateur
	PRE : /
	POST : Libère l'espace alloué dans la mémoire pour la table des symboles.
*/

void computeLocations(SYMTABLE s);
/* 
	objet utilise : s = table generee par le compilateur
	PRE : /
	POST : Initialise l'adresse de chaque symbole dans la table des symboles. 
*/

int getMaxMemoryUsage(SYMTABLE s);
/*
	objet utilise : s = element de l'environnement courant 
	PRE : s doit correspondre à un symbole représentant une fonction
	POST : Retourne le nombre de symboles existants dans l'environnement local de la fonction s
*/

void printSymbolTable(SYMTABLE s);
/*
	objet utilise : s = table generee par le compilateur
	PRE : / 
	POST : Affiche le contenu de la table des symboles.
*/

int fillTable (ASTTREE tree, SYMTABLE s, int currentType);
/*
	objet utilise : tree = l'arbre genere par le compilateur, s = table en cours de construction, currentType = le type 				de la declaration
	PRE : s != NULL, currentType = -1 ou compris entre 1 et 3.
	POST : Remplit la table des symboles en fonction de l'arbre.
*/




#endif
