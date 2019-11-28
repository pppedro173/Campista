#ifndef __tendas__
#define __tendas__

#include "structs.h"
#include <stdbool.h>



void cria_tenda ( Tenda* tenda ,int C, int L );

Tenda *get_tendas(int **matriz_map,int N_tendas,int L,int C);

void free_vec_tendas(Tenda *vec);

int check_T_LC(int **map,int l0,int c0,int *N_T_L,int *N_T_C,int L,int C);

void associa_TA(Arvore *A,Tenda *B);

void deassocia_TA(Arvore *A,Tenda *B);

int check_tendas_C(int **mat,int L,int C,int *N_T_L,int *N_T_C);

bool alldone(Tenda *vec,int N_tendas);

int findunassoc(Tenda *vec,int N_tendas);

int check_tendas_adj(int **mat,int l0,int c0,int L,int C);



#endif    /* __tendas__ */
