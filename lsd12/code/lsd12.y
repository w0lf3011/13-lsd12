/* lsd12.y
 *
 */

%{
#include <stdio.h>
#include <stdlib.h>

#include "arbre.h"
#include "sym.h"
#include "pcode.h"

extern int num_lines;
extern char* yytext;

  
// to avoid 'implicit definition'
int yylex(void);
int yyerror(char *str);

ASTTREE root;
%}


// définition du type des variables $x
%union{
        int ival;
        char *sval;
        ASTTREE tval;
}

%token PRINT READ WRITE 

%token MODULO PLUS MINUS TIMES ADD AND NOT LT GT EQUAL OR

%token TO FUNCTION REF REMOVE FROM PROG FORWARD 

%token LP RP COMMA AFFECT CARDINAL TWOPOINT

%token IF FI THEN ELSE WHILE DO OD RETURN BEGIN END FIN COMMENTBEGIN COMMENTEND 

%token TYPE BOOLEAN VAR NB

%left MODULO 
%left PLUS MINUS TIMES ADD
%left AND NOT OR
%left LT GT EQUAL

%type <tval> Lsd12 PROG Declaration BlocDecla Decla listVar InstructionList Instruction ExprD Var appelArg

%%

Lsd12: PROG VAR FIN FUNCTION VAR LP RP TWOPOINT TYPE FIN InstructList END
	{ root = createNodeTree(AT_ROOT, -1, $3, VAL_NOTYPE, 0, NULL, $5, NULL); }
;

BlocDecla: REF Decla 
	{ $$ = createNodeTree(AT_BLOCDECL, -1, NULL, VAL_NOTYPE, 0, $2, NULL, NULL); }
;

Decla: {$$ = NULL;}
	| Declaration Decla
	{ $$ = createNodeTree(AT_DECLA, -1, NULL, VAL_NOTYPE, 0, $1, NULL, $2); }
;

Declaration: TYPE listVar FIN
	{ $$ = createNodeTree(AT_DECLARATION, -1, NULL, $1, 0, $2, NULL, NULL); }
;

listVar: VAR
	{ $$ = createNodeTree(AT_VAR, 1, $1, VAL_NOTYPE, 0, NULL, NULL,NULL);}
	| VAR listVar
	{ $$ = createNodeTree(AT_VAR, 1, $1, VAL_NOTYPE, 0, NULL, NULL,$2);}
;

Instruction: ExprD
	{ $$ = createNodeTree(AT_EXPRD, -1, NULL, VAL_NOTYPE, 0, $1, NULL, NULL);}
	|IF LP ExprD RP THEN InstructList FI
	{ $$ = createNodeTree(AT_IF, -1, NULL, VAL_NOTYPE, 0, $3, $6, NULL);}
	| IF LP ExprD RP THEN InstructList ELSE InstructList FI
	{ $$ = createNodeTree(AT_IFELSE, -1, NULL, VAL_NOTYPE, 0, $3, $6, $8);}
	| WHILE LP ExprD RP DO InstructList OD
	{ $$ = createNodeTree(AT_WHILE, -1, NULL, VAL_NOTYPE, 0, $3, $6, NULL);}
	| Var AFFECTG ExprD
	{ $$ = createNodeTree(AT_AFFECTG, -1, NULL, VAL_NOTYPE, 0, $1, $3, NULL);}
	| ExprD AFFECTD Var
	{ $$ = createNodeTree(AT_AFFECTD, -1, NULL, VAL_NOTYPE, 0, $3, $1, NULL);}
	| ExprD AFFECTD PRINT
	{ $$ = createNodeTree(AT_PRINT, -1, NULL, VAL_NOTYPE, 0, $1, NULL, NULL);}
	
;

InstructList: { $$ = NULL;}
	| FIN
	{ $$ = createNodeTree(AT_INSTRUCTION, -1, NULL, VAL_NOTYPE, 0, NULL, NULL, NULL);}
	| Instruction FIN InstructList
	{ $$ = createNodeTree(AT_INSTRUCTION, -1, NULL, VAL_NOTYPE, 0, $1, NULL, $3);}
;

ExprD: Var
	{$$ = $1;}
	| VAR LP appelArg RP
	{$$ = createNodeTree(AT_APPELF, -1, $1, VAL_NOTYPE,0, $3, NULL, NULL);}
	| NB
	{$$ = createNodeTree(AT_NB, $1, NULL, VAL_INT,0, NULL, NULL, NULL);}
	| ExprD PLUS ExprD
	{$$ = createNodeTree(AT_PLUS,-1, NULL, VAL_INT,0, $1, NULL, $3);}
	| ExprD MINUS ExprD
	{$$ = createNodeTree(AT_MOINS, -1, NULL, VAL_INT,0, $1, NULL, $3);}
	| MINUS ExprD
	{$$ = createNodeTree(AT_NEG,-1,NULL,VAL_INT,0, NULL, NULL, $2);}
	| ExprD TIMES ExprD
	{$$ = createNodeTree(AT_FOIS, -1, NULL, VAL_INT,0, $1, NULL, $3);}
	| ExprD DIVISE ExprD
	{$$ = createNodeTree(AT_DIVISE, -1, NULL, VAL_INT,0, $1, NULL, $3);}
	| ExprD MODULO ExprD
	{$$ = createNodeTree(AT_MODULO, -1, NULL, VAL_INT,0, $1, NULL, $3);}
	| BOOLEAN
	{$$ = createNodeTree(AT_BOOL, $1, NULL, VAL_BOOL,0, NULL, NULL, NULL);}
	| ExprD AND ExprD
	{$$ = createNodeTree(AT_AND, -1, NULL, VAL_BOOL,0, $1, NULL, $3);}
	| ExprD OR ExprD
	{$$ = createNodeTree(AT_OR, -1, NULL, VAL_BOOL,0, $1, NULL, $3);}
	| NOT ExprD
	{$$ = createNodeTree(AT_NOT, -1, NULL, VAL_BOOL, 0, $2, NULL, NULL);}
	| ExprD PPETIT ExprD
	{$$ = createNodeTree(AT_PPETIT, -1, NULL, VAL_BOOL,0, $1, NULL, $3);}
	| ExprD EGPETIT ExprD
	{$$ = createNodeTree(AT_EGPETIT, -1, NULL, VAL_BOOL,0, $1, NULL, $3);}
	| ExprD EGAL ExprD
	{$$ = createNodeTree(AT_EGAL, -1, NULL, VAL_BOOL,0, $1, NULL, $3);}
	| LP ExprD RP
	{$$ = $2;}
	| IN
	{$$ = createNodeTree(AT_IN, -1, NULL, VAL_INT,0, NULL, NULL, NULL);}
	| GET LP VAR COMMA ExprD COMMA ExprD RP
	{$$ = createNodeTree(AT_GET, -1, $3, VAL_INT,0, $5, $7, NULL);}
;

appelArg: { $$ = NULL;}
	|ExprD
	{ $$ = createNodeTree(AT_APPELARG, -1, NULL, VAL_INT,0, $1, NULL, NULL);}
	| ExprD COMMA appelArg
	{ $$ = createNodeTree(AT_APPELARG, -1, NULL, VAL_INT,0, $1, NULL, $3);}
;

Var: VAR { $$ = createNodeTree(AT_VAR, -1, $1, VAL_NOTYPE, 1, NULL, NULL, NULL);}
;

%%

int yyerror(char *str)
{
        fprintf(stderr,"KO\n");
        printf("ERROR '%s' AT LINE  %d : UNRECOGNISED '%s'\n",
                str,num_lines,yytext);
        exit(0);
}
int main()
{ 
 
}
