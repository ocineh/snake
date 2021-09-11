#include <SDL2/SDL.h>

int main(){
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] %s", SDL_GetError());
		return  EXIT_FAILURE ;
	}
	
	SDL_Quit();
	return EXIT_SUCCESS;
}