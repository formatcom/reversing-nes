#include <SDL2/SDL.h>
#include "auto/config.h"


int main(void)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER))
	{
		return 1;
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
		return 2;
	}

	while(1)
	{
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

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();


	return 0;
}
