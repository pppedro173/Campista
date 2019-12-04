#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "tendas.h"
#include "arvores.h"
#include "structs.h"

/******************************************************************************
* cria_tenda()
*
* Arguments: tenda - A pointer to a tent structure
* 			 L - Number of lines
* 			 C -  Number of columns
*     
* Returns: (void)
* Side-Effects: Instanciates a tent structure
*
* Description: Initializes a tent 
* 
*****************************************************************************/

void cria_tenda(Tenda *tenda, int C, int L){
	
	tenda->local.C = C;
	tenda->local.L = L;
	tenda->isassoc =0;
	
}

/******************************************************************************
* get_tendas()
*
* Arguments: matriz_map - a matrix whith the map
* 			 N_tendas - Total Number of tents in the map
* 			 L - Number of lines
* 			 C -  Number of columns
*     
* Returns: (Tenda *)
* Side-Effects: Creates a vector of tents whith all the tents in the map
*
* Description: Initializes a vector of tents
* 
*****************************************************************************/

Tenda *get_tendas(int **matriz_map,int N_tendas,int L,int C){
	
	int i,j,counter=0;
	Tenda *aux;
	
	aux=(Tenda*)malloc(sizeof(Tenda)*N_tendas);
		
	for(i=0;i<L;i++){
		for(j=0;j<C;j++){
			if(matriz_map[i][j]==2){
				cria_tenda(&aux[counter],j,i);
				counter++;
			}			
		}
	}
	
	return aux;
}

/******************************************************************************
* free_vec_tendas()
*
* Arguments: vec - A vector of tents
*     
* Returns: (void)
* Side-Effects: frees alocated memory
*
* Description: frees a vector of tents
* 
*****************************************************************************/


void free_vec_tendas(Tenda *vec){
	
	free(vec);
}

/******************************************************************************
* check_T_LC()
*
* Arguments: mat - A matrix whith the map
* 			 l0 - Coordinate "y" of a point in the map
* 			 c0 - Coordinate "x" of a point in the map
* 			 N_T_L - A vector whith the number of tents per line
* 			 N_T_C - A vector whith the number of tents per column
* 			 L - Number of lines
* 			 C - Number of columns
*     
* Returns: (int)
* Side-Effects: Returns 1 if a point cannot have a tent due to the number 
* 				of tents in a respective a line or column. Returns 0 otherwise
*
* Description: Returns 1 if a point cannot have a tent due to the number 
* 			 of tents in a respective a line or column. Returns 0 otherwise 
* 
*****************************************************************************/

int check_T_LC(int **map,int l0,int c0,int *N_T_L,int *N_T_C,int L,int C){
	int i=0;
	int t_L=0;
	int t_C=0;
	
	
	for(i=0;i<C;i++){
		if(map[l0][i]==2) t_L++;
	}
	
	for(i=0;i<L;i++){
		if(map[i][c0]==2) t_C++;
	}
	
	if(map[l0][c0]==2){
		if(t_L<=N_T_L[l0] || t_C<=N_T_C[c0])return 0; 
	}
	
	
	if(t_L+1<=N_T_L[l0]&& t_C+1<=N_T_C[c0]) return 0; 
	
	return 1;
}

/******************************************************************************
* associa_TA()
*
* Arguments: A - A tree
* 			 B - A tent
*     
* Returns: (void)
* Side-Effects: Associates a tree and a tent
*
* Description: Associates a tree and a tent 
* 
*****************************************************************************/	
	
void associa_TA(Arvore *A,Tenda *B){	
	B->isassoc=1;
	A->isassoc=1;	
}	

/******************************************************************************
* deassocia_TA()
*
* Arguments: A - A tree
* 			 B - A tent
*     
* Returns: (void)
* Side-Effects: Deassociates a tree and a tent
*
* Description: Deassociates a tree and a tent 
* 
*****************************************************************************/	

void deassocia_TA(Arvore *A,Tenda *B){	
	B->isassoc=0;
	A->isassoc=0;	
}

/******************************************************************************
* check_tendas_C()
*
* Arguments: mat - A matrix whith the map
* 			 N_T_L - A vector whith the number of tents per line
* 			 N_T_C - A vector whith the number of tents per column
* 			 L - Number of lines
* 			 C - Number of columns
*     
* Returns: (int)
* Side-Effects: Returns 1 if a point cannot have a tent due to the number 
* 				of tents in a respective a line or column. Returns 0 otherwise
*
* Description: Returns 1 if a point cannot have a tent due to the number 
* 			 of tents in a respective a line or column. Returns 0 otherwise 
* 
*****************************************************************************/	
	
int check_tendas_C(int **mat,int L,int C,int *N_T_L,int *N_T_C){
	
	int ntl=0;
	int ntc=0;
	int i=0;
	int j=0;
	
	
	for(i=0;i<L;i++){
		ntl=0;
		for(j=0;j<C;j++){
			if(mat[i][j]==2) ntl++;
		}
		if(N_T_L[i]<ntl) return 1; //viola restrição
	}
	
	for(i=0;i<C;i++){
		ntc=0;
		for(j=0;j<L;j++){
			if(mat[j][i]==2) ntc++;
		}
		if(N_T_C[i]<ntc)return 1;
	}
	
	return 0; //não viola restrição
}
			
