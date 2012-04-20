/* sym.c
 *
 */

#include "sym.h"

SYMTABLE creaNode()
{
	SYMTABLE node = (SYMTABLE ) malloc(sizeof(NOEUD));

	if (node == NULL)
	{
	  fprintf(stderr,";KO\n");
	  printf(";ERROR : cannot malloc in createNode()\n");
	  exit(1);
 	}

 	node->id = NULL;       // Identifiant du noeud
 	node->address = -1;    // location pour pcode avant -1
 	node->varType = -1;    // Type de la variable
	node->ref = 0;         // variable par défaut
	node->fnctId = 0;      // suffixe du nom de la fonction
	
	
 	node->next = NULL;     // Pointeur next du noeud
 	node->previous = NULL; // Pointeur previous du noeud
 	node->up = NULL;       // Pointeur parent du noeud
 	node->down = NULL;     // Pointeur child du noeud

 	return node;
}

void printSymbolTableGraphViz(SYMTABLE s)
{
	if (s != NULL && s->id != NULL)
 	{
		
 		printf("\"%p\";\n", s);
 		if (s->id == NULL)
 			printf("NULL");
 		else{
 		printf("\"%p\"[shape=box, color=\"#e6e8f2\", fontcolor=\"#000000\",label=\"addr: %p id: %s address: %d type: %d niv: %d state: %d fnctId : %d;\"];\n", s,s,s->id,s->address,s->varType,s->levelNode,s->state,s->fnctId);
			if(s->next!=NULL)
			{
			printf("\"%p\" -> \"%p\" [color=\"#1DED16\", label=\"Next\"];\n", s, s->next);
			}
			if(s->down!=NULL)
			{
			printf("\"%p\" -> \"%p\"[color=\"#ED165E\", label=\"Down\"];\n", s, s->down);
			}
			if(s->up!=NULL)
			{
			printf("\"%p\" -> \"%p\"[color=\"#162BED\", label=\"Up\"];\n", s, s->up);
			}			

		}
 		if(s->down != NULL)
 			printSymbolTableGraphViz(s->down);
 		printSymbolTableGraphViz(s->next);
 	}
}

SYMTABLE checkSymbolLevel(SYMTABLE s, char* name, int state, int fnctId, int schFnct)
{
 	SYMTABLE retour = NULL;
 	if(s != NULL)
	{	
		if(strcmp(s->id,name) != 0)
		{
 			return checkSymbolLevel(s->previous, name, state, fnctId, schFnct);
 		}
 		else{
			if(state == 1) // recherche d'une variable ou d'un argument
			{
				if(fnctId == -1) // -1 -> quand on recherche juste si la fonction existe...
					retour = s;
				else
					if(schFnct == 0)// si on recherche par rapport au niveau de surcharge
					{	
						if(fnctId > s->fnctId) //tand que l'ID du noeud est plus grand à l'ID de la TDS
						{
							return checkSymbolLevel(s->previous, name, state, fnctId, schFnct);	
						}
						else
						{	
							retour = s;
						}
					}else{
						if(fnctId == s->fnctId)
						{
							retour = s;
						}
						else
						{						
							return checkSymbolLevel(s->previous, name, state, fnctId, schFnct);
						}
					}					
			}else{
				if(state == 3)
				{
					if(s->state == 0 || s->state == 2)
						retour = s;
					else
						return checkSymbolLevel(s->previous, name, state, fnctId, schFnct);
				}
				else
				{
					// si on trouve une variable locale ayant le même nom qu'un paramètre formel
					if((s->state == 2 && state == 0) || (s->state == 0 && state == 2))
					{
						retour = s;
					}else{
						if(s->state != state) // fonction peut avoir le meme nom qu'une variable ou un paramètre
						{
							return checkSymbolLevel(s->previous, name , state, fnctId, schFnct);
						}else{
							retour = s;
				
						}
					}
				}
			}
 		}
 	}
 	return retour;
}


SYMTABLE alreadyIsSymbolLevel(SYMTABLE s, char* name,int state, int fnctId, int schFnct)
{
 	if(s == NULL) {
		printf("; BORDEL-1");		
		return NULL;
	}
 	while(s->next != NULL) s = s->next;

 	return checkSymbolLevel(s->previous, name, state, fnctId, schFnct);
}


