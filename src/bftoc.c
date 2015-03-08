/*
 * compiles a bf file to a c file.
 */
#include <stdio.h>
#include <stdlib.h>
#include <bf.h>
#define MAXSIZE 400

static FILE *
init_outfile(const char *outpath)
{
	FILE *fp = fopen(outpath,"w");
	fprintf(fp,"int\nmain()\n{\n");
	fprintf(fp,"char arr[%d];\n",MAXSIZE);
	fprintf(fp,"int dp = %d/2;\n",MAXSIZE);
	return fp;
}

static int
close_outfile(FILE *outfile)
{
	fprintf(outfile,"return 0;\n}\n\n");
	fclose(outfile);
	return 0;
}

int 
bftoc(code_t code,const char *output)
{
	int i;
	//Initialise the c file
	FILE *outfile = init_outfile(output);
	if(outfile == NULL) {
		printf("Cannot open file\n");
		exit(1);
	}
	for(i=0;i<code.length;i++) {
		switch(code.code[i]) {
			case '<':
				fprintf(outfile,"dp--;\n");
				break;
			case '>':
				fprintf(outfile,"dp++;\n");
				break;
			case '+':
				fprintf(outfile,"arr[dp]++;\n");
				break;
			case '-':
				fprintf(outfile,"arr[dp]--;\n");
				break;
			case '.':
				fprintf(outfile,"putchar( arr[dp] );\n");
				break;
			case ',':
				fprintf(outfile,"arr[dp] = getchar();\n");
				break;
			case '[':
				fprintf(outfile," while( arr[dp] ) { \n");
				break;
			case ']':
				fprintf(outfile, " }\n");
				break;

		}
	}
	close_outfile(outfile);
	return 0;
}
