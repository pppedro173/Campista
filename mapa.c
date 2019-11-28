#include <stdio.h>
#include <stdlib.h>
#include "mapa.h"
#include "arvores.h"
#include "tendas.h"
#include "structs.h"


void cria_mapa(Mapa* map, int L ,int C,int N_arvores,int N_tendas,int **matriz_map){
		
	map->N_arvores=N_arvores;
	map->N_tendas=N_tendas;
	map->matriz_map=matriz_map;			
}



void add_arvores(Arvore* vec,Mapa* map){
	
	int i=0;
	map->vec_arvores=vec;
	
	for(i=0;i<map->N_arvores;i++)
		map->matriz_map[vec[i].local.L][vec[i].local.C]=1;
	
		
}
		
	

void add_tendas(Tenda* vec,Mapa* map){
	
	int i=0;
	map->vec_tendas=vec;
	
	for(i=0;i<map->N_tendas;i++)
		map->matriz_map[vec[i].local.L][vec[i].local.C]=2;
		
	
}

int **cria_map_mat(int L,int C){
	int** aux;
	int i=0;
	aux=malloc(sizeof(int *)*L);
	for(i=0;i<C;i++)
		aux[i]=malloc(sizeof(int)*C);
	
	return aux;
}

void free_matriz_map(int **mat,int L){
	int i=0;
	
	for(i=0;i<L;i++){
		free(mat[i]);
	}
		
	free(mat);
		
}

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

