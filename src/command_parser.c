#include "command_parser.h"
#include "string.h"
#include <stdint.h>
#include "malloc.h"

static void clean_command(char * cmd)
{
	int i = 0;
	while (cmd[i] != '\n')
	{
		i++;
	}
	cmd[i] = '\0';

}

static char* find_next_delim(char* str, char* delim)
{
	char* next_space = strfnd(str, ' ');
	char* next_double_quotes = strfnd(str, '"');
	char* next_null_terminator = strfnd(str+1, '\0');
	
	char* res = next_space < next_double_quotes ? next_space : next_double_quotes;
	res = res < next_null_terminator ? res : next_null_terminator;
	
	*delim = *res;
	
	return res;
}

char** parse_command(char* cmd, int* argc)
{
	clean_command(cmd);
	
	char* end_pos = strtok(cmd, '\0');
	char delim;
	char* delim_addr = find_next_delim(cmd, &delim);
	
	char** args = (char**) gmalloc(sizeof(char*));
	args[0] = cmd;

	uint32_t counter = 1;
	char* next_delim_addr;
	while (delim_addr < end_pos)
	{
		*delim_addr = '\0';
		
		// Find next delim
		if (delim == '"')
		{
			next_delim_addr = strtok(delim_addr, delim);
			delim = ' ';
		}
		else
		{
			next_delim_addr = find_next_delim(delim_addr, &delim);
			*next_delim_addr = '\0';
		}

		if (delim_addr+1 != next_delim_addr) // the two delimiters are not one after another, a word has been found
		{
			args = (char**) grealloc(args, sizeof(char*) * (counter++));
			args[counter-1] = delim_addr+1;
		}
		
		delim_addr = next_delim_addr;
	}
	
	*argc = counter;

	return args;
}

int str_to_int(char* str)
{
	int res = 0;
	int sign = 1;
	int i = 0;
	
	if (str[0] == '-')
	{
		sign = -1;
		++i;
	}
	
	for (; str[i] != '\0'; ++i)
		res = res*10 + str[i] - '0';
		
	return sign*res;
}
