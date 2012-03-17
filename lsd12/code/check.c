/* check.c
 *
 */

#include "check.h"
	
int check(ASTTREE tree, SYMTABLE tds)
{
	SYMTABLE node; 
	int type;
    	if (tds == NULL) { return KO; }
	if (tree == NULL)
		return KO;
	else{
		switch (tree->id)
		{
			case AT_ROOT : 
				if(tree->left != NULL) {
					return (check(tree->left, tds));
				}		
				break;

			
			case AT_FUNCT : 
				
				node = alreadyIsSymbol(tds, tree->sval, 1);
				
				if(node != NULL)
				{
					if(tree->left != NULL) {
						printf(";---GPS = tree_id : %d AT_FUNCT LEFT ;---\n", tree->id);
						return (check(tree->left, tds));
					}
					if(tree->right != NULL) {
						printf(";---GPS = tree_id : %d AT_FUNCT RIGHT ;---\n", tree->id);
						return (check(tree->right, tds));
					}
				}else {
					printf(";ERROR : la fonction main est inexistante \n");
					return KO;
				}
				break; 
			case AT_CORPS : 
				
				if(tree->right != NULL) {
					printf(";---GPS = tree_id : %d AT_CORPS RIGHT ;---\n", tree->id);
					return (check(tree->right, tds));
				}
				if(tree->left != NULL) {
					printf(";---GPS = tree_id : %d AT_CORPS LEFT ;---\n", tree->id);
					return (check(tree->left, tds));
				}
				break;
			case AT_IMPLEMENT : 
				
				if(tree->left != NULL) {
					printf(";---GPS = tree_id : %d AT_IMPLEMENT LEFT ;---\n", tree->id);
					return (check(tree->left, tds));
				}
				break;
			case AT_BLOCDECLA :
				if(tree->right != NULL) {
					return KO;
				}
				if(tree->left != NULL)	{
					printf(";---GPS = tree_id : %d AT_BLOCDECLA LEFT ;---\n", tree->id);
					return (check(tree->left, tds));
				}
				break;
			
			case AT_DECLA : 
				if(tree->right != NULL) {
					printf(";---GPS = tree_id : %d AT_DECLA RIGHT ;---\n", tree->id);
					return (check(tree->right, tds));
				}
				if(tree->left != NULL) {
					printf(";---GPS = tree_id : %d AT_DECLA LEFT ;---\n", tree->id);
					return (check(tree->left, tds));
				}
				break;			

			case AT_INSTRUCTION : 
				if(tree->right != NULL) {
					printf(";---GPS = tree_id : %d AT_INSTRUCTION RIGHT ;---\n", tree->id);
					return (check(tree->right, tds));
				}
				if(tree->left != NULL) {
					printf(";---GPS = tree_id : %d AT_INSTRUCTION LEFT ;---\n", tree->id);
					return (check(tree->left, tds));
				}
				break;
			case AT_AFFECT : 
				if(tree->right != NULL) {
					printf(";---GPS = tree_id : %d AT_AFFECT RIGHT ;---\n", tree->id);
					//return (check(tree->right, tds));
					type = tds->down->varType;
					printf(";---GPS = varType : %d ;---\n", type);
					return checkType(tree->right, type, tds);
					
				}
				if(tree->left != NULL) {
					printf(";---GPS = tree_id : %d AT_AFFECT LEFT ;---\n", tree->id);
					//return (check(tree->left, tds));
					type = tds->varType;
					return checkType(tree->left, type, tds);
				}
				break;
			case AT_EXPRD :  
				if(tree->right != NULL) {
					type = tds->varType;
					return checkType(tree->right, type, tds);
				}
				if(tree->left != NULL) {
					type = tds->varType;
					return checkType(tree->right, type, tds);
				}
				break;

			case AT_WRITE : 
				if(tree->right != NULL) {
					return (check(tree->right, tds));
				}
				break;
	
			case AT_RETURN : 
				if(tree->right != NULL) {
					return (check(tree->right, tds));
				}						
				break;	

			default :
				printf("; Erreur de typage check\n");
				fprintf(stderr,";KO\n");
				return KO;
		}
	}
}



int checkType(ASTTREE tree, int type, SYMTABLE tds)
{ 
	SYMTABLE node,function;
	if (tree == NULL)
		return 0;
	else{
		switch (tree->id)
		{

			
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
			
			
					
			
			case AT_PLUS :
						
						if(type != VAL_INT)
						{
							printf(";Error de typage avec PLUS\n");
							return KO;
						}
							
						else{
							return (checkType(tree->left, VAL_INT,tds) && checkType(tree->right,VAL_INT,tds));
						}
						break;

			
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


			
			case AT_NEG : 
						if(type != VAL_INT)
						{
							printf(";Erreur de typage avec NEG\n");
							return KO;
						}else{
								return checkType(tree->right,VAL_INT,tds);
						}
						break;

		    
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

			
			case AT_NOT : 
						
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

		
			case AT_LT : 
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

			
			case AT_LE :
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

		
			case AT_EQUAL : 
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

			
			case AT_NB : 
						printf(";---GPS = tree_id : %d AT_AFFECT LEFT ;---\n", tree->id);
						if (type == VAL_INT)
							return OK;
						else{
							printf(";ERREUR DE TYPAGE ! \n");
							return KO;
						}
						break;

		
			case AT_BOOL : 
						if (type == VAL_BOOL)
							return VAL_BOOL;
						else{
							printf(";ERREUR DE TYPAGE ! \n");
							return KO;
						}
						break;

			
			default : printf(";Erreur de typage check type\n");
						fprintf(stderr,";KO\n");
						return KO;
		}
	}
}
