/* lsd12.l
 *
 * "{"{blank}* [A-Za-z]([A-Za-z]|[0-9])* {blank}*"}" {return COMMENT;} 
 *
 */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "y.tab.h"

int num_lines=1;
%}

%option noyywrap

var       [A-Za-z]([A-Za-z]|[0-9])*
nbr       (0|[1-9][0-9]*)
boolean   ("true"|"false")
blank     [ \t]+
type	  ("int"|"bool"|"iest"|"void")
%%

"print"      {return PRINT;}
"read"       {return READ;}
"write"     {return WRITE;}
"add"     	{return ADD;}
"to"     	{return TO;}
"function"     	{return FUNCTION;}
"var" 		{return REF;}
"remove" 	{return REMOVE;}
"from" 		{return FROM;}
"progamme" 	{return PROG;}
"forward" {return FORWARD;}

"+"          {return PLUS;}
"-"          {return MINUS;}
"*"          {return TIMES;}
"("          {return LP;}
")"          {return RP;}
","          {return COMMA;}
"mod"        {return MODULO;}
"!"			  {return NOT;}
"="			  {return EQUAL;}
":"			  {return TWOPOINT;}
":="			  {return AFFECT;}
"<"			  {return LT;}
">"			  {return GT;}
"<="			  {return LE;}
">="			  {return GE;}
"&&"			  {return AND;}
"||"			  {return OR;}

"#" {return CARDINAL;}

"if" {return IF;}
"fi" {return FI;}
"then" {return THEN;}
"else" {return ELSE;}
"while" {return WHILE;}
"do" {return DO;}
"od" {return OD;}
"return" {return RETURN;}
"begin" {return BEGIN;}
"end" {return END;}

";" {return FIN;}

"{" {return COMMENTBEGIN;}
"}" {return COMMENTEND;}


{type} {
		if(strcmp(yytext, "void")==0) 
			{yylval.ival=1;}
		else
		{
			if(strcmp(yytext, "int")==0) {yylval.ival=2;}
			else
			{
				if(strcmp(yytext, "bool")==0)
					{yylval.ival=3;}
				else
					{yylval.ival=4;}				
			}
		}
		return TYPE;
	}

{boolean} {
		if(strcmp(yytext, "true")==0) 
			{yylval.ival=1;}
		else 
			{yylval.ival=0;}
		return BOOLEAN;
	}

{var}        {
                yylval.sval=(char*)calloc(strlen(yytext)+1,sizeof(char));
		strcpy(yylval.sval,yytext);
		return VAR;
             }

			 
{nbr}        {
                yylval.ival=atoi(yytext);
		return NB;
             }

"\n"         {++num_lines;}

{blank}      {/*On passe*/}

.            {
                fprintf(stderr,"KO\n");
                printf("ERROR : invalid '%s' in line %d\n",yytext, num_lines);
                exit(0);
             }

%%
