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
 * interprets a brainfuck source file
 */
#include <stdio.h>
#include <stdlib.h>
#include <bf.h>
#define MAXSIZE 30000
#define STACKSIZE 500

int data[MAXSIZE];
int stack[STACKSIZE];
int dp = MAXSIZE/2;
int SP = -1;
long pc = 0;

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
/*	int data[MAXSIZE];
	int stack[STACKSIZE];
	int dp = MAXSIZE/2;
	int SP = -1;*/
	int i;
//	long pc=0;
	int loop_tracker;
    unsigned int local_pc;
    char temp;
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
			    if(!data[dp]) {
                      local_pc = pc+1;
                      loop_tracker = 1;
                      while (local_pc < co.length && loop_tracker > 0){
                           temp = code[local_pc];
                           if (temp == '[')
                               loop_tracker++;
                           else if(temp == ']')
                                loop_tracker--;
                           local_pc++;

                      }
                      pc = local_pc-1;
                       
			  }
              break;
			case ']':
				if (data[dp]) {
                    local_pc = pc - 1;
                    loop_tracker = 1;
                    while(local_pc > 0 && loop_tracker > 0) {
                        temp = code[local_pc];
                        if (temp == ']') loop_tracker++;
                        else if(temp == '[') loop_tracker--;
                        local_pc--;
                    }
                    pc = local_pc+1;
                }
				break;
		}
		pc++;
	}
	return 0;
}
/*
 * read the chars from the bf file and copy it to the
 * buffer for processing
 */
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
    printf("File size: %d\n",code.length);
	return code;
}
