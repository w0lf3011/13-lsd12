/* pcode.h
 *
 * File of LSD12 Compiler Project (group 11)
 * Exercise LSD12: INFOB314/IHDCB332 : LSD12 - Group LSD12-HD-G11
 * 
 * Team :
 * 	- 	Johan BARTHELEMY	johan.barthelemy@fundp.ac.be
 * 	-	Xavier PEREMANS		xavier.peremans@student.fundp.ac.be
 *	-	Quentin FRANSSEN	quentin.franssen@student.fundp.ac.be
 */

#ifndef PCODE_H_
#define PCODE_H_

#include "ast.h"
#include "sym.h"

// Declaration fonctions

/*
 * Objets utilises : tree = arbre genere par le compilateur, s = variable recherchee, function = la fonction courante
 * Pré-condition : s ne doit pas être NULL et function ne doit pas être NULL.
 * Post-condition: Génère le p-code qui récupère l'adresse de la variable.
 */
void pcodeGenAddress(ASTTREE tree, SYMTABLE s, SYMTABLE function);

/*
 * Objets utilises : tree = arbre genere par le compilateur, s = element de l'environnement courant
 * Pré-condition : /
 * Post-condition: Génère le p-code associé au noeud en train d'être analysé
 */
void pcodeGenValue(ASTTREE tree, SYMTABLE s);

#endif /*PCODE_H_*/