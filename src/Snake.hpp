#ifndef SNAKE_SNAKE_HPP
#define SNAKE_SNAKE_HPP

#include <SDL2/SDL.h>
#include <utility>

enum Direction { Up, Down, Left, Right };

class Snake;

class SnakeCell {
public:
	SnakeCell() = delete;
	SnakeCell(const SnakeCell &snake_cell) = default;
	SnakeCell(int x, int y, Direction direction = Right, SnakeCell *prev = nullptr, SnakeCell *next = nullptr);
	
	void render(SDL_Renderer *renderer);
	void move();
	void turn(Direction direction);
	
	std::pair<int, int> get_position();
	
	friend Snake;

private:
	void move(Direction direction) noexcept;
	
	SDL_Rect m_rect;
	Direction m_direction;
	SnakeCell *m_prev, *m_next;
};

class Snake {
public:
	Snake() = delete;
	Snake(Snake const &snake) = default;
	Snake(int x, int y, Direction direction = Right);
	
	void render(SDL_Renderer *renderer);
	void move();
	void turn(Direction direction);
	void grow();
	
	std::pair<int, int> get_head_position();
private:
	SnakeCell *get_tail();
	
	SnakeCell m_head;
};

#endif //SNAKE_SNAKE_HPP
