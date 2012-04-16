/* pcode.c
 * test p2 ok
 */

#include <stdio.h>
#include <stdlib.h>
#include "pcode.h"


void pcodeGenAddress(ASTTREE tree, SYMTABLE s, SYMTABLE function) // function = fonction courante
{ 

  SYMTABLE node;
  int location;
  int niveau;
  
  if (tree == NULL) {
    return;
  }
  
  switch (tree->id) 
    {
    case AT_ARG :
    case AT_VAR :
      node = alreadyIsSymbol(s, tree->sval,0);
   
      // calcul l'écart d'imbrication entre la fonction et la variable   
      niveau = s->levelNode - 1;
      if(niveau <= function->levelNode) 	
	niveau = function->levelNode - niveau;
      else{
	niveau = niveau - function->levelNode;
      }
      // on peut le faire avec une valeur absolue -> a modifier
      
      //int tmp = -5 * niveau;
      int tmp = 0;
     
      if ( niveau == 0 && strcmp(function->id, "main") != 0 ) {
	tmp = 5;  // 5 + niveau * 5 ????
      }

      if(s->varType == VAL_INT) {
	//if( strcmp(function->id, "main") != 0 ) { 
	//  printf("lda i %d %d\n",niveau,node->address + 5 );
	//}
	//else 
	  printf("lda i %d %d\n",niveau,node->address + tmp);
      }
      if(s->varType == VAL_BOOL) {
	//if( strcmp(function->id, "main") != 0 ) { 
	//printf("lda b %d %d\n",niveau,node->address + 5);
	//}
	//else 
	  printf("lda b %d %d\n",niveau,node->address + tmp);
      }
      //      if(s->ref == 1) {
      // printf("ind a\n");
      // }

      break;
      
    default:
      printf(";ERROR : unrecognized type=%d in pcodeGenAddress(..)\n", tree->type);
      fprintf(stderr,";KO\n");
      exit(1);
    }

}


