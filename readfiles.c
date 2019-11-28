#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readfiles.h"
#include "solver.h"
#include "mapa.h"
#include "arvores.h"
#include "tendas.h"



/******************************************************************************
* start_read()
*
* Arguments: file - file pointer to read data from
* 			 filename - string with the filename
*     
* Returns: (void)
* Side-Effects:   
*
* Description: Reads the map dimensions and the variant associated 
*****************************************************************************/

void start_read(FILE *file,char *filename){
	
	char *exit_filename = create_file(filename); //stores the exit filename
	int L,C=0;
	char variante;
	
	while(1){
		if(fscanf(file,"%d %d %c",&L,&C,&variante)!=3) return;
		
		switch(variante){
		
		case 'A': 
			readA(file,L,C,exit_filename);
			break;
		case 'B':
			readB(file,L,C,exit_filename);			
			break;
		case 'C':
			readC(file,L,C,exit_filename);			
			break;
		default:
			write_exit_file(filename,L,C,variante,-1);			
		}
	}	
}



/******************************************************************************
* create_file()
*
* Arguments: filename - string with the filename
*     
* Returns: (char*) string with the solution file name.
* Side-Effects: Creates a file to write solutions in. 
*
* Description: Sets the solutions file name and creates the file.
*****************************************************************************/

char *create_file (char *in){
	
	char *retfile_name;
	FILE *out;
	
	retfile_name = strtok(in,".");
	strcat(retfile_name,".tents0");
	out=fopen(retfile_name,"w");
	fclose(out);
	
	return retfile_name;
}
	
/******************************************************************************
* write_exit_file()
*
* Arguments: filename - string with the exit file name.
* 			L - number of lines in the map
* 			C - number of columns in the map
* 			variante - self explanatory
* 			result - self explanatory
*     
* Returns: (void)
* Side-Effects: writes a solution in the exit file. 
*
* Description: Writes a solution in the exit file.
*****************************************************************************/	
	
	
void write_exit_file(char *filename,int L,int C,char variante,int result){
	
	FILE *aux_file=fopen(filename,"a");
	
	fprintf(aux_file,"%d %d %c %d%c%c",L,C,variante,result,'\n','\n');
	
	fclose(aux_file);
}

/******************************************************************************
* write_exit_file_B()
*
* Arguments: filename - string with the exit file name.
* 			L - number of lines in the map
* 			C - number of columns in the map
* 			result - result of the problem
* 			l0 - self explanatory
* 			c0 - self explanatory
*     
* Returns: (void)
* Side-Effects: writes a solution in the exit file. 
*
* Description: Writes a solution in the exit file.
*****************************************************************************/

void write_exit_file_B(char *filename,int L,int C,char variante,int result,int l0,int c0){
	
	FILE *aux_file=fopen(filename,"a");
	
	fprintf(aux_file,"%d %d %c %d %d %d%c%c",L,C,variante,l0,c0,result,'\n','\n');
	
	fclose(aux_file);
}

/******************************************************************************
* readA()
*
* Arguments: file - file pointer to read data from.
* 			L - number of lines in the map
* 			C - number of columns in the map
* 			exit_filename - string with the exit file name
*     
* Returns: (void)
* Side-Effects: read a portion of a file and gathers data. 
*
* Description: Gathers the data to solve a problem of variant A and calls the
* 			   the algorithm to solve it.
*****************************************************************************/

void readA(FILE *file,int L,int C,char *exit_filename){
	
	int i,j=0;
	int aux=0;
	char aux2;
	int N_tendas_por_linha=0;
	int N_tendas_por_coluna=0;
	int N_arvores=0;
	
	for(i=0;i<L;i++){		
		if(fscanf(file,"%d",&aux)!=1) return;
		N_tendas_por_linha=N_tendas_por_linha+aux;
	}
	
		
	for(i=0;i<C;i++){
		if(fscanf(file,"%d",&aux)!=1) return;
		N_tendas_por_coluna=N_tendas_por_coluna+aux;		
	}
	
	
	for(i=0;i<L;i++){
		for(j=0;j<C;j++){
			if(fscanf(file,"%c",&aux2)!=1) return;
			if(aux2==' ' || aux2=='\n'){
				j--;
			}
			if(aux2=='A') N_arvores=N_arvores+1;
		}
	}
	solve_A(exit_filename,L,C,N_arvores,N_tendas_por_coluna,N_tendas_por_linha);

}

