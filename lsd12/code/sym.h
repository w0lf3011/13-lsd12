/* sym.h
 *
 * File of LSD12 Compiler Project (group 11)
 * Exercise LSD12: INFOB314/IHDCB332 : LSD12 - Group LSD12-HD-G11
 * 
 * Team :
 * 	- 	Johan BARTHELEMY	johan.barthelemy@fundp.ac.be
 * 	-	Xavier PEREMANS		xavier.peremans@student.fundp.ac.be
 *	-	Quentin FRANSSEN	quentin.franssen@student.fundp.ac.be
 */

#ifndef SYM_H_
#define SYM_H_

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

// Structure de notre table des symboles.
struct SYMBOLETABLE {

  char* id;     // Nom variable
  int address;  // Position de la variable en mémoire
  int varType;  // Type de variable : entier, boolean
  int levelNode;// Niveau d'imbrication
  int state;    // Etat :  0 variable, 1 function, 2 argument, 3 (tout sauf fonction)
  int ref;      // arg par copie (0) ou par reference (1)
  int fnctId;   // suffixe du nom de la fonction -> 0 par defaut et 1 si au moins une fonction créée
  int fnctFor; 	// Boolean si fonction est une fonction forward (1) ou pas (0)
  
  int UId;
	
  struct SYMBOLETABLE* next;     // Pointeur vers le prochain symbole
  struct SYMBOLETABLE* previous; // Pointeur vers le symbole précedent
  struct SYMBOLETABLE* up;       // Pointeur vers le symbole parent
  struct SYMBOLETABLE* down;     // Pointeur vers le symbole enfant

};

// Definition des structures
typedef struct SYMBOLETABLE NOEUD;
typedef NOEUD * SYMTABLE;

// int schFnct;	 utilisé pour rechercher une fonction en fonction de sa surcharge. 0 -> pas rechercher, 1 -> chercher

// Declaration et prototypes des fonctions
/*
 * Créer une table des symboles vide.
 * Pré-condition : /
 * Post-condition: Créer un symbole dans la table des symboles.
 */
SYMTABLE creaNode();

/*
 * Affiche la table des symboles suivant un certain format pour être utiliser par GraphViz.
 * GraphiViz : logiciel permettant de générer une image à partir d'un code,
 * utiliser ici pour générer la représentation de la table des symboles.
 */
void printSymbolTableGraphViz(SYMTABLE s);

/*
 * Contrôle si un symbole contenant un nom (name), un état (state), un suffixe du nom de la fonction (fnctId),
 * si il s'agit d'une surcharge (schFnct), et si il s'agit d'une fonction forward (fnctFor).
 * Et renvoie l'adresse du symbole si il existe.
 * Pré-condition : name != NULL, state != NULL et compris entre 0 et 3, fnctId != NULL, schFnct != NULL et fnctFor != NULL et 0 ou 1.
 * Post-condition:
 *		renvoie NULL si le symbole n'existe pas dans la table des symboles,
 *		renvoie l'adresse du symbole si le symbole existe dans la table des symboles.
 */
SYMTABLE checkSymbolLevel(SYMTABLE s, char* name, int state, int fnctId, int schFnct, int fnctFor);

/*
 * Renvoie l'adresse du symbole recherché dans la table des symboles.
 * Pré-condition : name != NULL, state != NULL et compris entre 0 et 3, fnctId != NULL, schFnct != NULL et fnctFor != NULL et 0 ou 1.
 * Post-condition: renvoie l'adresse recherché dans la table des symboles.
 */
SYMTABLE alreadyIsSymbolLevel(SYMTABLE s, char* name,int state, int fnctId, int schFnct, int fnctFor);

/*
 * Renvoie l'adresse du symbole recherché dans la table des symboles.
 * Pré-condition : name != NULL, state != NULL et compris entre 0 et 3, fnctId != NULL, schFnct != NULL et fnctFor != NULL et 0 ou 1.
 * Post-condition: renvoie l'adresse recherché dans la table des symboles.
 */
SYMTABLE alreadyIsSymbol(SYMTABLE s, char* name, int state, int fnctId, int schFnct, int fnctFor);

/*
 * Ajout un nouveau symbole à la l'arbre de la table des symboles.
 * Pré-condition : name != name != NULL, state != NULL et compris entre 0 et 3, type != NULL et est un entier ou un booleen, fnctId != NULL, schFnct != NULL et fnctFor != NULL et 0 ou 1.
 * Post-condition: renvoie l'arbre de la table des symboles.
 */
SYMTABLE addToSymbolTable(SYMTABLE s, char* name, int state, int type, int fnctId, int schFnct, int fnctFor);

/*
 * Contrôle le nombre de fois que l'on trouve un symbole déterminé par le "name", le "state", le "fnctId", le "schFnct" et le "fnctFor".
 * Pré-condition : name != name != NULL, state != NULL et compris entre 0 et 3, type != NULL et est un entier ou un booleen, fnctId != NULL, schFnct != NULL et fnctFor != NULL et 0 ou 1.
 * Post-condition: Renvoie le nombre de fois que le symbole est trouvé dans la table des symboles.
 */
int checkNbFunctSymbol(SYMTABLE s, char* name, int state, int fnctId, int schFnct, int fnctFor);

/*
 * Libère la table de symbole "s".
 * Pré-condition : /
 * Post-condition: Libère l'espace alloué dans la mémoire pour la tables des symboles.
 */
void freeSymbolTable(SYMTABLE s);

/*
 * Initialise l'adresse de chaque symbole dans la table des symboles.
 * Pré-condition : s != NULL
 * Post-condition: Initialise l'adresse de chaque symbole de la table des symboles.
 */
void computeLocations(SYMTABLE s);

/*
 * Renvoie le nombre de symboles existant dans la table des symboles.
 * Pré-condition : s != NULL
 * Post-condition: renvoie le nombre de symboles existant dans l'arbre "s".
 */
int getMaxMemoryUsage(SYMTABLE s);

/*
 * Affiche le contenu de la table des symboles.
 * Pré-condition : /
 * Post-condition: Affiche le contenu de la table des symboles.
 */
void printSymbolTable(SYMTABLE s);

/*
 * Remplit la table des symboles en fonction de l'arbre.
 * Pré-condition : currentType != NULL
 * Post-condition: remplit la table des symboles en fonction de l'arbre.
 */
int fillTable (ASTTREE tree, SYMTABLE s, int currentType);

#endif
