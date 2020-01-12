#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *
read_file(char *filename){

  char *out;
  FILE *fp;
  char ch;
  unsigned long size;

  fp = fopen(filename, "r");
  fseek(fp, 0, SEEK_END);

  size = (unsigned long)ftell(fp);
  fseek(fp, 0, SEEK_SET);

  out = (char *)malloc(sizeof(char)* (size+1));
  
  while( (ch=fgetc(fp))!=EOF)
    *out++ = ch;

  *out = '\0';
  out -= size;
  return out;
}


void process_loops(char *contents){
  char ch;
  int tracker;
  int pc;
  int i;
  int len = strlen(contents);

  tracker = 0;
  for(i=0;i<len;i++){
    ch = contents[i];
    if (ch == '['){
      // find corresponding close
      pc = i+1;
      tracker = 1;
      while(tracker != 0 || ch != ']'){
	ch = contents[pc];
	if(ch == '[') tracker +=1;
	else if (ch == ']') tracker -= 1;
       
	  printf("Tracker: %d, PC: %d,Char: %c\n",tracker,pc, ch);
	pc += 1;
      }
      printf("'[' at %d. Corresponding close: %d\n", i, pc-1); 
    }
    else if (ch == ']'){
      printf("Encountered Close: %d\n",i);
    }
    else {
    }
  }
  
}


int main(int argc, char *argv[]) {
  char *filename, *contents;
  char ch;
  int tracker;
  int pc; 
  FILE *fp;
  
  filename = argv[1];
  printf("Processing file: %s\n", filename);
  contents = read_file(filename);
  printf("%s\n", contents);
  process_loops(contents);
  return 0;
}
