#include "snake.hpp"
#include "game.hpp"

void Snake::render(SDL_Renderer *renderer) {
	move();
	for(auto &cell: m_cells) cell.render(renderer);
}

void Snake::move() {
	for(unsigned long i = m_cells.size() - 1; i > 0; --i)
		m_cells[i] = { m_cells[i - 1] };
	switch(m_direction) {
		case Up: m_cells[0].move_up();
			break;
		case Down: m_cells[0].move_down();
			break;
		case Left: m_cells[0].move_left();
			break;
		case Right: m_cells[0].move_right();
			break;
	}
}

Snake::Snake(int x, int y, Direction direction)
		: m_cells({{ x, y, color }}), m_direction(direction) {
}

void Snake::turn(Direction direction) {
	if(direction != m_direction) {
		if(direction == Up && m_direction == Down) return;
		if(direction == Down && m_direction == Up) return;
		if(direction == Left && m_direction == Right) return;
		if(direction == Right && m_direction == Left) return;
		m_direction = direction;
	}
}

void Snake::grow() {
	Pixel pixel { m_cells.back() };
	pixel.move_left();
	m_cells.push_back(pixel);
}
