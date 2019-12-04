#include <stdio.h>
#include <stdlib.h>
#include "mapa.h"
#include "arvores.h"
#include "tendas.h"
#include "structs.h"


/******************************************************************************
* cria_mapa()
*
* Arguments: map - a pointer to a map structure
* 			 L - Number of lines
* 			 C -  Number of columns
* 			 N_arvores - Total Number of trees
* 			 N_tendas - Total Number of tents
* 			 matriz_map - a matrix whith the "actual" map.
*     
* Returns: (void)
* Side-Effects: Instanciates a map structure
*
* Description: Initializes a map 
* 
*****************************************************************************/

void cria_mapa(Mapa* map, int L ,int C,int N_arvores,int N_tendas,int **matriz_map,int *N_T_L,int *N_T_C){
	
	int i=0;
	
	map->L=L;
	map->C=C;
	map->N_T_L=N_T_L;
	map->N_T_C=N_T_C;	
	map->N_arvores=N_arvores;
	map->N_tendas=N_tendas;
	map->matriz_map=matriz_map;	
	map->N_freeps=(L*C)-(N_arvores);
	map->N_T_L_curr=malloc(sizeof(int)*L);
	map->N_T_C_curr=malloc(sizeof(int)*C);
	
	for(i=0;i<L;i++)
		map->N_T_L_curr[i]=0;
		
	for(i=0;i<C;i++)
		map->N_T_C_curr[i]=0;
	
			
}

/******************************************************************************
* add_arvores()
*
* Arguments: vec - a vector whith all the trees in the map
* 			 map - a pointer to a map structure
*     
* Returns: (void)
* Side-Effects: Adds all the trees to their respective map
*
* Description: adds trees to the map.
* 
*****************************************************************************/

void add_arvores(Arvore* vec,Mapa* map){
	
	int i=0;
	map->vec_arvores=vec;
	
	for(i=0;i<map->N_arvores;i++)
		map->matriz_map[vec[i].local.L][vec[i].local.C]=1;
	
		
}
		
/******************************************************************************
* add_tendas()
*
* Arguments: vec - a vector whith all the tents in the map
* 			 map - a pointer to a map structure
*     
* Returns: (void)
* Side-Effects: Adds all the tents to their respective map
*
* Description: adds tents to the map.
* 
*****************************************************************************/	

void add_tendas(Tenda* vec,Mapa* map){
	
	int i=0;
	map->vec_tendas=vec;
	
	for(i=0;i<map->N_tendas;i++)
		map->matriz_map[vec[i].local.L][vec[i].local.C]=2;
		
	
}
/******************************************************************************
* cria_map_mat()
*
* Arguments: L - Number of lines
* 			 C - Number of columns
*     
* Returns: (int**)
* Side-Effects: To remove , not in use
*
* Description: To remove, not in use
* 
*****************************************************************************/
int **cria_map_mat(int L,int C){
	int** aux;
	int i=0;
	aux=malloc(sizeof(int *)*L);
	for(i=0;i<C;i++)
		aux[i]=malloc(sizeof(int)*C);
	
	return aux;
}

/******************************************************************************
* free_matriz_map()
*
* Arguments: mat - a matrix 
* 			 L - Number of lines in the matrix
*     
* Returns: (void)
* Side-Effects: Frees the memory associated whith a matrix
*
* Description: Frees the memory associated whith a matrix
* 
*****************************************************************************/

void free_matriz_map(int **mat,int L){
	int i=0;
	
	for(i=0;i<L;i++){
		free(mat[i]);
	}
		
	free(mat);
		
}

/******************************************************************************
* print_map()
*
* Arguments: mat - a matrix 
* 			 L - Number of lines in the matrix
* 			 C - Number of columns
*     
* Returns: (void)
* Side-Effects: Prints a matrix (Not in use, for testing only)
*
* Description: Prints a matrix (Not in use , for testing only)
* 
*****************************************************************************/

void print_map(int **mat,int L,int C){
	int i,j=0;
	for(i=0;i<L;i++){
		for(j=0;j<C;j++){
			if(mat[i][j]==0)printf(".");
			if(mat[i][j]==1)printf("A");
			if(mat[i][j]==2)printf("T");
		}
		printf("\n");
	}
}

int find_free_p (Mapa map){
	
	int i=0;
	
	for(i=0;i<map.N_freeps;i++)
		if(map.vec_freeps[i].ischecked==0) return i;
	
	printf("GONE WRONG %d \n",i);
	exit(0);
		
	return 0;
}
		
	
void add_freeps(Mapa *map){
	
	int i,j,counter=0;
	
	Freep *vec_freeps=malloc(sizeof(Freep)*map->N_freeps);
	
	for(i=0;i<map->L;i++){
		for(j=0;j<map->C;j++){
			if(map->matriz_map[i][j]==0){
				vec_freeps[counter].local.L=i;
				vec_freeps[counter].local.C=j;
				vec_freeps[counter].ischecked=0;
				counter++;
			}
		}
	}
	
	map->vec_freeps=vec_freeps;
}
					
void checks_freeps(Freep *freepoint){
	
	freepoint->ischecked=1;
}

void unchecks_freeps(Freep *freepoint){
	freepoint->ischecked=0;
}
	
