#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 1000
#define STACKSIZE 500

int 
interpreter(char *code)
{
	int data[MAXSIZE];
	int stack[STACKSIZE];
	int dp = MAXSIZE/2;
	int SP = -1;
	int i;
	long pc=0;

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
}

int 
main(int argc,char *argv[])
{
	if(argc != 2){
		fprintf(stderr,"Filename required.\n");
		return 1;
	}
	FILE *fp;
	fp = fopen(argv[1],"r");
	char *code;
	unsigned long len;
	fseek(fp,0,SEEK_END);
	len = (unsigned long)ftell(fp);
	fseek(fp,0,SEEK_SET);
	code = (char *)malloc(sizeof(char)*(len+1));
	int c;
	while( (c=fgetc(fp))!=EOF)
		*code++ = c;
	*code='\0';
	code -= len;
	interpreter(code);
	return 0;
}
