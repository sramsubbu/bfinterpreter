#include <stdio.h>
#include <stdlib.h>
#include <bf.h>
#define MAXSIZE 1000
#define STACKSIZE 500

int 
interpret_file(code_t co)
{
	/*
	 *No error handling has been done. 
	 *If the program contains some unexpected characters the compiler will
	 * just ignore them. Which is what the "specs" say. 
	 * This includes whitespaces and newlines. 
	 * This can be used as a powerful feature of the language to add comments wherever necessary :P
	 */
	int data[MAXSIZE];
	int stack[STACKSIZE];
	int dp = MAXSIZE/2;
	int SP = -1;
	int i;
	long pc=0;
	char *code = co.code;

	for(i=0;i<MAXSIZE;i++)
		data[i] = 0;
	
	int c;
	while( code[pc] != '\0')
	{
		c = code[pc];
		switch(c){
			case '+':
				(data[dp])++;
				break;
			case '-':
				(data[dp])--;
				break;
			case '<':
				dp--;
				break;
			case '>':
				dp++;
				break;
			case '.':
				putchar(data[dp]);
				break;
			case ',':
				data[dp] = getchar();
				break;
			case '[':
				if (!data[dp])
					while(c!=']')
						c = code[pc++];
				else
					stack[++SP] =pc;
				break;
			case ']':
				if ( data[dp])
					pc = stack[SP];
				else
					SP--;
				break;
		}
		pc++;
	}
	return 0;
}

code_t
read_file(const char *filename)
{	
	FILE *fp;
	fp = fopen(filename,"r");
	code_t code;

	//number of chars in the file
	fseek(fp,0,SEEK_END);
	code.length = (unsigned long)ftell(fp);
	fseek(fp,0,SEEK_SET);

	code.code = (char *)malloc(sizeof(char)*(code.length+1));
	int c;
	while( (c=fgetc(fp))!=EOF)
		*(code.code)++ = c;
	*(code.code)='\0';
	code.code -= code.length;
	return code;
//	interpreter(code);
//	return 0;
}
