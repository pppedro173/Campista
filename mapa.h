#ifndef __mapa__
#define __mapa__


#include "structs.h"
	
	
void cria_mapa (Mapa* map,int L,int C,int N_arvores,int N_tendas,int **matriz_map,int *N_T_L, int *N_T_C);
	
void add_arvores(Arvore* vec,Mapa* map);

void add_tendas(Tenda* vec,Mapa* map);

int **cria_map_mat(int L,int C);

void free_matriz_map(int **mat,int L);
	
void print_map(int **mat,int L,int C);

int find_free_p (Mapa map);

void add_freeps(Mapa *map);

void checks_freeps(Freep *freepoint);

void unchecks_freeps(Freep *freepoint);

#endif    /* __mapa__ */

