#ifndef SNAKE_GAME_HPP
#define SNAKE_GAME_HPP

#include <SDL2/SDL_ttf.h>
#include <cstdlib>
#include <random>
#include "snake.hpp"

#define WIDTH 500
#define HEIGHT 500

class Game {
public:
	Game();

	void start();
	void render();
	void stop();

	constexpr static const SDL_Color food_color = { 255, 0, 0, 0 };

private:
	void handle_input();
	void place_food();
	void has_been_eaten();
	bool is_outside_window();

	bool m_is_open{ true };
	Snake *m_snake = new Snake{ Pixel::length, Pixel::length };
	Pixel *m_food{ nullptr };

	SDL_Window *m_window{ nullptr };
	SDL_Renderer *m_renderer{ nullptr };
	SDL_Event m_events{};

	std::default_random_engine m_engine{ std::random_device{}() };
	std::uniform_int_distribution<int> m_x_generator{
			1,
			(WIDTH - Pixel::length * 2) / Pixel::length
	};
	std::uniform_int_distribution<int> m_y_generator{
			1,
			(HEIGHT - Pixel::length * 2) / Pixel::length
	};
};


#endif //SNAKE_GAME_HPP
