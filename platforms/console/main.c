#include <stdio.h>
#include <string.h>
#include "console/console.h"
#include "debugger/debugger.h"
#include "auto/config.h"


int main(void)
{
	if (CON_enable() == -1) return 1;

	CON_clean();

	char * buf;

	while(1)
	{

		CON_update();

		buf = CON_capture();

		if (buf)
		{
			if (strncmp(buf, "exit", 4) == 0)
			{
				printf("bye\n\r");
				break;
			}

			debugger_execute_command(NULL, buf);
		}

	}

	CON_disable();

	return 0;
}
