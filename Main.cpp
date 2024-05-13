#include "Global.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
//#if defined(__MINGW32__)
# define SDL_MAIN_HANDLED
//#endif /* !defined(__MINGW32__) */
extern "C" {
# include "SDL.h"
# include "SDL_main.h"
}
#include "Scene.h"



#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char **argv) {
	SDL_Window *window;
	SDL_Renderer *renderer;
	bool quit = false;
	int result = 0;

	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return 1;
	}

	//if(SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer) != 0) {
	if(SDL_CreateWindowAndRenderer(GLOBAL_WINDOW_WIDTH, GLOBAL_WINDOW_HEIGHT, 0, &window, &renderer) != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return 1;
	};
	
	SDL_SetWindowTitle(window, GLOBAL_PREFIX_FILENAME);
	//SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	//SDL_RenderSetLogicalSize(renderer, GLOBAL_WINDOW_WIDTH,GLOBAL_WINDOW_HEIGHT);
	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_ShowCursor(SDL_DISABLE);

	result = Scene::initialize(renderer);

	int finalfps = 0;
	int fpstimercont = 0;
	int fpscont = 0;
	uint32_t ticksPrev = SDL_GetTicks();

	while(!quit && (result >= 0)) {
		uint32_t ticks = SDL_GetTicks();
		float periodInSekunds = (ticks - ticksPrev) * 0.001f;
		fpstimercont += (ticks - ticksPrev);
		ticksPrev = ticks;
		fpscont++;

		if(fpstimercont > 1000) {
			fpstimercont = fpstimercont - 1000;
			finalfps = fpscont;
			fpscont = 0;
		}

		SDL_RenderClear(renderer);
		quit = Scene::render(renderer, periodInSekunds, finalfps);
		SDL_RenderPresent(renderer);
	};

	Scene::deinitialize();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
};
