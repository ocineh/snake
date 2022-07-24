#ifndef SNAKE_SNAKE_HPP
#define SNAKE_SNAKE_HPP

#include <SDL2/SDL.h>
#include <utility>
#include <vector>
#include <deque>
#include "pixel.hpp"

class Game;

enum Direction { Up, Down, Left, Right };

class Snake {
public:
	Snake() = delete;
	Snake(Snake const &snake) = default;
	Snake(int x, int y, Direction direction = Right);

	void render(SDL_Renderer *renderer);
	void move();
	void turn(Direction direction);
	void grow();

	constexpr static const SDL_Color color = { 0, 255, 0, 0 };
	friend Game;
private:
	Direction m_direction;
	std::deque<Pixel> m_cells {};
};

#endif //SNAKE_SNAKE_HPP
