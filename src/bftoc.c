/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
