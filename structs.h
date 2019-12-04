#ifndef __structs__
#define __structs__



typedef struct _Point{
	int C,L;
}Point;

typedef struct _Arvore {
	
	struct _Point local;
	int isassoc;	
	
}Arvore;


typedef struct _Tenda {
	int isassoc;
	struct _Point local;	
	struct _Arvore arvore_associada;	
	int id;
}Tenda;

typedef struct _Freep{
	int ischecked;
	struct _Point local;
}Freep;

typedef struct _Mapa {
	int L;
	int C;
	int *N_T_L;
	int *N_T_L_curr;
	int *N_T_C;
	int *N_T_C_curr;
	int N_arvores;
	int N_tendas;
	int N_freeps;
	int** matriz_map; /* 0- espaço vazio , 1-arvore , 2-tenda*/
	struct _Arvore* vec_arvores;
	struct _Tenda* vec_tendas;
	struct _Freep* vec_freeps;
}Mapa;

#endif    /* __structs__ */
