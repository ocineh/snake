#include <atomic>
#include "Snake.hpp"

int main(){
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0){
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
		return EXIT_FAILURE;
	}
	
	SDL_Window *pWindow{ nullptr };
	SDL_Renderer *pRenderer{ nullptr };
	if(SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN, &pWindow, &pRenderer) < 0){
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}
	SDL_SetWindowTitle(pWindow, "snake");

	SDL_Event events;
	bool isOpen{ true };
	Snake snake{10,10};
	while(isOpen){
		while(SDL_PollEvent(&events)){
			switch(events.type){
				case SDL_QUIT: isOpen = false; break;
				case SDL_KEYDOWN:
					SDL_Log("+key");
					switch(events.key.keysym.scancode){
						case SDL_SCANCODE_W: snake.turn(Up); break;
						case SDL_SCANCODE_A: snake.turn(Left); break;
						case SDL_SCANCODE_S: snake.turn(Down); break;
						case SDL_SCANCODE_D: snake.turn(Right); break;
						default: break;
					}
					break;
				case SDL_KEYUP: SDL_Log("-key"); break;
			}
		}
		
		SDL_SetRenderDrawColor(pRenderer, 50, 50, 50, 255);
		SDL_RenderClear(pRenderer);
		
		snake.render(pRenderer);
		
		SDL_RenderPresent(pRenderer);
		SDL_Delay(500);
	}

	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(pWindow);
	SDL_Quit();
	return EXIT_SUCCESS;
}