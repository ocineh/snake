#ifndef SNAKE_GAME_HPP
#define SNAKE_GAME_HPP

#include "Snake.hpp"

class Game {
public:
	Game();
	
	void start();
	
	void stop();
	
	static const int length = 10;

private:
	void handle_input();
	
	bool m_is_open { true };
	Snake *m_snake = new Snake { 10, 10 };
	SDL_Window *m_window { nullptr };
	SDL_Renderer *m_renderer { nullptr };
	SDL_Event m_events {};
};


#endif //SNAKE_GAME_HPP