SYMTABLE alreadyIsSymbol(SYMTABLE s, char* name, int state, int fnctId, int schFnct)
{

 	if (s == NULL)
	{
		printf("; BORDEL0");
 		return NULL;
	}

 	SYMTABLE symbol = alreadyIsSymbolLevel(s,name,state,fnctId, schFnct);

 	if (symbol == NULL)
	{
 		if(s->up != NULL)
		{
 			return alreadyIsSymbol(s->up, name,state,fnctId, schFnct);
		}else{
			printf("; BORDEL1");
 			return NULL;
 		}
 	}else{
 		return symbol;
 	}
}

SYMTABLE addToSymbolTable(SYMTABLE s, char* name, int state, int type, int fnctId, int schFnct)
{	

	
	if (alreadyIsSymbolLevel(s,name,state,fnctId, schFnct) != NULL) {
		printf("; BORDEL2");
		return NULL;
	}
	else {

	printf("; ... ajout de %s dans la table, state = %d, type = %d, fnctId = %d\n", name, state, type, fnctId); // a virer	

	  while(s->next != NULL) {
	    s = s->next;
	  }
	  printf("; BORDEL56");
	  // Spécifie les infos
	  s->id = name;
	  s->varType = type;
	  s->state = state;
	  s->fnctId = fnctId;
	  
	  printf("; ....... s->id = %s, s->fnctId = %d\n", s->id,s->fnctId);

	  // Specifie son level
	  if(s->up == NULL)
	    s->levelNode = 0;
	  
	  // Cree un noeud Next
	  s->next = creaNode();
	  s->next->previous = s;
	  
	  // Specifie le parent et le level
	  if (s->previous != NULL) {
	    s->up= s->previous->up;
	    s->levelNode = s->previous->levelNode;
	  }
	
	  // Si c'est une fonction on ajoute un enfant
	  if(state == 1) {
		
	    s->down = creaNode();
	    s->down->up = s;
	    s->down->levelNode = s->levelNode + 1;
	  }
	  
	  return s;
	}
}

// liberation de la memoire
void freeSymbolTable(SYMTABLE s) {

  if (s != NULL) {
    if (s->down != NULL) {
      freeSymbolTable(s->down);
    }
    freeSymbolTable(s->next);
    free(s);
  }

}


int checkNbFunctSymbol(SYMTABLE s, char* name, int state, int fnctId, int schFnct) { // retourne le nombre de fois qu'une fonction est imbriquée
	SYMTABLE sym;

	if(s == NULL) {
		printf("; BORDEL58");		
		return -1; //erreur...
	}
	//printf("; YOYO -> : alreadyIsSymbol(s, %s,%d,%d, %d); \n",name,state,fnctId, schFnct); 
	sym = alreadyIsSymbol(s, name,state,fnctId, schFnct); 	
	
	if(sym != NULL){
 		if(strcmp(sym->id,name) == 0)
		{
 			if(state == 1) // recherche d'une fonction
			{
				//printf("; YOYO : %d \n",sym->fnctId); 
				return sym->fnctId;
				
			}
 		}
		else
		{		
			printf("; BORDEL59");		
			return -1; //erreur...
		}
		
 	}
	else
	{		
		printf("; BORDEL60");		
		return -1; //erreur...
	}


}



// fonctionne a l envers...

void computeLocations(SYMTABLE s) {
  
  SYMTABLE local = s;
  int available = 5; // 5 pour le block réservé par la fonction dans la stack (avant 0)
  
  /*
  if( strcmp(s->id, "main") == 0 ) {
    available = 0;
  }
  else {
    available = 5;
  }
  */

  if( local->up != NULL ) {
    if( strcmp(local->up->id, "main") == 0 ) {
      available = 0;
    }
  }

  while(local != NULL) {

    if(local->down != NULL) {
      computeLocations(local->down);
    }
  
    if(local->next != NULL) {        
      if ( local->state != 1 ) { // pour n identifier que les adresses relatives des variables/constantes 
	local->address = available;
	printf("; ... localisation de %s : %d\n", local->id, available);
	available++;
      }
    }
    
    local = local->next;
    
  }

}

