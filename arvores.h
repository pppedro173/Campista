#ifndef __arvores__
#define __arvores__


#include "structs.h"
#include <stdbool.h>
	
	
void cria_arvore (Arvore *arvore,int C ,int L);
	
Arvore *get_arvores(int **matriz_map,int Numarvores,int L,int C);

void free_vec_arvores(Arvore *vec);

int check_adj_trees (int **mat,int l0,int c0,int L,int C);
	
int check_adj_trees_number(int **mat,int l0,int c0,int L,int C,Mapa map);

Arvore get_arvore (Arvore *vec,int linhas,int coluna,int N_arvores);

bool check_is_possible(Tenda tent,Arvore tree);

bool check_is_tree(int **matriz_map,int l0,int c0);

#endif    /* __arvores__ */
