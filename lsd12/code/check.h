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

/**
 * 
 * Pré-condiction : tree et tds ne peuvent être null, sinon le message "KO" sera renvoyé.
 */
int check (ASTTREE tree, SYMTABLE tds);

int checkType (ASTTREE tree, int type, SYMTABLE tds);

#endif 
