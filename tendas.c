#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "tendas.h"
#include "structs.h"

void cria_tenda(Tenda *tenda, int C, int L){
	
	tenda->local.C = C;
	tenda->local.L = L;
	tenda->isassoc =0;
	
}

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


void free_vec_tendas(Tenda *vec){
	
	free(vec);
}



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
	
	
void associa_TA(Arvore *A,Tenda *B){	
	B->isassoc=1;
	A->isassoc=1;	
}	


void deassocia_TA(Arvore *A,Tenda *B){	
	B->isassoc=0;
	A->isassoc=0;	
}
	
	
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
			
		
bool alldone(Tenda *vec,int N_tendas){
	
	int i=0;
	
	for(i=0;i<N_tendas;i++){
		if(vec[i].isassoc==0) return false;
	}
	
	return true;
	
}
		
		
int findunassoc(Tenda *vec,int N_tendas){
	
	int i=0;
	
	for(i=0;i<N_tendas;i++){
		if(vec[i].isassoc==0) return i;
	}	
	
	return -1;
}	
		
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
	
	
	
