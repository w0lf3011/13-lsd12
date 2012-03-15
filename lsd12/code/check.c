/* check.c
 *
 */

#include "check.h"
	
int check(ASTTREE tree, SYMTABLE tds)
{
	SYMTABLE node,nodeR; 
	int type;
    	
	if (tree == NULL)
		return KO;
	else{
		switch (tree->id)
		{
			// AT_ROOT : NULL Main NULL
			case AT_ROOT : 
						node = alreadyIsSymbol(tds, tree->sval,1);
											
						if(node != NULL)
						{
							return check (tree->right,tds);
							return check (tree->left,tds);
						}else{
							printf(";ERROR : la fonction main est inexistante \n");
							return KO;
						}
					
						break;

			// AT_CORPS : BlocDecla Code NULL
			case AT_CORPS : 
						return (check(tree->left,tds) && check(tree->right,tds));
						break;

			// AT_BLOCDECL : Decla NULL NULL
			case AT_BLOCDECL :
						// bloc decla vide
						if(tree->left == NULL)
							return OK;
						else
							return check(tree->left,tds);
						break;

			// AT_DECLA : (Declaration|function) NULL DECLA
			case AT_DECLA : 
						if(tree->right != NULL)
							return check(tree->right,tds);
						else
							return OK;
						break;

			// AT_CODE : InstructList NULL NULL
			case AT_CODE : 
						// si code non vide
						if(tree->right != NULL)
							return check(tree->right,tds);
						else
							return OK;
						break;

			// InstructList : Instruction NULL InstructList
			case AT_INSTRUCTION : 
						// si instruction vide
						if(tree->left == NULL)
							return OK;
						else{						
							if(tree->right == NULL)	// si dernière instruction
							{
								if(check(tree->left,tds)!=0)
								{
									return OK;
								}else{
									return KO;
								}
							}else{
								if(check(tree->left,tds)!=0 && check(tree->right,tds)!=0)
								{
									return OK;
								}else{
									return KO;
								}	
							}
						}
						break;

			case AT_EXPRD :  
					// récupérer le type de l'expression de droite
					type = tree->left->type;
					if(type != VAL_NOTYPE)
					{
						if(checkType(tree->left,type,tds)==type)
							return type; 
						else{
							printf(";Error de type pour EXPRD\n");
							return KO;
						}
					}else{
						// ExprD est une fonction
						node = alreadyIsSymbol(tds,tree->left->sval,1);
						if(node != NULL)
							return checkType(tree->left,node->varType,tds);
						else{
							printf(";Error la function %s n'est pas declaree\n",tree->left->sval);
							return KO;
						}
					}
					break;
					
			
			
			// AT_WRITE : ExprD
			case AT_PRINT : 
						// Verifie si le type du noeud left est VAL_INT
						if(checkType(tree->left, VAL_INT, tds)==1)
						{
							return OK;
						}else{
							printf(";Erreur de typage avec OUT\n");
							return KO;
						}
						break;

			// AT_RETURN : ExprD
			case AT_RETURN : 
						// Verifier que ExprD est du même type que la fonction
						type = tds->up->varType;
						return checkType(tree->left,type,tds); 
						break;

			
			// check par default : retourne KO
			default : printf("; Erreur de typage check\n");
						fprintf(stderr,";KO\n");
						return KO;
		}
	}
}



