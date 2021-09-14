#include <SDL2/SDL.h>

int main(){
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0){
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
		return EXIT_FAILURE;
	}
	
	SDL_Window *pWindow{ nullptr };
	SDL_Renderer *pRenderer{ nullptr };
	if(SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_SHOWN, &pWindow, &pRenderer) < 0){
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}
	SDL_SetWindowTitle(pWindow, "snake");

	SDL_Event events;
	bool isOpen{ true };
	while(isOpen){
		while(SDL_PollEvent(&events)){
			switch(events.type){
				case SDL_QUIT: isOpen = false; break;
			}
		}
	}

	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(pWindow);
	SDL_Quit();
	return EXIT_SUCCESS;
}