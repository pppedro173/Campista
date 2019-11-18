#ifndef __readfiles__
#define __readfiles__

void start_read(FILE *file,char *filename);

char *create_file (char *in);

void write_exit_file(char *filename,int L,int C,char variante,int result);

void write_exit_file_B(char *filename,int L,int C,char variante,int result,int l0,int c0);

void readA(FILE *file,int L,int C,char *exit_filename);

void readB(FILE *file,int L,int C,char *exit_filename);

void readB1(FILE *file,int L,int C);

void readC(FILE *file,int L,int C,char *exit_filename);



#endif    /* __readfiles__ */



