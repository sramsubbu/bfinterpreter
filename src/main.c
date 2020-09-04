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

#include <argp.h>
#include <stdlib.h>
#include <bf.h>

const char *argp_program_version = 
	"bfl 0.2";
const char *program_bug_address = 
	"<sramsubu@gmail.com>";

static char doc[] = 
	"bfl  --  an interpreter for the brainfuck language";

static char args_doc[] = "SRC_FILE";

static struct argp_option options[] = {
	{"output",  'o', "FILE", 0, "Output file to be used while compiling"},
	{"compile", 'c', 0,      0, "Compiler to a .c file instead of executing"},
	{"debug",   'd', 0,      0,  "Enable debugging"},
	{0}
};

struct arguments
{
	char *src_file;
	int compile;
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
		case 'c':
			arguments->compile = 1;
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
	code_t code;

	arguments.debug = 0;
	arguments.output_file = "tmp.c";
	arguments.compile = 0;
	argp_parse(&argp,argc,argv,0,0,&arguments);

	code = read_file(arguments.src_file);
	if(arguments.compile)
		ret = bftoc(code,arguments.output_file);
	else
		ret  = interpret_file(code);
	exit(ret);
}