void pcodeGenValue(ASTTREE tree, SYMTABLE s)
{

  SYMTABLE node;
  int location, argument, lvl;
  static int staticlabel = 0;
  static int main_defined = 0;  // a supprimer?
  ASTTREE treeTmp = NULL;

  static int n_par;

  int id_while;
  int id_if;

  char type_return;

  staticlabel++;

  if (tree != NULL && s != NULL)
    {
	
      switch (tree->id) 
	{
	case AT_ROOT: 
	  
	  node = s;

	  if (tree->left != NULL) {   
	    pcodeGenValue(tree->left,s);
	  }
	  
	  printf("stp\n");	  
	  break;

	case AT_FUNCT : 

	  // trouver la fonction
	  node = alreadyIsSymbol(s, tree->sval, 1);
	  if(node != NULL) {
	      
	    //if( strcmp(s->id, "main") == 0  ) {
	    //  printf("ssp %d\n",getMaxMemoryUsage(s));
	    //  printf("ujp @main\n");		
	    //}      
	    
	    if (tree->left != NULL) {
	      pcodeGenValue(tree->left,node->down);
	    }
	    if(tree->right != NULL) {
	      pcodeGenValue(tree->right,node->down);
	    }
	      	      
	    // return des fonction void et diffente du main
	    if(node->varType == VAL_NOTYPE && strcmp(s->id, "main") != 0) {
	      printf("retp\n");
	    }

	  }
	  
	  break; 

	case AT_HEADFUNCT :  // arguments fonction, entre les ()
	  
	  printf(";at_headfunc\n");
	  if( tree->left != NULL ) {
	    pcodeGenValue(tree->left,s);
	  }
	  break;

	case AT_LISTPARAM :
	  printf(";at_listparam g\n");
	  if( tree->left != NULL ) {
	    pcodeGenValue(tree->left,s->down);
	  }
	  printf(";at_listparam d\n");
	  if( tree->right != NULL ) {
	    pcodeGenValue(tree->right,s->down);
	  }
	  break;

	case AT_CORPS :

	  // reservation memoire pour les fonctions autre que main
	  //if( strcmp(s->up->id, "main") != 0 ) {
	    printf("define @%s\n", s->up->id);

	    if( strcmp(s->up->id, "main") != 0 ) {
	      printf("ssp %d\n",getMaxMemoryUsage(s->up) + 5);
	    }
	    else {
	      printf("ssp %d\n",getMaxMemoryUsage(s->up) + 0);
	    }
	    printf("ujp @%s_body\n", s->up->id);
	    //}
	  
	  // pcode bloc decla
	  if (tree->left != NULL ){
	    pcodeGenValue(tree->left,s);
	  }
	  // pcode implementation	  
	  if (tree->right != NULL ){
	    // cas particulier: fonction main
	    //if( strcmp(s->up->id, "main") == 0 ) {
	    //  printf("define @main\n");
	    //}
	    //else {
	      printf("define @%s_body\n", s->up->id);
	      //}
	    pcodeGenValue(tree->right,s);
	  }
	  break;
      
	case AT_IMPLEMENT :

	  if(tree->left != NULL) {
	    pcodeGenValue(tree->left,s);
	  }
	  break;

	case AT_BLOCDECLA :
	  if(tree->left != NULL)
	    pcodeGenValue(tree->left,s);
	  break;
		
	case AT_DECLA : 
	  if(tree->right->id != AT_VAR ) {
	      pcodeGenValue(tree->right,s);
	  }
	  if(tree->left != NULL ) {
	    pcodeGenValue(tree->left,s);			
	  }	   
	  break;			
	
	case AT_INSTRUCTION : 	

	  if(tree->right != NULL && tree->left != NULL) {
		pcodeGenValue(tree->left,s);		
		pcodeGenValue(tree->right,s);		
	  }

	  if(tree->right == NULL && tree->left != NULL) {
		pcodeGenValue(tree->left,s);
	  }

	  break;

	case AT_AFFECT : 

	  node = alreadyIsSymbol(s, tree->left->sval, 0);

	  if(node != NULL)
	    {
	      pcodeGenAddress(tree->left, node ,s->up);
	      pcodeGenValue(tree->right, s);
	      if(node->varType == VAL_INT) // affectation d'entier
		{
		  printf("sto i\n");
		}
	      if(node->varType == VAL_BOOL) // ... ou de booleens
		{
		  printf("sto b\n");
		}
	    }
	  break;	

	case AT_EXPRD :  
	  if (tree->left != NULL){
	    pcodeGenValue(tree->left,s);
	  }
	  break;

	case AT_WRITE : 
	  pcodeGenValue(tree->right, s);
	  printf("prin\n");		
	  break;

	case AT_READ : 
	  node = alreadyIsSymbol(s, tree->right->sval, 0);  // dernier argument = 0 pour variable, 1 pour fonction  
	  pcodeGenAddress(tree->right, node ,s->up);

	  printf("read\n");
	  printf("sto i\n");
	  break;

	case AT_PLUS :
	  pcodeGenValue(tree->left, s);
	  pcodeGenValue(tree->right, s);
	  printf("add i\n");	
	  break;
			
	case AT_MOINS :
	  pcodeGenValue(tree->left, s);
	  pcodeGenValue(tree->right, s);
	  printf("sub i\n");
	  break;
		
	case AT_FOIS : 
	  pcodeGenValue(tree->left, s);
	  pcodeGenValue(tree->right, s);
	  printf("mul i\n");
	  break;
			
	case AT_NEG : 
	  pcodeGenValue(tree->right, s);
	  printf("neg i\n");
	  break;
		    
	case AT_DIVISE : 
	  pcodeGenValue(tree->left, s);
	  pcodeGenValue(tree->right, s);
	  printf("div i\n");
	  break;
			
	case AT_NOT :
	  pcodeGenValue(tree->right, s);
	  printf("not b\n");
	  break;
		
	case AT_AND : 

	  pcodeGenValue(tree->left, s);
	  pcodeGenValue(tree->right, s);
	  printf("and b\n");
	  break;
		
	case AT_OR : 
	  pcodeGenValue(tree->left, s);
	  pcodeGenValue(tree->right, s);
	  printf("or b\n");
	  break;
		
	case AT_LT : 	  
	  pcodeGenValue(tree->left, s);
	  pcodeGenValue(tree->right, s);
	  printf("les b\n");
	  break;
		
	case AT_LE :
	  pcodeGenValue(tree->left, s);
	  pcodeGenValue(tree->right, s);
	  printf("leq b\n");
	  break;
		
	case AT_EQUAL : 
	  pcodeGenValue(tree->left, s);
	  pcodeGenValue(tree->right, s);
	  printf("equ b\n");
	  break;
			
	case AT_NB :
	  printf("ldc i %d\n", tree->ival);
	  break;
		
	case AT_BOOL : 
	  printf("ldc b %d\n",tree->ival);
	  break;
		
	case AT_VAR:
	  
	  node = alreadyIsSymbol(s, tree->sval, 0);  // dernier argument = 0 pour variable, 1 pour fonction  
	  pcodeGenAddress(tree, node ,s->up);
	  
	  if(node->varType == VAL_INT) {
	    printf("ind i\n");
	  }
	  if(node->varType == VAL_BOOL) {
	    //printf(";bool var\n");
	    printf("ind b\n");
	  }
	  
	  break;
	  
	// condition bool du if
	case AT_IF :

	  if ( tree->right != NULL ) {
	    pcodeGenValue(tree->left, s);
	    pcodeGenValue(tree->right, s);
	  }
	  
	  break;

	// instruction du then
	case AT_InstructionIF :

	  id_if = staticlabel;

	  printf("fjp @fi_%d\n", id_if);
	  pcodeGenValue(tree->left, s);
	  printf("ujp @fi_%d\n", id_if);
	  printf("define @fi_%d\n", id_if);

	  break;

	// instruction du if then else
	case AT_InstructionIFELSE :
	  
	  id_if = staticlabel;

	  printf("fjp @else_%d\n", id_if);
	  if( tree->left != NULL ) {
	    pcodeGenValue(tree->left, s);	    
	  }
	  printf("ujp @fi_%d\n", id_if);
	  printf("define @else_%d\n", id_if);
	  if( tree->right != NULL ) {
	    pcodeGenValue(tree->right, s);
	  }
	  printf("define @fi_%d\n", id_if);

	  break;

	// boucle while
	case AT_WHILE :
	  id_while = staticlabel;
	  printf("define @while_%d\n", id_while);
	  pcodeGenValue(tree->left, s);
	  
	  printf("fjp @od_%d\n", id_while);
	  
	  if( tree->right != NULL ) {
	    pcodeGenValue(tree->right, s);
	  }
	  
	  printf("ujp @while_%d\n", id_while);
	  printf("define @od_%d\n", id_while);
	  
	  break;
	
	case AT_RETURN :
	  // determiner type de retour: entier ou booleen
	  printf("; type ret = %d\n", s->up->varType);
	  if( s->up->varType == 2 ) { //VAL_INT ????
	    type_return = 'i';
	  }
	  else {
	    type_return = 'b';
	  }
	  
	  // generation pcode retour
	  printf("lda %c 0 0\n", type_return);
	  pcodeGenValue(tree->right, s);
	  printf("sto %c\n", type_return);
	  printf("retf\n");
	  break;


	case AT_FUNCTPARAM :
	  if( tree->right != NULL && tree->left == NULL ) {
	    pcodeGenValue(tree->right,s);
	    n_par++;
	  }
	  if( tree->left != NULL ) {
	    pcodeGenValue(tree->right,s);
	    pcodeGenValue(tree->left,s);
	    n_par++;
	  }
	  break;

	case AT_ARG :
	  pcodeGenAddress(tree, node ,s->up);
	  break;

	case AT_APPELF :
	  
	  n_par = 0;

	  printf(";calcul diff de profondeur d\n");
	  int niveau = s->levelNode - 1;
	  
	  printf("mst %d\n", niveau);  // pour le moment pas de fonctions imbriquees -> 0

	  printf(";calcul nombre para n_par\n");
	  if(tree->right != NULL) {
	    pcodeGenValue(tree->right, s->down);
	  }

	  printf(";appel de %s\n", tree->sval);  
	  printf("cup %d @%s\n", n_par, tree->sval);  // pour p2: pas de parametres -> 0 
	  break;

	case AT_FORWARD :
	  break;

	default:
	  printf(";ERROR : unrecognized type=%d in pcodeGenValue(..)\n", tree->type);
	  fprintf(stderr,";KO\n");
	  
  	}

    }


}
