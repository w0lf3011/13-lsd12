/* check.h
 *
 * File of LSD12 Compiler Project (group 11)
 * Exercise LSD12: INFOB314/IHDCB332 : LSD12 - Group LSD12-HD-G11
 * 
 * Team :
 * 	- 	Johan BARTHELEMY	johan.barthelemy@fundp.ac.be
 * 	-	Xavier PEREMANS		xavier.peremans@student.fundp.ac.be
 *	-	Quentin FRANSSEN	quentin.franssen@student.fundp.ac.be
 */

#ifndef CHECK_H_
#define CHECK_H_

#include <stdio.h>
#include "ast.h"
#include "sym.h"
#define OK 1
#define KO 0

/*
 * Check si chaque élement de l'arbre est bien présent dans la table des symboles.
 * Pré-condition : /
 * Post-condition: renvoie 1 pour "OK" et 0 pour "KO".
 */
int check (ASTTREE tree, SYMTABLE tds);

/*
 * Check si chaque élement de l'arbre est bien présent dans la table des symboles.
 * Pré-condition : type != NULL et tds != NULL
 * Post-condition: renvoie 0 pour "KO", 2 pour "VAL_INT" ou 3 pour "VAL_BOOL".
 */
int checkType (ASTTREE tree, int type, SYMTABLE tds);

#endif 