int getMaxMemoryUsage(SYMTABLE s)
{
        SYMTABLE tmp = s->down;
	int max = 0; // avant O (?1 dans le cas ou une fonction renvoit juste une constante)
	//if ( strcmp(s->id, "main") == 0 ) { max = 0;}
  	while (tmp->next != NULL)
    	{
		if(tmp->state != 1 )
      			max++;
      		tmp = tmp->next;
    	}
  	return max;
}


void printSymbolTable(SYMTABLE s)
{
	if (s != NULL && s->id != NULL)
 	{
 		printf(";--\n; [%p] Id : ", s);
 		if (s->id == NULL)
 			printf("NULL");
 		else{
 			printf("id: %s address: %d type: %d niv: %d state: %d\n;", s->id,s->address,s->varType,s->levelNode,s->state);
 			printf("\t Next : %p, Previous : %p, down : %p, up : %p\n", s->next, s->previous, s->down, s->up);
		}
 		if(s->down != NULL)
 			printSymbolTable(s->down);
 		printSymbolTable(s->next);
 	}
}


int fillTable(ASTTREE tree, SYMTABLE s, int currentType)
{
	int type = currentType;
 	if (tree == NULL)
	{
 		return 0;
 	}else{
		
		if(tree->id == AT_FUNCT) // change de fonction courante
		{
			type = tree->type; 
			SYMTABLE yo = s; // test
			yo = addToSymbolTable(s, tree->sval,1, type, 1, 0);
			
			int ID = 1;			
			while(yo == NULL)
			{
				ID+=1;
				yo = addToSymbolTable(s, tree->sval,1, type, ID, 0);
			}
						
			s = yo;
			tree->fnctId = ID;
			type = -1;// on n'est plus dans les déclarations, on nettoye le type sauvé
			
		} 
		
		/*
		if(tree->id == AT_CODE)
			type = -1; // on n'est plus dans les déclarations, on nettoye le type sauvé
		*/
 		if(tree->id == AT_DECLA) // ajout variable dans la TDS
		{
		
			switch(tree->type) // sauve le type pour les prochaines variables déclarées avant le ";"
			{ 
				case VAL_INT: type = 2;  break;
				case VAL_BOOL: type = 3; break;
				case VAL_ENS: type = 4; break;
			}
		}

		// verifie si la variable est deja declaree
		if(tree->id == AT_VAR)
		{
			if(type != -1)
			{
				s = addToSymbolTable(s, tree->sval,0, type, tree->fnctId, 0); 	
				if(s == NULL) // ajouter la variable sur le niveau courant imbrication "s->level"
				{
 					printf("; ATTENTION VARIABLE %s!, Il existe deja une declaration local annotee\n.",tree->sval);
 					fprintf(stderr,"KO\n");
					exit(1);
				}
			}
 		}
	
		if(tree->id == AT_ARG)
		{
			s = addToSymbolTable(s,tree->sval,2,tree->type, tree->fnctId, 0);
			if(tree->varRef == 1)
			{
					s->ref = 1;
			}			
			if(s == NULL)
			{
 				printf("; ATTENTION ARGUMENT %s !, Il existe deja une declaration local annotee\n.",tree->sval);
 				fprintf(stderr,"KO\n");
				exit(1);
			}
		}
		
		// si fonction ajoutée => tout les pointeurs fils de AT_FUNCT seront sauvés sur un niveau imbrication plus élevé dans la table
		// sauf le fils à droite qui permet d'aller à la fonction suivante sur le même niveau
		if(tree->id  == AT_FUNCT)
		{
			if(tree->right != NULL)
 				fillTable(tree->right, s->down,type);
			if(tree->left != NULL)
 				fillTable(tree->left, s->down,type);
			
		}else{
			if(tree->left != NULL)
				fillTable(tree->left, s,type);
			if(tree->right != NULL)
 				fillTable(tree->right, s,type);
		}
 
 		return 1;
 	}
}
