#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "arvores.h"
#include "mapa.h"
#include "structs.h"


void cria_arvore(Arvore *arvore, int C, int L){
	
	arvore->local.C = C;
	arvore->local.L = L;
	arvore->isassoc =0;
	
}

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


void free_vec_arvores(Arvore *vec){
	
	free(vec);
}

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

Arvore get_arvore (Arvore *vec,int linhas,int coluna,int N_arvores){
	
	int i=0;
	
	for(i=0;i<N_arvores;i++){
		if(vec[i].local.C==coluna && vec[i].local.L==linhas) return vec[i];		
	}
	
	printf("erro \n");
	exit(0);
}

bool check_is_possible(Tenda tent,Arvore tree){
	
	
	if(tree.isassoc==1) return false;
	
	if(tent.local.L+1==tree.local.L && tent.local.C==tree.local.C) return true;
	
	if(tent.local.L-1==tree.local.L && tent.local.C==tree.local.C) return true;
	
	if(tent.local.L==tree.local.L && tent.local.C+1==tree.local.C) return true;
	
	if(tent.local.L==tree.local.L && tent.local.C-1==tree.local.C) return true;
	
	return false;
	
	
}
