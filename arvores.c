#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "arvores.h"
#include "mapa.h"
#include "structs.h"

/******************************************************************************
* cria_arvore()
*
* Arguments: arvore - A pointer to a tree structure
* 			 L - Number of lines
* 			 C -  Number of columns
*     
* Returns: (void)
* Side-Effects: Instanciates a tree structure
*
* Description: Initializes a tree 
* 
*****************************************************************************/

void cria_arvore(Arvore *arvore, int C, int L){
	
	arvore->local.C = C;
	arvore->local.L = L;
	arvore->isassoc =0;
	
}


/******************************************************************************
* get_arvores()
*
* Arguments: matriz_map - a matrix whith the map
* 			 N_arvores - Total Number of trees
* 			 L - Number of lines
* 			 C -  Number of columns
*     
* Returns: (Arvore *)
* Side-Effects: Creates a vector of trees whith all the trees in the map
*
* Description: Initializes a vector of trees
* 
*****************************************************************************/

Arvore *get_arvores(int **matriz_map,int N_arvores,int L,int C){
	
	int i,j,counter=0;
	Arvore *aux;
	
	aux=(Arvore*)malloc(sizeof(Arvore)*N_arvores);
		
	for(i=0;i<L;i++){
		for(j=0;j<C;j++){
			if(matriz_map[i][j]==1){
				cria_arvore(&aux[counter],j,i);
				counter++;
			}			
		}
	}
	
	return aux;
}

/******************************************************************************
* free_vec_arvores()
*
* Arguments: vec - A vector of trees 
*     
* Returns: (void)
* Side-Effects: frees alocated memory
*
* Description: frees a vector of trees
* 
*****************************************************************************/
 			
void free_vec_arvores(Arvore *vec){
	
	free(vec);
}

/******************************************************************************
* check_adj_trees()
*
* Arguments: mat - A matrix whith the map
* 			 l0 - Coordinate "y" of a point in the map
* 			 c0 - Coordinate "x" of a point in the map
* 			 L - Number of lines
* 			 C - Number of columns
*     
* Returns: (int)
* Side-Effects: Checks if a point has adjacent trees
*
* Description: Checks if a point has adjacent trees, has soon has it finds 
* 				evidence of that returns 0, if it doesn't find an adjacent
* 				tree returns 1.
* 
*****************************************************************************/



int check_adj_trees (int **mat,int l0,int c0,int L,int C){
	//print_map(mat,L,C);
	if(l0-1>=0 && l0-1<=L-1 && c0>=0 && c0<=C-1){	
		//printf(" l0-1=%d , c0= %d \n",l0-1,c0);	
		if(mat[l0-1][c0]==1) return 0; //tem arvore adj logo pode ter tenda
	}
	
	if(l0+1<=L-1 && l0+1>=0 && c0>=0 && c0<=C-1){
		//printf(" l0+1=%d , c0= %d \n",l0+1,c0);			
		if(mat[l0+1][c0]==1) return 0;
	}
	
	if(c0-1>=0 && c0-1<=C-1 && l0>=0 && l0<=L-1){
		//printf(" l0=%d , c0-1= %d \n",l0,c0-1);	
		if(mat[l0][c0-1]==1) return 0;
	}
	
	if(c0+1<=C-1 && c0+1>=0 && l0>=0 && l0<=L-1){	
		//printf(" l0=%d , c0+1= %d \n",l0,c0+1);		
		if(mat[l0][c0+1]==1) return 0;
	}
	
	return 1; //não existe arvores adj logo não pode ter tenda certamente
}

/******************************************************************************
* check_adj_trees_number()
*
* Arguments: mat - A matrix whith the map
* 			 l0 - Coordinate "y" of a point in the map
* 			 c0 - Coordinate "x" of a point in the map
* 			 L - Number of lines
* 			 C - Number of columns
* 			 map - A map
*     
* Returns: (int)
* Side-Effects: Checks how many adjacent tree a point has 
*
* Description: Returns the number of adjacent trees of a point in the map
* 
*****************************************************************************/

int check_adj_trees_number(int **mat,int l0,int c0,int L,int C,Mapa map){
	
	int tree_adj=0;
	
	if(l0-1>=0 && l0-1<=L-1 && c0>=0 && c0<=C-1){	
		if(mat[l0-1][c0]==1 && get_arvore(map.vec_arvores,l0-1,c0,map.N_arvores).isassoc==0) tree_adj++; //tem arvore adj não associada
	}
	
	if(l0+1<=L-1 && l0+1>=0 && c0>=0 && c0<=C-1){
		if(mat[l0+1][c0]==1 && get_arvore(map.vec_arvores,l0+1,c0,map.N_arvores).isassoc==0) tree_adj++;
	}
	
	if(c0-1>=0 && c0-1<=C-1 && l0>=0 && l0<=L-1){
		if(mat[l0][c0-1]==1 && get_arvore(map.vec_arvores,l0,c0-1,map.N_arvores).isassoc==0) tree_adj++;
	}
	
	if(c0+1<=C-1 && c0+1>=0 && l0>=0 && l0<=L-1){	
		if(mat[l0][c0+1]==1 && get_arvore(map.vec_arvores,l0,c0+1,map.N_arvores).isassoc==0) tree_adj++;
	}
	
	return tree_adj; //não existe arvores adj logo não pode ter tenda certamente	
	
	
}

/******************************************************************************
* get_arvore()
*
* Arguments: vec - a vector of trees
* 			 linhas - Coordinate "y" of a point in the map
* 			 coluna - Coordinate "x" of a point in the map
* 			 N_arvores - Number of trees
*     
* Returns: (Arvore)
* Side-Effects: Returns a tree
*
* Description: Returns a specific tree on the map according to the coordinates 
* 			   given.
* 
*****************************************************************************/

Arvore get_arvore (Arvore *vec,int linhas,int coluna,int N_arvores){
	
	int i=0;
	
	for(i=0;i<N_arvores;i++){
		if(vec[i].local.C==coluna && vec[i].local.L==linhas) return vec[i];		
	}
	
	printf("erro \n");
	exit(0);
}

/******************************************************************************
* check_is_possible()
*
* Arguments: tent - A tent structure
* 			 tree - A tree structure
*     
* Returns: (bool)
* Side-Effects: Checks if a tree can be associated whith a specific tent
*
* Description: If possible returns true and associates a tent whith a tree 
* 			   if the association is not possible returns false.
* 
*****************************************************************************/

bool check_is_possible(Tenda tent,Arvore tree){
	
	
	if(tree.isassoc==1) return false;
	
	if(tent.local.L+1==tree.local.L && tent.local.C==tree.local.C) return true;
	
	if(tent.local.L-1==tree.local.L && tent.local.C==tree.local.C) return true;
	
	if(tent.local.L==tree.local.L && tent.local.C+1==tree.local.C) return true;
	
	if(tent.local.L==tree.local.L && tent.local.C-1==tree.local.C) return true;
	
	return false;
	
	
}
