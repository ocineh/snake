#ifndef SNAKE_SNAKE_HPP
#define SNAKE_SNAKE_HPP

#include <SDL2/SDL.h>
#include <utility>
#include <vector>
#include <deque>

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
private:
	Direction m_direction;
	std::deque<SDL_Rect> m_cells {};
};

#endif //SNAKE_SNAKE_HPP
