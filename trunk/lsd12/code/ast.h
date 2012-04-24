/* ast.h
 *
 * File of LSD12 Compiler Project (group 11)
 * Exercise LSD12: INFOB314/IHDCB332 : LSD12 - Group LSD12-HD-G11
 * 
 * Team :
 * 	- 	Johan BARTHELEMY	johan.barthelemy@fundp.ac.be
 * 	-	Xavier PEREMANS		xavier.peremans@student.fundp.ac.be
 *	-	Quentin FRANSSEN	quentin.franssen@student.fundp.ac.be
 */

#ifndef AST_H
#define AST_H

// Valeur des types de Noeuds.
#define AT_VAR     0
#define AT_BLOCDECLA 1
#define AT_DECLA 2
#define AT_FUNCT 3
#define AT_HEADFUNCT 4
#define AT_CORPS 5
#define AT_IMPLEMENT 6
#define AT_FORWARD 7
#define AT_INSTRUCTION 8
#define AT_NB 9
#define AT_BOOL 10
#define AT_PLUS 11
#define AT_ROOT 12
#define AT_EXPRD 13
#define AT_NOT 14
#define AT_EQUAL 15 
#define AT_GE 16
#define AT_GT 17
#define AT_LE 18
#define AT_LT 19
#define AT_OR 20
#define AT_AND 21
#define AT_NEG 22
#define AT_MODULO 23
#define AT_DIVISE 24
#define AT_FOIS 25
#define AT_MOINS 26
#define AT_AFFECT 27
#define AT_READ 28
#define AT_WRITE 29
#define AT_RETURN 30
#define AT_InstructionIF 31
#define AT_InstructionIFELSE 32
#define AT_IF 33
#define AT_WHILE 34
#define AT_ARG 35
#define AT_LISTPARAM 36
#define AT_APPELF 37
#define AT_FUNCTPARAM 38

// Valeur des types.
#define VAL_VOID 1
#define VAL_INT 2
#define VAL_BOOL 3
#define VAL_ENS 4
#define VAL_NOTYPE 5

// Structure de notre arbre.
struct astnode {
  int id;		// identification d'un noeud;
  int type;		// identifie le type de noeud;

  int ival;		// valeur entiere (constante);
  char* sval;	// nom de l'identificateur (variable ou fonction);

  int varRef;	// indique is variable passee par ref (1) ou pas (0);
  int fnctId;	// numero de surcharge d'une fonction (l5);
 
  struct astnode * left;	// pointe vers le fils de gauche;
  struct astnode * right;	// pointe vers le fils de droite;
};

typedef struct astnode * ASTTREE;
typedef struct astnode   ASTNODE; // detail

/*
 * Créer un noeud de type ASTTREE.
 * Pré-condition : /
 * Post-condition: Créer un nouveau noeud dans l'arbre et retourne le nouvel arbre.
 */
extern ASTTREE createNode(int id, int type, int varRef, int fnctId, int ival, char* sval, ASTTREE left, ASTTREE right);

/*
 * Supprime le noeud et libère la mémoire.
 * Pré-condition : node != null
 * Post-condition: libère la mémoire alloué par la variable "node".
 */
extern void freeNode(ASTTREE node);

/*
 * Supprime l'arbre et libère la mémoire.
 * Pré-condition : tree != null
 * Post-condition: libère la mémoire alloué par la variable "tree".
 */
extern void freeTree(ASTTREE tree);

/*
 * Affiche l'arbre en partant de la racine
 * Pré-condition : tree != null
 * Post-condition: Convertit les identifiants des noeuds en un nom représentables.
 */
extern void printTree(ASTTREE tree);

#endif
