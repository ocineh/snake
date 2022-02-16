#ifndef SNAKE_GAME_HPP
#define SNAKE_GAME_HPP

#include<cstdlib>
#include <random>
#include "snake.hpp"

#define WIDTH 800
#define HEIGHT 800

bool are_they_colliding(SDL_Rect *rect_1, SDL_Rect *rect_2);

class Food {
public:
	Food() = delete;
	Food(int x, int y);
	
	void render(SDL_Renderer *renderer) {
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, &m_rect);
	}
private:
	SDL_Rect m_rect;
};

class Game {
public:
	Game();
	
	void start();
	void render();
	void stop();
	
	static const int length = 10;

private:
	void handle_input();
	void place_food();
	
	bool m_is_open { true };
	Snake *m_snake = new Snake { 10, 10 };
	Food *m_food;
	
	SDL_Window *m_window { nullptr };
	SDL_Renderer *m_renderer { nullptr };
	SDL_Event m_events {};
	
	std::default_random_engine m_engine { std::random_device {}() };
	std::uniform_int_distribution<int> m_x_generator { 0, WIDTH };
	std::uniform_int_distribution<int> m_y_generator { 0, HEIGHT };
};


#endif //SNAKE_GAME_HPP
