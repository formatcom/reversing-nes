#include <stdio.h>
#include <string.h>
#include "debugger/debugger.h"


void debugger_execute_command(void * core, char * input)
{
	char * command_string = input;
	char * arguments      = strchr(input, ' ');

	if (arguments)
	{
		arguments[0] = 0; // split command
		arguments++;      // arguments
	}
	else
	{
		arguments = "";   // only command
	}

	printf(" [%s][%s] ", command_string, arguments);
}
