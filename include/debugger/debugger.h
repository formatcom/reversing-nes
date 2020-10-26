#ifndef _MODULE_DEBUGGER_H_
#define _MODULE_DEBUGGER_H_

#include <stdint.h>

struct debugger_command_s;
typedef int debugger_command_imp_t(void *core,
									char *arguments,
									char *modifiers,
									const struct debugger_command_s *command);

typedef char * debugger_completer_imp_t(void *core,
										const char *string,
										void * context);

typedef struct debugger_command_s {
	const char                * command;
	uint8_t                     min_length;
	debugger_command_imp_t    * implementation;
	const char                * help_string;       // Null if should not appear in help
	const char                * arguments_format;  // For usage message
	const char                * modifiers_format;  // For usage message
	debugger_completer_imp_t  * argument_completer;
	debugger_completer_imp_t  * modifiers_completer;
} debugger_command_t;

void debugger_execute_command(void * core, char * input);

#endif
