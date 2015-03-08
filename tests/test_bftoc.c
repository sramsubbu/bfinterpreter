#include <bf.h>

int 
main(int argc,char *argv[])
{
	int ret;
	code_t code = read_file(argv[1]);
	ret = bftoc(code,"tmp.c");
	return ret;
}