int checkType(TREE tree, int type, SYMTABLE tds)
{ 
	SYMTABLE node,function;
	if (tree == NULL)
		return 0;
	else{
		switch (tree->id)
		{

			// Check AT_VAR : NULL NULL NULL
			case AT_VAR : 
						node = alreadyIsSymbol(tds,tree->sval,3);
						if(node != NULL) // si variable existe
						{
							if(node->varType == type)
							{
								return type;
							}else{
								printf(";ATTENTION ERREUR TYPE ! \n");
								return KO;
							}
						}else{
							printf(";Variable %s n'existe pas\n",tree->sval);
							return KO;
						}
						break;
			
			
					
			// AT_PLUS : NULL ExprD ExprD 
			case AT_PLUS :
						// Si mauvais type retourne KO
						if(type != VAL_INT)
						{
							printf(";Error de typage avec PLUS\n");
							return KO;
						}
							// Verifie si le type du noeud middle et noeud right sont bien VAL_INT
						else{
							return (checkType(tree->left, VAL_INT,tds) && checkType(tree->right,VAL_INT,tds));
						}
						break;

			// AT_MINUSS : NULL ExprD ExprD
			case AT_MOINS :
						if(type != VAL_INT)
						{
							printf(";Error de type avec MOINS\n");
							return KO;
						}
						else{
								return (checkType(tree->left, VAL_INT,tds) && checkType(tree->right,VAL_INT,tds));
						}
						break;


			// AT_FOIS : NULL ExprD ExprD
			case AT_FOIS : 
						if(type != VAL_INT)
						{
							printf(";Error de typage avec FOIS\n");
							return KO;
						}
						else{
								return (checkType(tree->left, VAL_INT,tds) && checkType(tree->right,VAL_INT,tds));
						}
						break;


			// AT_NEG : NULL NULL ExprD
			case AT_NEG : 
						if(type != VAL_INT)
						{
							printf(";Erreur de typage avec NEG\n");
							return KO;
						}else{
								return checkType(tree->right,VAL_INT,tds);
						}
						break;

		    	// AT_DIVISE : NULL ExprD ExprD
			case AT_DIVISE : 
						if(type != VAL_INT)
						{
							printf(";Error de typage avec DIVISE\n");
							return KO;
						}
						else{
								return (checkType(tree->left, VAL_INT,tds) && checkType(tree->right,VAL_INT,tds));
						}
						break;

			
			case AT_NOT : //printf(";Check AT_NOT \n");
						
						if(type != VAL_BOOL)
						{
							printf(";Error de typage avec NOT\n");
							return KO;
						}
						else{
								if(checkType(tree->left, VAL_BOOL,tds)==2)
									return VAL_BOOL;
								else
									return KO;
						}
						break;

			// AT_AND : ExprD ExprD NULL
			case AT_AND : 
						if(type != VAL_BOOL)
						{
							printf(";Error de typage avec AND\n");
							return KO;
						}
						else{
								if(checkType(tree->left,VAL_BOOL,tds)==2 && checkType(tree->right,VAL_BOOL,tds)==2)
									return VAL_BOOL;
								else
									return KO;
						}
						break;

			// AT_OR : ExprD ExprD NULL
			case AT_OR : 
						if(type != VAL_BOOL)
						{
							printf(";Error de typage avec OR\n");
							return KO;
						}
						else{
								if(checkType(tree->left,VAL_BOOL,tds)==2 && checkType(tree->right,VAL_BOOL,tds)==2)
									return VAL_BOOL;
								else
									return KO;
						}
						break;

			// AT_PPETIT : ExprD ExprD NULL
			case AT_PPETIT : 
						if(type != VAL_BOOL)
						{
							printf(";Erreur de typage pour opération '<'\n");
							return KO;
						}else{
								if(checkType(tree->left, VAL_INT, tds)==1 && checkType(tree->right,VAL_INT, tds)==1)
								{ 
									return VAL_BOOL;
								}else{
									return KO;
								}
						}
						break;

			// AT_EGPETIT : ExprD ExprD NULL
			case AT_EGPETIT :
						if(type != VAL_BOOL)
						{
							printf(";Erreur de typage pour opération '<='\n");
							return KO;
						}else{
								if(checkType(tree->left, VAL_INT, tds)==1 && checkType(tree->right,VAL_INT, tds)==1)
								{ 
									return VAL_BOOL;
								}else{
									return KO;
								}
						}
						break;

			// AT_EGAL : ExprD ExprD NULL
			case AT_EGAL : 
						if(type != VAL_BOOL)
						{
							printf(";Erreur de typage pour opération '='\n");
							return KO;
						}else{
								if(checkType(tree->left, VAL_INT, tds)==1 && checkType(tree->right,VAL_INT, tds)==1)
								{ 
									return VAL_BOOL;
								}else{
									return KO;
								}
						}
						break;

			// AT_NB : NULL NULL NULL
			case AT_NB : 
						if (type == VAL_INT)
							return OK;
						else{
							printf(";ERREUR DE TYPAGE ! \n");
							return KO;
						}
						break;

			// AT_BOOL : NULL NULL NULL
			case AT_BOOL : 
						if (type == VAL_BOOL)
							return VAL_BOOL;
						else{
							printf(";ERREUR DE TYPAGE ! \n");
							return KO;
						}
						break;

			//default
			default : printf(";Erreur de typage check type\n");
						fprintf(stderr,";KO\n");
						return KO;
		}
	}
}
