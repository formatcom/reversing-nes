#include <stdio.h>
#include "debugger/debugger.h"

int help(void * core,
				char *arguments,
				char *modifiers, const debugger_command_t *ignored);

debugger_command_t commands[] = {
	{"help", 1, help, "List available commands or show help for the specified command", "[<command>]"},
	{NULL,}, /* Null terminator */
};
