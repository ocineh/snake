#ifndef SNAKE_SNAKE_HPP
#define SNAKE_SNAKE_HPP

#include <SDL2/SDL.h>

const int WIDTH = 800;
const int HEIGHT = 800;

enum Direction{ Up, Down, Left, Right };

class SnakeCell{
public:
	SnakeCell() = delete;
	SnakeCell(const SnakeCell &snake_cell) = default;
	SnakeCell(int x, int y, Direction direction = Right, SnakeCell *prev = nullptr, SnakeCell *next = nullptr);
	
	void render(SDL_Renderer *renderer);
	void move();
	
	static const int length = 10;

private:
	void move(Direction direction) noexcept;
	
	SDL_Rect m_rect;
	Direction m_direction;
	SnakeCell *m_prev, *m_next;
};

class Snake{
public:
	Snake() = delete;
	Snake(Snake const &snake) = default;
	Snake(int x, int y, Direction direction = Right);
	
	void render(SDL_Renderer *renderer);
	
private:
	SnakeCell m_head;
};

#endif //SNAKE_SNAKE_HPP