/******************************************************************************
* readB()
*
* Arguments: file - file pointer to read data from.
* 			L - number of lines in the map
* 			C - number of columns in the map
* 			exit_filename - string with the exit file name
*     
* Returns: (void)
* Side-Effects: read a portion of a file and gathers data. 
*
* Description: Gathers the data to solve a problem of variant B and calls the
* 			   the algorithm to solve it.
*****************************************************************************/
void readB(FILE *file,int L,int C,char *exit_filename){
	
	int l0,c0=0;
	int coluna[L];
	int linha[C];
	int T_na_linha_l0=0;
	int T_na_coluna_c0=0;
	int aux=0;
	char aux2;
	int comp_linha=0;
	int comp_coluna=0;
	int T_adj_tree=0;
	int T_adj_tenda=0;
	int i,j=0;
	char variante = 'B';
		
	if(fscanf(file,"%d %d",&l0,&c0)!=2) return;
	
	if(check_l0co(l0,c0,L,C)==-1){ // takes care of outside the map coord
		readB1(file,L,C);//reads b for the sake of reading
		write_exit_file_B(exit_filename,L,C,variante,-1,l0,c0);
		return;
	}
	
	/* Weird way i found to gather enough information to solve B without spending
	 * "memory" */
	
	for(i=0;i<L;i++){	
		if(fscanf(file,"%d",&aux)!=1) return;
		if(i==l0) T_na_linha_l0=aux; 
	}
	
		
	for(i=0;i<C;i++){
		if(fscanf(file,"%d",&aux)!=1) return;
		if(i==c0) T_na_coluna_c0=aux;		
	}
	
	for(i=0;i<L;i++){
		for(j=0;j<C;j++){
			if(fscanf(file,"%c",&aux2)!=1) return;
			
			
			if(i==l0-1 && j==c0-1){
				if(aux2=='T') T_adj_tenda++;
			}
			
			if(i==l0+1 && j==c0-1){
				if(aux2=='T') T_adj_tenda++;
			}
			
			if(i==l0-1 && j==c0+1){
				if(aux2=='T') T_adj_tenda++;
			}
						
			if(i==l0+1 && j==c0+1){
				if(aux2=='T') T_adj_tenda++;
			}			
			
			if(i==l0 && j==c0-1){
				if(aux2=='T') T_adj_tenda++;
			}
			
			if(i==l0 && j==c0+1){
				if(aux2=='T') T_adj_tenda++;
			}
			
			if(i==l0-1 && j==c0){
				if(aux2=='T') T_adj_tenda++;
			}
			
			if(i==l0+1 && j==c0){
				if(aux2=='T') T_adj_tenda++;
			}
			
			if(i==l0){
				 if(aux2=='.') linha[j]=0;
				 if(aux2=='A'){
					  linha[j]=1;
					  if(j==c0-1 || j==c0+1){
						   T_adj_tree++;
					   }
				  }
				 if(aux2=='T'){
					  linha[j]=2;
					  comp_linha++;
				  }
			 }
			 if(j==c0){
				 if(aux2=='.') coluna[i]=0;
				 if(aux2=='A'){
					  coluna[i]=1;
					  if(i==l0-1 || i==l0+1){
						   T_adj_tree++;
					   }
				  }
				 if(aux2=='T'){
					  coluna[i]=2;
					  comp_coluna++;
				  }
			 }				 
			if(aux2==' ' || aux2=='\n'){
				j--;
			}
		}
	}
	
	solve_B(exit_filename,L,C,l0,c0,linha,T_adj_tree,T_adj_tenda,coluna,comp_linha,T_na_linha_l0,comp_coluna,T_na_coluna_c0);		
}
	



/******************************************************************************
* readB1()
*
* Arguments: file - file pointer to read data from.
* 			L - number of lines in the map
* 			C - number of columns in the map
*     
* Returns: (void)
* Side-Effects: Advances the pointer tracking what to read in the input file.
*
* Description: Advances the pointer from the file we are reading data from.
*****************************************************************************/

void readB1(FILE *file,int L,int C){
	int i,j=0;
	int aux=0;
	char aux2;
	
	//reads B for the sake of reading!!!
	
	for(i=0;i<L;i++){		
		if(fscanf(file,"%d",&aux)!=1) return;
	}
	
		
	for(i=0;i<C;i++){
		if(fscanf(file,"%d",&aux)!=1) return;		
	}
	
	for(i=0;i<L;i++){
		for(j=0;j<C;j++){
			if(fscanf(file,"%c",&aux2)!=1) return;
			if(aux2==' ' || aux2=='\n'){
				j--;
			}
		}
	}
}		

/******************************************************************************
* readC()
*
* Arguments: file - file pointer to read data from.
* 			L - number of lines in the map
* 			C - number of columns in the map
* 			exit_filename - string with the exit file name
*     
* Returns: (void)
* Side-Effects: read a portion of a file and gathers data, creates the map.
*
* Description: Gathers the data to solve a problem of variant C and calls the
* 			   the algorithm to solve it.
*****************************************************************************/

void readC(FILE *file,int L,int C,char *exit_filename){

	int N_T_L[L];
	int N_T_C[C];
	char strings[L+1]; 
	int i,j=0;
	char variante='C';
	char wS=' ';
	char emp='.';
	char tent='T';
	char arv='A';
	int **mapa;
	int NUMA=0;
	int NUMT=0;
	Mapa map;		
		
	for(i=0;i<L;i++)		
		if(fscanf(file,"%d",&N_T_L[i])!=1) return;
		
	for(i=0;i<C;i++)
		if(fscanf(file,"%d",&N_T_C[i])!=1) return;
		
	mapa=malloc(L*sizeof(int*));      //MOVER ISTO TALVEZ PARA UMA FUNÇÃO
	for(i=0;i<L;i++){
		mapa[i]=malloc(C*sizeof(int));
	}
	
	//strings=malloc(sizeof(char)*(L+1)); PENSO QUE JÁ NÃO SEJA NECESSÁRIO
	
	for(i=0;i<L;i++){
		for(j=0;j<C;j++){
			if(fscanf(file,"%c",&strings[i])!=1) return;
			if(strings[i]==arv){
				mapa[i][j]=1;
				NUMA=NUMA+1;
			}
			if(strings[i]==emp){
				mapa[i][j]=0;
			}				
			if(strings[i]==tent){
				mapa[i][j]=2;
				NUMT=NUMT+1;
			}			
			
			if(strings[i]==wS || strings[i]=='\n'){
				j--;
			}
		}
	}
	
	cria_mapa(&map,L,C,NUMA,NUMT,mapa);
	add_arvores(get_arvores(mapa,NUMA,L,C),&map);
	add_tendas(get_tendas(mapa,NUMT,L,C),&map);
	solve_C(exit_filename,variante,N_T_L,N_T_C,L,C,map);
	free_vec_tendas(map.vec_tendas);
	free_vec_arvores(map.vec_arvores);
	free_matriz_map(map.matriz_map,L);
}
	
