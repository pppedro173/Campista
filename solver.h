#ifndef __solver__
#define __solver__


#include "structs.h"
#include <stdbool.h>

void solve_A(char *filename,int L,int C,int N_arvores,int N_tendas_por_coluna,int N_tendas_por_linha);

int check_l0co(int l0,int c0,int L,int C);

void solve_B(char *filename,int L,int C,int l0,int c0,int *linha,int T_adj_tree,int T_adj_tenda,int *coluna,int comp_linha,int T_na_linha_l0,int comp_coluna,int T_na_coluna_c0);

void solve_C(char *filename,char variante,int *N_T_L,int *N_T_C,int L,int C,Mapa map);

bool backtrackingalgo(Mapa map);

bool mandatoryalgo(Mapa map,int L,int C);


#endif    /* __solver__ */
