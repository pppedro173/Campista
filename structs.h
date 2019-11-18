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


typedef struct _Mapa {
	
	int N_arvores;
	int N_tendas;
	int** matriz_map; /* 0- espaço vazio , 1-arvore , 2-tenda*/
	struct _Arvore* vec_arvores;
	struct _Tenda* vec_tendas;
}Mapa;

#endif    /* __structs__ */
