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
	int varType; // Type de variable : entier, boolean
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


void printSymbolTableGraphViz(SYMTABLE s);

SYMTABLE checkSymbolLevel(SYMTABLE s, char* name, int state);


SYMTABLE alreadyIsSymbolLevel(SYMTABLE s, char* name,int state);


SYMTABLE alreadyIsSymbol(SYMTABLE s, char* name, int state);


SYMTABLE addToSymbolTable(SYMTABLE s, char* name, int state, int type);

void freeSymbolTable(SYMTABLE s);


void computeLocations(SYMTABLE s);


int getMaxMemoryUsage(SYMTABLE s);


void printSymbolTable(SYMTABLE s);

int fillTable (ASTTREE tree, SYMTABLE s, int currentType);


#endif
