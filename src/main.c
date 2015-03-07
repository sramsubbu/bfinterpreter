#include <argp.h>
#include <stdlib.h>
const char *argp_program_version = 
	"bfl 0.1";
const char *program_bug_address = 
	"<sramsubu@gmail.com>";

static char doc[] = 
	"bfl  --  an interpreter for the brainfuck language";

static char args_doc[] = "SRC_FILE";

static struct argp_option options[] = {
	{"compile", 'c', 0,      0, "Compiler to a .c file instead of executing"},
	{"debug",  'd', 0,     0,  "Enable debugging"},
	{0}
};

struct arguments
{
	char *src_file;
	char *output_file;
	int debug;
};

static error_t
parse_opt(int key,char *arg,struct argp_state *state)
{
	struct arguments *arguments = state->input;
	switch(key) 
	{
		case 'd':
			arguments->debug = 1; 
			break;
		case 'o':
			arguments->output_file = arg;
			break;
		case ARGP_KEY_ARG:
			if(state->arg_num > 1) //Too many arguments
				argp_usage(state);
			arguments->src_file = arg;
			break;
		case ARGP_KEY_END:
			if(state->arg_num < 1) //Not enough arguments
				argp_usage(state);
			break;
		default:
			return ARGP_ERR_UNKNOWN;

	}
	return 0;
}

static struct argp argp = {options,parse_opt,args_doc,doc};

int
main(int argc,char *argv[])
{
	struct arguments arguments;
	int ret;

	arguments.debug = 0;
	arguments.output_file = "-";
	argp_parse(&argp,argc,argv,0,0,&arguments);

	ret = interpret_file(arguments.src_file);
	if(ret == 0)
		printf("File executed successfully\n");
	else
		printf("Error(s) occured %d\n",ret);
	exit(0);
}

