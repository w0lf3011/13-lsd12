/* check.c
 *
 */

#include "check.h"
	
int check(ASTTREE tree, SYMTABLE tds)
{
	SYMTABLE node; 
	int type;
    	if (tds == NULL) { 
		printf("; Tree Empty");
		return KO; }
	if (tree == NULL) {
		printf("; Tree Empty");
		return KO; }
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
						return (check(tree->left, node->down)); //tds
					}
					if(tree->right != NULL) {
						printf(";---GPS = tree_id : %d AT_FUNCT RIGHT ;---\n", tree->id);
						return (check(tree->right, node->down)); //tds
					}
				}else {
					printf(";ERROR : la fonction main est inexistante \n");
					return KO;
				}
				break; 
			case AT_CORPS : 
				if(tree->left != NULL) {
					printf(";---GPS = tree_id : %d AT_CORPS LEFT ;---\n", tree->id);
					return (check(tree->left, tds));
				}
				if(tree->right != NULL) {
					printf(";---GPS = tree_id : %d AT_CORPS RIGHT ;---\n", tree->id);
					return (check(tree->right, tds));
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
					printf(";---GPS = tree_id : %d AT_BLOCDECLA RIGHT ;---\n", tree->id);
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
					type = tree->type;
					return checkType(tree->right, type, tds);
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
					type = tree->right->type;
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
						printf(";---GPS = tree_id : %d AT_VAR ;---\n", tree->id);
						node = alreadyIsSymbol(tds, tree->sval, 3); 
						if(node != NULL) // si variable existe
						{
							if(node->varType == type)
							{
								printf("OK %d \n", type);
								return type;
							}else{
								printf(";ATTENTION ERREUR TYPE ! %d - %d \n", node->varType, type);
								return KO;
							}
						}else{
							printf(";Variable %s n'existe pas\n",tree->sval);
							return KO;
						}
						break;
			
			
					
			
			case AT_PLUS :
						printf(";---GPS = tree_id : %d AT_PLUS ;---\n", tree->id);
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
						printf(";---GPS = tree_id : %d AT_MOINS ;---\n", tree->id);
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
						printf(";---GPS = tree_id : %d AT_FOIS ;---\n", tree->id);
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
						printf(";---GPS = tree_id : %d AT_NEG ;---\n", tree->id);
						if(type != VAL_INT)
						{
							printf(";Erreur de typage avec NEG\n");
							return KO;
						}else{
								return checkType(tree->right,VAL_INT,tds);
						}
						break;

		    
			case AT_DIVISE : 
						printf(";---GPS = tree_id : %d AT_DIVISE ;---\n", tree->id);
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
						printf(";---GPS = tree_id : %d AT_NOT ;---\n", tree->id);
						if(type != VAL_BOOL)
						{
							printf(";Error de typage avec NOT\n");
							return KO;
						}
						else{
								if(checkType(tree->left, VAL_BOOL,tds)==3)
									return VAL_BOOL;
								else {
									printf(";Error : VAL_BOOL OK but -> AT_NOT\n");
									return KO; }
						}
						break;

		
			case AT_AND : 
						printf(";---GPS = tree_id : %d AT_AND ;---\n", tree->id);
						if(type != VAL_BOOL)
						{
							printf(";Error de typage avec AND\n");
							return KO;
						}
						else{
								if(checkType(tree->left,VAL_BOOL,tds)==3 && checkType(tree->right,VAL_BOOL,tds)==3)
									return VAL_BOOL;
								else {
									printf(";Error : VAL_BOOL OK but -> AT_AND\n");
									return KO; }
						}
						break;

		
			case AT_OR : 
						printf(";---GPS = tree_id : %d AT_OR ;---\n", tree->id);
						if(type != VAL_BOOL)
						{
							printf(";Error de typage avec OR\n");
							return KO;
						}
						else{
								if(checkType(tree->left,VAL_BOOL,tds)==3 && checkType(tree->right,VAL_BOOL,tds)==3)
									return VAL_BOOL;
								else {
									printf(";Error : VAL_BOOL OK but -> AT_OR\n");
									return KO; } 
						}
						break;

		
			case AT_LT : 
						printf(";---GPS = tree_id : %d AT_LT ;---\n", tree->id);
						if(type != VAL_BOOL)
						{
							printf(";Erreur de typage pour opération '<'\n");
							return KO;
						}else{
								if(checkType(tree->left, VAL_INT, tds)==2 && checkType(tree->right,VAL_INT, tds)==2)
								{ 
									return VAL_BOOL;
								}else{
									printf(";Error : VAL_BOOL OK but -> AT_LT\n");
									return KO;
								}
						}
						break;

			
			case AT_LE :
						printf(";---GPS = tree_id : %d AT_LE ;---\n", tree->id);
						if(type != VAL_BOOL)
						{
							printf(";Erreur de typage pour opération '<='\n");
							return KO;
						}else{
								if(checkType(tree->left, VAL_INT, tds)==2 && checkType(tree->right,VAL_INT, tds)==2)
								{ 
									return VAL_BOOL;
								}else{
									printf(";Error : VAL_BOOL OK but -> AT_LE\n");
									return KO;
								}
						}
						break;

		
			case AT_EQUAL : 
						printf(";---GPS = tree_id : %d AT_EQUAL ;---\n", tree->id);
						if(type != VAL_BOOL)
						{
							printf(";Erreur de typage pour opération '='\n");
							return KO;
						}else{
								if(checkType(tree->left, VAL_INT, tds)==2 && checkType(tree->right,VAL_INT, tds)==2)
								{ 
									return VAL_BOOL;
								}else{
									printf(";Error : VAL_BOOL OK but -> AT_EQUAL\n");
									return KO;
								}
						}
						break;

			
			case AT_NB : 
						printf(";---GPS = tree_id : %d AT_NB ;---\n", tree->id);
						if (type == VAL_INT)
							return OK;
						else{
							printf(";ERREUR DE TYPAGE ! \n");
							return KO;
						}
						break;

		
			case AT_BOOL : 
						printf(";---GPS = tree_id : %d AT_BOOL ;---\n", tree->id);
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
