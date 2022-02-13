#include <cassert>
#include <unistd.h>
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
	if(m_prev != nullptr) m_prev->render(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &m_rect);
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

void Snake::render(SDL_Renderer *renderer) {
	m_head.render(renderer);
	move();
}

void Snake::move() {
	for(auto *actual = get_tail(); actual->m_next != nullptr; actual = actual->m_next)
		actual->m_rect = { actual->m_next->m_rect };
	m_head.move(m_head.m_direction);
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

void Snake::grow() {
	auto *tail = get_tail();
	tail->m_prev = new SnakeCell { tail->m_rect.x, tail->m_rect.y + Game::length };
	tail->m_prev->m_next = tail;
}

SnakeCell *Snake::get_tail() {
	auto *actual = &m_head;
	while(actual->m_prev != nullptr)
		actual = actual->m_prev;
	return actual;
}
