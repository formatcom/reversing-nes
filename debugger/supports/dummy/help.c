#include <stdio.h>
#include "debugger/debugger.h"

int help(void * core,
				char *arguments,
				char *modifiers, const debugger_command_t *ignored)
{

	printf("call help");
	return 0;
}