/******************************************************************************
* alldone()
*
* Arguments: vec - A vector whith all the tents in the map
* 			 N_tendas -  The lenght of that vector
*     
* Returns: (bool)
* Side-Effects: Returns true or false
*
* Description: Returns true if all tents are associated whith a tree and false
* 			   otherwise 
* 
*****************************************************************************/
		
bool alldone(Tenda *vec,int N_tendas){
	
	int i=0;
	
	for(i=0;i<N_tendas;i++){
		if(vec[i].isassoc==0) return false;
	}
	
	return true;
	
}

/******************************************************************************
* findunassoc()
*
* Arguments: vec - A vector whith all the tents in the map
* 			 N_tendas -  The lenght of that vector
*     
* Returns: (int)
* Side-Effects: Returns an integer
*
* Description: Returns the possition on the vector of a tent not associated yet 
* 
*****************************************************************************/		
		
int findunassoc(Tenda *vec,int N_tendas){
	
	int i=0;
	
	for(i=0;i<N_tendas;i++){
		if(vec[i].isassoc==0) return i;
	}	
	
	return -1;
}

/******************************************************************************
* check_tendas_adj()
*
* Arguments: mat - A matrix whith the map
* 			 l0 - Coordinate "y" of a point in the map
* 			 c0 - Coordinate "x" of a point in the map
* 			 L - Number of lines
* 			 C - Number of columns
*     
* Returns: (int)
* Side-Effects: Checks if a point has adjacent tents
*
* Description: Checks if a point has adjacent tents, has soon has it finds 
* 				evidence of that returns 1, if it doesn't find an adjacent
* 				tent returns 0.
* 
*****************************************************************************/	
		
int check_tendas_adj(int **mat,int l0,int c0,int L,int C){
	
	
	if(l0-1>=0 && l0-1<=L-1 && c0>=0 && c0<=C-1){
		if(mat[l0-1][c0]==2) return 1; //tem tenda adj
	}
	
	if(l0+1>=0 && l0+1<=L-1 && c0>=0 && c0<=C-1){
		if(mat[l0+1][c0]==2) return 1;
	}
	
	if(l0>=0 && l0<=L-1 && c0-1>=0 && c0-1<=C-1){
		if(mat[l0][c0-1]==2) return 1;
	}
	
	if(l0>=0 && l0<=L-1 && c0+1>=0 && c0+1<=C-1){
		if(mat[l0][c0+1]==2)return 1;
	}
		
	if(l0-1>=0 && l0-1<=L-1 && c0-1>=0 && c0-1<=C-1){
		if(mat[l0-1][c0-1]==2) return 1;
	}
	
	if(l0+1>=0 && l0+1<=L-1 && c0-1>=0 && c0-1<=C-1){
		if(mat[l0+1][c0-1]==2) return 1;
	}
	
	if(l0-1>=0 && l0-1<=L-1 && c0+1>=0 && c0+1<=C-1){
		if(mat[l0-1][c0+1]==2) return 1;
	}
	
	if(l0+1>=0 && l0+1<=L-1 && c0+1>=0 && c0+1<=C-1){
		if(mat[l0+1][c0+1]==2) return 1;
	}
	
	return 0;
}
	
	
bool alldone2(Mapa map){
	int i,j,counter=0;
	
	for(i=0;i<map.L;i++){
		for(j=0;j<map.C;j++){
			if(map.matriz_map[i][j]==2) counter++;
		}
	}
	if(counter==map.N_tendas) return true;
	
	return false;
	
}

bool check_is_tent(int **matriz_map,int l0,int c0){
	
	if(matriz_map[l0][c0]==2) return true;
	
	return false;
}


bool check_N_T_L(int *N_T_L,int *N_T_L_curr,int line){
	
	if(N_T_L_curr[line]+1 > N_T_L[line]) return true;
	
	return false;
}

bool check_N_T_C(int *N_T_C,int *N_T_C_curr,int col){
	
	if(N_T_C_curr[col]+1 > N_T_C[col]) return true;
	
	return false;
}	

bool is_safe(Mapa map,int line,int col){
	if(check_is_tree(map.matriz_map,line,col)) return false;
	//printf("A\n");
	if(check_is_tent(map.matriz_map,line,col)) return false;
	//printf("b\n");
	if(check_adj_trees(map.matriz_map,line,col,map.L,map.C)!=0) return false;
	//printf("c\n");
	if(check_tendas_adj(map.matriz_map,line,col,map.L,map.C)==1) return false;
	//printf("d\n");
	if(check_N_T_L(map.N_T_L,map.N_T_L_curr,line)) return false;
	//printf("e\n");
	if(check_N_T_C(map.N_T_C,map.N_T_C_curr,col)) return false;
	//printf("f\n");
	return true;
	
}


void put_tent(Mapa *map,int line,int col){
	//printf("puts tent in line = %d e col =%d \n",line,col);
	map->matriz_map[line][col]=2;
	map->N_T_L_curr[line]=map->N_T_L_curr[line]+1;
	map->N_T_C_curr[col]=map->N_T_C_curr[col]+1;
	
}
	
void takes_tent(Mapa *map,int line,int col){
	
	map->matriz_map[line][col]=0;
	map->N_T_L_curr[line]=map->N_T_L_curr[line]-1;
	map->N_T_C_curr[col]=map->N_T_C_curr[col]-1;
}	
