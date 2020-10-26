#include <stdio.h>
#include <string.h>
#include "debugger/debugger.h"

extern debugger_command_t commands;


debugger_command_t * find_command(const char *string)
{

	debugger_command_t * command = &commands;

	size_t length = strlen(string);

	for (;command->command; command++)
	{

		if (command->min_length > length) continue;

		if (strncmp(command->command, string, length) == 0)
		{
			return command;
		}
	}

    return NULL;
}

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

	char * modifiers      = strchr(input, '/');

	if (modifiers)
	{
		modifiers[0] = 0; // split command
		modifiers++;      // modifiers
	}

	debugger_command_t * command = find_command(command_string);

	if (command)
	{
		command->implementation(core, arguments, modifiers, command);
	}
}
