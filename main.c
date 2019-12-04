#include <stdio.h>
#include <stdlib.h>
#include "readfiles.h"

int main(int argc,char *argv[]){
	
	FILE *file;


	if (argc < 2) exit(0); // Not enough input arguments
	
	file=fopen(argv[1],"r"); // Opens file in read mode
	if(!file)exit(0);       
	
	//start_read(file,argv[1]);
	
	start_readfinal(file,argv[1]);
	
	fclose(file);
	
	exit(0);
}
	
	
	
