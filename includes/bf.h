#ifndef BF_H_
#define BF_H_

struct src
{
	unsigned long length;
	char *code;
};

typedef struct src code_t;

int bftoc(code_t code,const char *output);
int interpret_file(code_t code);
code_t read_file(const char *infile);

#endif
