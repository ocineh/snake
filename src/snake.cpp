#include "snake.hpp"
#include "game.hpp"

void Snake::render(SDL_Renderer *renderer) {
	move();
	for(auto &cell: m_cells) {
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		SDL_RenderFillRect(renderer, &cell);
	}
}

void Snake::move() {
	for(unsigned long i = m_cells.size() - 1; i > 0; --i)
		m_cells[i] = { m_cells[i - 1] };
	switch(m_direction) {
		case Up: m_cells[0].y -= Game::length;
			break;
		case Down: m_cells[0].y += Game::length;
			break;
		case Left: m_cells[0].x -= Game::length;
			break;
		case Right: m_cells[0].x += Game::length;
			break;
	}
}

Snake::Snake(int x, int y, Direction direction)
	: m_cells({{ x, y, Game::length, Game::length }}), m_direction(direction) {
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
	auto *end = &m_cells.back();
	m_cells.push_back({ end->x, end->y + Game::length });
}