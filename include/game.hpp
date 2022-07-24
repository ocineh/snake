#ifndef SNAKE_GAME_HPP
#define SNAKE_GAME_HPP

#include <SDL2/SDL_ttf.h>
#include <cstdlib>
#include <random>
#include "snake.hpp"

#define WIDTH 500
#define HEIGHT 500

class Game;

class Food {
public:
	Food() = delete;
	Food(int x, int y);
	
	void render(SDL_Renderer *renderer) {
		m_pixel.render(renderer);
	}

	constexpr static const SDL_Color color = { 255, 0, 0, 0 };
	friend Game;
private:
	Pixel m_pixel;
};

class Game {
public:
	Game();
	
	void start();
	void render();
	void stop();

private:
	void handle_input();
	void place_food();
	void has_been_eaten();
	bool is_outside_window();
	
	bool m_is_open { true };
	Snake *m_snake = new Snake { Pixel::length, Pixel::length };
	Food *m_food { nullptr };
	
	SDL_Window *m_window { nullptr };
	SDL_Renderer *m_renderer { nullptr };
	SDL_Event m_events {};
	
	std::default_random_engine m_engine { std::random_device {}() };
	std::uniform_int_distribution<int> m_x_generator { 0, (WIDTH - Pixel::length) / Pixel::length };
	std::uniform_int_distribution<int> m_y_generator { 0, (HEIGHT - Pixel::length) / Pixel::length };
};


#endif //SNAKE_GAME_HPP
