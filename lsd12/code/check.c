/* check.c
 *
 */

#include "check.h"
	
int check(ASTTREE tree, SYMTABLE tds)
{
	SYMTABLE node; 
	int type;
    	if (tds == NULL) { 
		printf("; Tds Empty \n");
		return KO; }
	if (tree == NULL) {
		printf("; Tree Empty \n");
		return KO; }
	else{
		//printf("%d\n", tree->id);
		switch (tree->id)
		{
			case AT_ROOT : 
				
				if(tree->left != NULL) {
					printf(";---GPS = tree_id : %d AT_ROOT LEFT ;---\n", tree->id);
					return (check(tree->left, tds));
				}		
				break;

			
			case AT_FUNCT : 
					node = alreadyIsSymbol(tds, tree->sval, 1, tree->fnctId, 1, 0);
					
					if(node != NULL)
					{
						if(tree->left != NULL) {
							printf(";---GPS = tree_id : %d AT_FUNCT LEFT  ;---\n", tree->id);
							return check(tree->left, node->down); //tds
						}
						if(tree->right != NULL) {
							printf(";---GPS = tree_id : %d AT_FUNCT RIGHT  ;---\n", tree->id);
							return check(tree->right, node->down); //tds
						}
						
					}else {
						printf(";ERROR : la fonction %s est inexistante \n", tree->sval);
						return KO;
					}
				
				break; 
			case AT_HEADFUNCT : printf(";---GPS = tree_id : %d AT_HEADFUNCT LEFT;---\n", tree->id);
				if(tree->left != NULL) {
					
					return check(tree->left,tds);
				}
				else {
					return OK;
				}
				break;
			case AT_FORWARD : printf(";---GPS = tree_id : %d AT_FORWARD ;---\n", tree->id);
					return OK;
				break;
			case AT_CORPS : 
				if(tree->left != NULL && tree->right != NULL) {
					printf(";---GPS = tree_id : %d AT_CORPS LEFT ;---\n", tree->id);
					return check(tree->left, tds) && check(tree->right, tds);
				}
				break;
			case AT_IMPLEMENT : 
				if(tree->left != NULL) {
					printf(";---GPS = tree_id : %d AT_IMPLEMENT LEFT ;---\n", tree->id);
					return check(tree->left, tds);
				}
				if(tree->right == NULL && tree->left == NULL) {
					printf(";---GPS = tree_id : %d AT_IMPLEMENT NULL NULL ;---\n", tree->id);
					return OK;
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
				if(tree->right == NULL && tree->left == NULL) {
					printf(";---GPS = tree_id : %d AT_BLOCDECLA NULL NULL ;---\n", tree->id);
					return OK;
				}
				break;
			
			case AT_DECLA : 
				printf(";---GPS = tree_id : %d AT_DECLA RIGHT->LEFT ;---\n", tree->id);
				if (tree->left != NULL) //tj at_decla
				{
					printf(";left ;---\n");
					return check(tree->left, tds);
				}
				if (tree->right->id == AT_FUNCT)
				{	
					printf(";Funct ;---\n");			
					return check(tree->right, tds);
				}
				if (tree->right->id == AT_VAR)
				{
					printf(";VAR ;---\n");
					type = tree->type;
					return checkType(tree->right, type, tds);
				}
				
				
				break;				

			case AT_INSTRUCTION : 
				if(tree->right != NULL && tree->left != NULL) {
					printf(";---GPS = tree_id : %d AT_INSTRUCTION RIGHT ;---\n", tree->id);
					return check(tree->right, tds) && check(tree->left, tds);
				}
				if(tree->right == NULL && tree->left != NULL) {
					printf(";---GPS = tree_id : %d AT_INSTRUCTION LEFT ;---\n", tree->id);
					return check(tree->left, tds);
				}
				else
				{
					return OK;
				}
				break;
			case AT_AFFECT : 
				printf(";---GPS = tree_id : %d AT_AFFECT RIGHT ;---\n", tree->id);
				node = alreadyIsSymbol(tds,tree->left->sval,3, tree->fnctId, 1, 0); 
				if (node != NULL)
				{	//printf(";--varType : %d --\n", node->varType);
					switch(node->varType)
					{
						
						case VAL_INT : 
						//	printf(";--type : %d --\n", checkType(tree->right,VAL_INT,tds));							
							if(checkType(tree->right,VAL_INT,tds) == 2)
							{
								return OK;
							}
							
							break;
						
						case VAL_BOOL : 
							//printf(";--type : %d --\n", checkType(tree->right,VAL_BOOL,tds));	
							if(checkType(tree->right,VAL_BOOL,tds)==3)
							{
								
								return OK;
							}
							
							break;
						// Si ID no_type
						default : printf(";Erreur l'affectation a %s est mal typee\n",tree->left->sval);
							return KO;
					}
					printf(";Heu?\n");
					return KO;
				}else{
					// Sinon retourne KO
					//printf(";Erreur impossible de faire une affectation sur %s car non declaree\n",tree->left->sval);
					return KO;
				}
				
				break;
			case AT_EXPRD :  
				if(tree->left != NULL) {
					printf(";---GPS = AT_EXPRD LEFT ;---\n");
					if (tree->left->id == 0) { // Si tree->left->id est AT_VAR (type 5 dans l'arbre et autre type dans la table des symboles;
						return OK;
					}
					else {
					type = tree->left->type;
					//printf(";°°° %d °°°", type);
					return checkType(tree->left, type, tds);
					}
				}
				break;

			case AT_WRITE : printf(";---GPS = AT_WRITE RIGHT ;---\n");
				if(tree->right != NULL) {
					//printf(";---GPS = tree_id : %d AT_WRITE RIGHT ;---\n", tree->id);	
					// Verifie si le type du noeud left est VAL_INT
					if(checkType(tree->right, VAL_INT, tds)==2)
					{
						return OK;
					}else{
						printf(";Erreur de typage avec WRITE\n");
						return KO;
					} 
				}
				else 
					return KO;
				break;
			case AT_READ : printf(";---GPS = AT_READ RIGHT ;---\n");
				if(tree->right != NULL) {
					//printf(";---GPS = tree_id : %d AT_READ RIGHT ;---\n", tree->id);
					//type = tree->right->type;
					//return checkType(tree->right, type, tds);
					if(checkType(tree->right, VAL_INT, tds)==2)
					{
						return OK;
					}else{
						printf(";Erreur de typage avec READ\n");
						return KO;
					}  
				}
				else 
					return KO;
				
				break;
			case AT_RETURN : 
				if(tree->right != NULL) {
					printf(";---GPS = tree_id : %d AT_RETURN RIGHT ;---\n", tree->id);
					type = tds->up->varType;
					return checkType(tree->right,type,tds);
					
				} return OK;						
				break;	
			case AT_IF : 
				// Si "ExprD" est de type VAL_BOOL
				if(checkType(tree->left,VAL_BOOL,tds) == 3)
				{
					// Si instruction vide dans le bloc
					if(tree->right == NULL)
						return OK;
					else
						return check(tree->right,tds);
					}else{	
						printf(";Error IF\n");
					return KO;
				}
				break;
	

			case AT_InstructionIF : 
				if(tree->left != NULL) {
					//printf(";---GPS = tree_id : %d AT_INSTRUCTIONIF LEFT ;---\n", tree->id);
					return check(tree->left, tds);
				}
				else
				{
					return OK;
				}
				break;	
			case AT_InstructionIFELSE : 
				if(tree->left != NULL)
				{
					return check(tree->left,tds);
				}
				if(tree->right != NULL)
				{
					return check(tree->right,tds);
				}
				if(tree->left == NULL && tree->right == NULL)
				{
					return OK;
				}
				break;	
			case AT_WHILE : 
				// Si "ExprD" est de type VAL_BOOL
				if(checkType(tree->left,VAL_BOOL,tds) == 3)
				{
					if(tree->right == NULL)
						return OK;
					else
						return check(tree->right,tds);
				}else{	
					printf(";Error WHILE\n");
					return KO;
				}
				break;			
			case AT_FUNCTPARAM :
				printf(";---GPS = tree_id : %d AT_FUNCTPARAM ;---\n", tree->id);
				if(tree->left != NULL)
				{
					return check(tree->left,tds);
				}
				if(tree->right != NULL)
				{
					return check(tree->right,tds);
				}	
				break;	
			
			
			case AT_LISTPARAM :
				printf(";---GPS = tree_id : %d AT_LISTPARAM ;---\n", tree->id);	
				if(tree->left != NULL)
				{
					return check(tree->left,tds);
				}
				if(tree->right != NULL)
				{
					return check(tree->right,tds);
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
						node = alreadyIsSymbol(tds, tree->sval, 3, tree->fnctId, 1, 0); 
						//printf("-- %s -- ", node->id);
						if(node != NULL) // si variable existe
						{
							if(node->varType == type)
							{	//printf("OK -> %d", type);
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
							if(checkType(tree->left,VAL_INT,tds)==2 && checkType(tree->right,VAL_INT,tds)==2)
								return VAL_INT;
							else {
								printf(";Error : VAL_INT OK but -> AT_PLUS\n");
								return KO; 
							} 
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
							if(checkType(tree->left,VAL_INT,tds)==2 && checkType(tree->right,VAL_INT,tds)==2)
								return VAL_INT;
							else {
								printf(";Error : VAL_INT OK but -> AT_MOINS\n");
								return KO; 
								} 
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
							if(checkType(tree->left,VAL_INT,tds)==2 && checkType(tree->right,VAL_INT,tds)==2)
								return VAL_INT;
							else {
								printf(";Error : VAL_INT OK but -> AT_FOIS\n");
								return KO; 
							} 
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
							if(checkType(tree->left,VAL_INT,tds)==2 && checkType(tree->right,VAL_INT,tds)==2)
								return VAL_INT;
							else {
								printf(";Error : VAL_INT OK but -> AT_DIVISE\n");
								return KO; 
								} 
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
								
								if(checkType(tree->right, VAL_BOOL,tds)==3)
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
								  //return VAL_BOOL;   // Avant : decommenter lignes au dessus
								}
						}
						break;

			
			case AT_NB : 
						printf(";---GPS = tree_id : %d AT_NB ;---\n", tree->id);
						if (type == VAL_INT)
							return VAL_INT;
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
	
			case AT_APPELF :
					printf(";---GPS = tree_id : %d AT_APPELF ;---\n", tree->id);

int nbOverLoad = checkNbFunctSymbol(tds, tree->sval, 1, -1, 0, 0); // renvoie le nombre d'overload de la fonction

if(nbOverLoad != -1) // si fonction existe
{ 
	printf("; APPELF -> %s\n",tree->sval);
	int cpt = 1; // 1 car elle existe dans la TDS
	
	while(cpt <= nbOverLoad)
	{
		
		int check = 0;
		function = alreadyIsSymbol(tds, tree->sval,1, cpt, 1, 0);
		printf("; APPELF -> %s ET cpt = %d\n",tree->sval, cpt);				
		if(tree->right == NULL) // si appel de fonction sans arg
		{
			if(function->down->state != 2) // si la fonction a bien aucun argument dans sa déclaration
			{
				if(type == function->varType) 
					return type;
				else{	
					check = 1;
					cpt ++;
					continue;
					/*
					printf("; La fonction %s retourne un type incorrect -> %d - %d \n",function->id,function->varType, type);
					return KO;
					*/
				}
			}else{
				check = 1;
				cpt ++;
				continue;
				/*
				printf(";ERROR Appel de la fonction %s avec trop peu arguments\n",function->id);
				return KO;
				*/
			}	
		}
		else
		{
			// si appel de fonction AVEC arg
			ASTTREE treeSafe = tree;
			node = function->down;
			treeSafe = treeSafe->right;
			int b = 0;
			while(treeSafe != NULL){
				
				if(node->state != 2 || node == NULL)
				{
					
					check = 1;
					cpt ++;
					b = 1;
					break;
					/*
					printf(";ERROR Appel de la fonction %s avec trop arguments\n",function->id);
					return KO;
					*/
				}
				
				if(checkType(treeSafe->right,node->varType,tds) != node->varType)  //si erreur renvoie 0
				{
					
					check = 1;
					cpt ++;
					b = 1;
					break;
					
					/*
					printf(";ERROR Argument mal type dans l'appel de fonction %s\n",function->id);
					return KO;
					*/
				}
				
				node = node->next; 
				treeSafe = treeSafe->left; 
				
				
			}
			
			
			if(b == 1)
			{
				
				continue;
			}		
			if(node != NULL && node->state == 2)
			{
				
				check = 1;
				cpt ++;
				continue;
				/*
				printf(";ERROR Appel de la fonction %s avec trop peu arguments\n",function->id);
				return KO;
				*/
			}
			
			if(type == function->varType) 
			{
				
				return type;
			}else{
				check = 1;
				cpt ++;
				continue;
				/*
				printf("; La fonction retourne un type incorrect\n");
				return KO;
				*/
			}
		}
		
			
		
	}
	// End while
	if(check == 0)
	{
		return OK; 
	}
	else
	{
		return KO;
	}
	
}else{
	printf("; La fonction %s est inexistante\n",tree->sval);
	return KO;
}

					break;

			
			default : printf(";Erreur de typage check type\n");
						fprintf(stderr,";KO\n");
						return KO;
		}
	}
}
