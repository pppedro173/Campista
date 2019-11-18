#include <stdio.h>
#include <stdlib.h>
#include "solver.h"
#include "readfiles.h"




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
* aolve_B()
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
	

