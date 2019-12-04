#include <stdio.h>
#include <stdlib.h>
#include "solver.h"
#include "readfiles.h"
#include "arvores.h"
#include "tendas.h"
#include "mapa.h"
#include "structs.h"



/******************************************************************************
* solve_A()
*
* Arguments: filename - file pointer to write data to.
* 			L - number of lines in the map
* 			C - number of columns in the map
* 			N_arvores - Number of trees in the map
* 			N_tendas_por_coluna - total number of tents according to columns
* 			N_tendas_por_linha - total number of tents according to lines.
* 			
*     
* Returns: (void)
* Side-Effects: Solves a problem of var A. 
*
* Description: Evaluates a map according to the restritions of var. A.
*****************************************************************************/


void solve_A(char *filename,int L,int C,int N_arvores,int N_tendas_por_coluna,int N_tendas_por_linha){
	
	int result = 0;
	char variante = 'A';
	
	
	if(N_tendas_por_linha!=N_tendas_por_coluna){
		write_exit_file(filename,L,C,variante,result);
		return;
	}
	
	
	if(N_arvores<N_tendas_por_coluna){
		write_exit_file(filename,L,C,variante,result);
		return;
	}
	
	result=1;
	
	//é admísivel
	write_exit_file(filename,L,C,variante,result);
	
}



/******************************************************************************
* check_l0co()
*
* Arguments: l0- coord. l0
* 			 c0 -  coord. c0
* 			 L - number of lines in the map
* 			 C - number of columns in the map

* 			
*     
* Returns: (int) 1 if l0 and c0 valid (inside the map) -1 otherwise. 
* Side-Effects:  
*
* Description: Evaluates l0 and c0 coord.
*****************************************************************************/

int check_l0co(int l0,int c0,int L,int C){
	
	if(l0>=L || l0<0) return -1;
	
	if(c0>=C  || c0<0) return -1;
	
	return 1;
}

/******************************************************************************
* solve_B()
*
* Arguments: file - filename to write data to.
* 			l0 - coord l0
* 			c0 - coord c0
* 			linha - vector with the line to which the l0,c0 cell belongs to.
* 			coluna - vector with the colum to which the l0,c0 cell belongs to.
* 			T_adj_tree - Number of adjacent trees to the l0,c0 cell.
* 			T_adj_tenda - Number of adjacent tents to the l0.c0 cell.
* 			T_na_linha_l0 - Number of tents allowed in the l0,c0 cell line.
* 			T_na_coluna_c0 - Number of tents allowed in the l0,c0 cell colum.
* 			comp_linha - Number of tents in the line to which l0,c0 cell belongs.
* 			comp_coluna - Number of tents in the column to which l0,c0 cell belongs.
*     
* Returns: (void)
* Side-Effects: writes a solution to a var B problem
*
* Description: Solvs a var B type problem.
*****************************************************************************/
void solve_B(char *filename,int L,int C,int l0,int c0,int *linha,int T_adj_tree,int T_adj_tenda,int *coluna,int comp_linha,int T_na_linha_l0,int comp_coluna,int T_na_coluna_c0){
	
	char variante = 'B';
	int result =1;
	
	if(linha[c0]==1){
		write_exit_file_B(filename,L,C,variante,result,l0,c0);
		return;
	}
	
	if(T_adj_tree==0){
		write_exit_file_B(filename,L,C,variante,result,l0,c0);
		return;
	}
	
	
	if(T_adj_tenda!=0){
		write_exit_file_B(filename,L,C,variante,result,l0,c0);
		return;
	}
	if(coluna[l0]==2){
		if(comp_linha>T_na_linha_l0 || comp_coluna>T_na_coluna_c0){
			write_exit_file_B(filename,L,C,variante,result,l0,c0);
			return;
		}
	}
	
	if(coluna[l0]!=2){
		if(comp_linha+1>T_na_linha_l0 || comp_coluna+1>T_na_coluna_c0){
			write_exit_file_B(filename,L,C,variante,result,l0,c0);
			return;
		}
	}	
	result=0;
	write_exit_file_B(filename,L,C,variante,result,l0,c0);	
}


