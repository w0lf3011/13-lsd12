/* ast.h
 *
 * part of the DEMO compiler
 *
 * H. Toussaint (hto@info.fundp.ac.be), 14/06/05
 */

#ifndef AST_H
#define AST_H

// do not change values below, or also edit humanReadableNodeType() in ast.c
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

//
#define VAL_VOID 1
#define VAL_INT 2
#define VAL_BOOL 3
#define VAL_ENS 4
#define VAL_NOTYPE 5


struct astnode {
  int id;
  int type;

  int ival;
  char* sval;

  struct astnode * left;
  struct astnode * right;
};

typedef struct astnode * ASTTREE;
typedef struct astnode   ASTNODE;

extern ASTTREE createNode(int id, int type, int ival, char* sval, ASTTREE left, ASTTREE right);
extern void freeNode(ASTTREE node);
extern void freeTree(ASTTREE tree);

extern void printTree(ASTTREE tree);

#endif
