/* pcode.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "pcode.h"


void pcodeGenAddress(ASTTREE tree, SYMTABLE s, SYMTABLE function) // function = fonction courante
{ 

  SYMTABLE node;
  int location, niveau;
  
  if (tree == NULL)
    return;
  
  switch (tree->id) 
    {
    case AT_VAR: 
      node = alreadyIsSymbol(s, tree->sval,0);
      
      niveau = s->levelNode - 1;
      
      // calcul l'écart d'imbrication entre la fonction et la variable
      if(niveau <= function->levelNode) 	
	niveau = function->levelNode - niveau;
      else{
	niveau = niveau - function->levelNode;
      }
      
      if(s->varType == VAL_INT)
	printf("lda i %d %d\n",niveau,node->address);
      if(s->varType == VAL_BOOL)
	printf("lda b %d %d\n",niveau,node->address);
      if(s->ref == 1)
	{
	  printf("ind a\n");
	}
      break;
      
    default:
      fprintf(stderr,";KO\n");
      printf(";ERROR : unrecognized type=%d in pcodeGenAddress(..)\n", tree->type);
      exit(1);
    }

}


void pcodeGenValue(ASTTREE tree, SYMTABLE s)
{
  SYMTABLE node;
  int location, argument, lvl;
  static int staticlabel = 0;
  int i = staticlabel; // numero du label
  ASTTREE treeTmp = NULL;

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
	  if(node != NULL)
	    {
	    	if (tree->left != NULL) {
			pcodeGenValue(tree->left,node->down);
		}
		if(tree->right != NULL) {
			pcodeGenValue(tree->right,node->down); //tds
		}
		
	      if(node->varType == VAL_NOTYPE) // sortir de la fonction nill
		printf("retf\n");
	    }
	  
	  break; 

	case AT_HEADFUNCT :  // arguments fonction, entre les ()
	  if( tree->left != NULL )
	    {
	      pcodeGenValue(tree->left,s);
	    }
	  break;
	case AT_CORPS : 
		if (tree->left != NULL ){	  
			pcodeGenValue(tree->left,s);
		}
		 
		  printf("define @%s\n",s->up->id);
		  printf("ssp %d\n",getMaxMemoryUsage(s->up));
	
		if (tree->right != NULL ){
		  pcodeGenValue(tree->right,s);
		}
		  break;
	case AT_IMPLEMENT :
	  if(tree->left != NULL)
	    {
	      pcodeGenValue(tree->left,s);
	    }
	  break;
	case AT_BLOCDECLA :
	  if(tree->left != NULL)
	    pcodeGenValue(tree->left,s);
	  
	  break;
		
	case AT_DECLA : 

	  if(tree->right->id != AT_VAR )
	    {
	      pcodeGenValue(tree->right,s);
	    }
	    if(tree->left != NULL )
	    {
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
	  pcodeGenValue(tree->right, s);
	  printf("read\n");			
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
	  
	if(node->varType == VAL_INT)
	    printf("ind i\n");
	  if(node->varType == VAL_BOOL)
	    printf("ind b\n");							

	  break;
	  

	default:
	  fprintf(stderr,";KO\n");
	  printf(";ERROR : unrecognized type=%d in pcodeGenValue(..)\n", tree->type);
  	}
    }



}
