#include "pixel.hpp"

Pixel::Pixel(int x, int y, SDL_Color color)
		: m_rect({ x, y, length, length }), m_color(color) {
}

void Pixel::render(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, m_color.a);
	SDL_RenderFillRect(renderer, &m_rect);
}

void Pixel::move_left() {
	m_rect.x -= length;
}

void Pixel::move_right() {
	m_rect.x += length;
}

void Pixel::move_up() {
	m_rect.y -= length;
}

void Pixel::move_down() {
	m_rect.y += length;
}

bool Pixel::is_colliding(Pixel &pixel) {
	SDL_Rect intersection {};
	SDL_IntersectRect(&m_rect, &pixel.m_rect, &intersection);
	return intersection.w > 0 && intersection.h > 0;
}

bool Pixel::is_outside_window(int width, int height) const {
	return m_rect.x < 0 || m_rect.y < 0 || m_rect.x + length > width || m_rect.y + length > height;
}
