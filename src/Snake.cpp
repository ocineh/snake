#include <cassert>
#include "Snake.hpp"
#include "game.hpp"

void SnakeCell::move(Direction direction) noexcept{
	switch(direction){
		case Up: m_rect.y -= Game::length; break;
		case Down: m_rect.y += Game::length; break;
		case Left: m_rect.x -= Game::length; break;
		case Right: m_rect.x += Game::length; break;
	}
}

void SnakeCell::render(SDL_Renderer *renderer){
	if(m_next != nullptr) m_next->render(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &m_rect);
}

void SnakeCell::move(){
	if(m_next != nullptr) m_next->move();
	if(m_prev != nullptr) m_rect = m_prev->m_rect;
	else{
		if(m_direction == Up && m_rect.y <= 0) m_direction = Right;
		else if(m_direction == Left && m_rect.x <= 0) m_direction = Up;
		else if(m_direction == Right && m_rect.x + Game::length >= WIDTH) m_direction = Down;
		else if(m_direction == Down && m_rect.y + Game::length >= HEIGHT) m_direction = Left;
		this->move(m_direction);
	}
}

SnakeCell::SnakeCell(int x, int y, Direction direction, SnakeCell *prev, SnakeCell *next)
	: m_rect({ x, y, Game::length, Game::length }), m_direction(direction), m_prev(prev), m_next(next){
	assert(x >= 0 && y >= 0 && x + Game::length <= WIDTH && y + Game::length <= HEIGHT && "Coordinated outside the window");
}

void SnakeCell::turn(Direction direction){
	if(direction != m_direction){
		if(direction == Up && m_direction == Down) return;
		if(direction == Down && m_direction == Up) return;
		if(direction == Left && m_direction == Right) return;
		if(direction == Right && m_direction == Left) return;
		m_direction = direction;
	}
}

std::pair<int, int> SnakeCell::get_position() {
	return {m_rect.x, m_rect.y };
}

void Snake::render(SDL_Renderer *renderer){
	m_head.render(renderer);
	m_head.move();
}

Snake::Snake(int x, int y, Direction direction)
	: m_head({ x, y, direction }){
}

void Snake::turn(Direction direction){
	m_head.turn(direction);
}

std::pair<int, int> Snake::get_head_position() {
	return m_head.get_position();
}
