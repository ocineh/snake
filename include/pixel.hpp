#ifndef SNAKE_PIXEL_HPP
#define SNAKE_PIXEL_HPP

#include <SDL.h>

class Pixel {
public:
	Pixel() = delete;
	Pixel(int x, int y, SDL_Color color);
	Pixel(Pixel const &pixel) = default;

	void render(SDL_Renderer *renderer);

	void move_left();
	void move_right();
	void move_up();
	void move_down();

	[[nodiscard]] bool is_colliding(Pixel &pixel);
	[[nodiscard]] bool is_outside_window(int width, int height) const;

	static const int length = 10;
private:
	SDL_Rect m_rect;
	SDL_Color m_color;
};

#endif //SNAKE_PIXEL_HPP