/******************************************************************************
* solve_C()
*
* Arguments: filename - file pointer to write data to.
* 			variante - C (because changing code is to much work sometimes)
* 			N_T_L - Number of tents in each line (vector)
* 			N_T_C - Number of tents in each column (vector)
* 			L - number of lines in the map
* 			C - number of columns in the map
* 			map - map structure
* 			
*     
* Returns: (void)
* Side-Effects: Solves a problem of var C. 
*
* Description: Evaluates a map according to the restritions of var. C.
*****************************************************************************/



	
void solve_C(char *filename,int *N_T_L,int *N_T_C,int L,int C,Mapa map){
	
	int result=1;
	int i,j=0;
	
	for(i=0;i<map.N_tendas;i++){
	if(check_tendas_adj(map.matriz_map,map.vec_tendas[i].local.L,map.vec_tendas[i].local.C,L,C)==1){
			write_exit_file_final(filename,map,result);
			return;
		}
	}
	
	
	for(i=0;i<L;i++){
		for(j=0;j<C;j++){
			if(map.matriz_map[i][j]==2){
				if(check_adj_trees(map.matriz_map,i,j,L,C)==1){
					 write_exit_file_final(filename,map,result);
					 return;
				 }
			}
		}
	}
	
	if(check_tendas_C(map.matriz_map,L,C,N_T_L,N_T_C)==1){
		write_exit_file_final(filename,map,result);
		return;
	}
	

	if(mandatoryalgo(map,L,C)){
		write_exit_file_final(filename,map,0);
		return;
	}	
	result=0;
	if(backtrackingalgo(map)){
		write_exit_file_final(filename,map,result);
		return;
	}
	
	
	result=1;
	
	write_exit_file_final(filename,map,result);
	
	
	
	
}

/******************************************************************************
* backtrackingalgo()
*
* Arguments: map - map structure ( with all the map informations)

* 			
*     
* Returns: (bool)
* Side-Effects: Returns true if all tents are associated with their tree 
* 				and false if there isn't a config which allow for each tent
* 				to have it's own tree. 
*
* Description: Attempts to associate each tent whith a tree
*****************************************************************************/

bool backtrackingalgo(Mapa map){
	
	int i=0;
	int aux;
	
	
	if(alldone(map.vec_tendas,map.N_tendas)){
		 return true; //all done
	 }
	
	aux=findunassoc(map.vec_tendas,map.N_tendas);
	for(i=0;i<map.N_arvores;i++){
		if(check_is_possible(map.vec_tendas[aux],map.vec_arvores[i])){ //O problem está aqui!!!!!!!!!!!!!!!!!!!!!!!!!
			associa_TA(&map.vec_arvores[i],&map.vec_tendas[aux]);
			if(backtrackingalgo(map)) return true;
			deassocia_TA(&map.vec_arvores[i],&map.vec_tendas[aux]); 
		}
	}	
	return false;
}

/******************************************************************************
* mandatorylgo()
*
* Arguments: map - map structure ( with all the map informations)
* 			L - number of lines
* 			C - number o columns

* 			
*     
* Returns: (bool)
* Side-Effects: Returns true if all tents are associated with their tree 
* 				and false if there there if detects a tent without a tree 
* 				associated
*
* Description: Takes care o "mandatory" tent-tree associatians (eg. tents which 
* 				only have 1 tree available for association due to the map config).
*****************************************************************************/

bool mandatoryalgo(Mapa map,int L,int C){
	
	int i,j=0;
	int stop=0;
	
	while(stop!=1){
		stop=1;
		for(i=0;i<map.N_tendas;i++){		
			if(check_adj_trees_number(map.matriz_map,map.vec_tendas[i].local.L,map.vec_tendas[i].local.C,L,C,map)==1){
				for(j=0;j<map.N_arvores;j++){
					if(check_is_possible(map.vec_tendas[i],map.vec_arvores[j])){
						associa_TA(&map.vec_arvores[j],&map.vec_tendas[i]);
						stop=0;
					}
				}
			}
		}
	}
	
	if(alldone(map.vec_tendas,map.N_tendas)) return true;
	
	
	return false;
	
}

bool backtrackingalgo2(Mapa map){
	
	
	//int delete=0;
	int i=0;

	if(alldone2(map)){
		 return true; //all done
	 }
	
	//aux=find_free_p(map);
	//printf("matriz_map[%d][%d]=%d and aux.L=%d , aux.C=%d \n",map.vec_freeps[aux].local.L,map.vec_freeps[aux].local.C,map.matriz_map[map.vec_freeps[aux].local.L][map.vec_freeps[aux].local.C],map.vec_freeps[aux].local.L,map.vec_freeps[aux].local.C);
	for(i=0;i<map.N_freeps;i++){
		if(is_safe(map,map.vec_freeps[i].local.L,map.vec_freeps[i].local.C) && map.vec_freeps[i].ischecked==0){
			//printf("is going to put tent in line=%d col=%d \n",map.vec_freeps[i].local.L,map.vec_freeps[i].local.C);
			put_tent(&map,map.vec_freeps[i].local.L,map.vec_freeps[i].local.C);
			checks_freeps(&map.vec_freeps[i]);
			//printf("*********************\n");
			//print_map(map.matriz_map,map.L,map.C);
			//printf("*********************\n");
			//scanf("%d",&delete);
			if(backtrackingalgo2(map)) return true;
			takes_tent(&map,map.vec_freeps[i].local.L,map.vec_freeps[i].local.C);
			unchecks_freeps(&map.vec_freeps[i]);
		}
	}
			
	return false;
}








