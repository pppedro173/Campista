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

bool alldone2(Mapa map);

bool check_is_tent(int **matriz_map,int l0,int c0);

bool check_N_T_L (int *N_T_L,int *N_T_L_curr,int line);

bool is_safe(Mapa map,int line,int col);

void put_tent(Mapa *map,int line,int col);

void takes_tent(Mapa *map,int line,int col);

#endif    /* __tendas__ */
