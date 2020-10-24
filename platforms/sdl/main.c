#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "console/console.h"
#include "debugger/debugger.h"
#include "auto/config.h"


int main(void)
{
	if (CON_enable() == -1) return 1;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER))
	{
		return 2;
	}

	SDL_Window   * window;
	SDL_Renderer * renderer;
	SDL_Event      event;

	//unsigned int lastTicks  = 0;
	//unsigned int deltaTicks = 0;

	if (SDL_CreateWindowAndRenderer(
				256*CONFIG_DISPLAY_SCALE, 240*CONFIG_DISPLAY_SCALE,
				SDL_WINDOW_OPENGL, &window, &renderer))
	{
		return 3;
	}

	SDL_SetWindowPosition(window, 0, 0);

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

		if (event.type == SDL_QUIT) {
			break;
		}

		while(SDL_PollEvent(&event))
		{

			if (event.type == SDL_QUIT) {
				break;
			}

		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);

		// Draw Here

		SDL_RenderPresent(renderer);

	}


	CON_disable();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();


	return 0;
}
