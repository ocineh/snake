#include "game.hpp"

Game::Game() {
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	if(SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN, &m_window, &m_renderer) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
		SDL_Quit();
		exit(EXIT_FAILURE);
	}
	SDL_SetWindowTitle(m_window, "snake");
	if(TTF_Init() != 0) {
		SDL_Log("Error: TTF_Init");
		SDL_Quit();
		return;
	}
}

void Game::handle_input() {
	while(SDL_PollEvent(&m_events)) {
		switch(m_events.type) {
			case SDL_QUIT: m_is_open = false;
				break;
			case SDL_KEYDOWN:
				switch(m_events.key.keysym.scancode) {
					case SDL_SCANCODE_W:
					case SDL_SCANCODE_UP: m_snake->turn(Up);
						break;
					case SDL_SCANCODE_S:
					case SDL_SCANCODE_DOWN: m_snake->turn(Down);
						break;
					case SDL_SCANCODE_A:
					case SDL_SCANCODE_LEFT: m_snake->turn(Left);
						break;
					case SDL_SCANCODE_D:
					case SDL_SCANCODE_RIGHT: m_snake->turn(Right);
						break;
					default: break;
				}
				break;
		}
	}
}

void Game::start() {
	bool is_alive { true };
	while(m_is_open) {
		handle_input();
		if(is_alive) {
			has_been_eaten();
			render();
			if(is_outside_window()) {
				is_alive = false;
				TTF_Font *font = TTF_OpenFont("../fonts/font.ttf", 50);
				SDL_Surface *surface = TTF_RenderText_Solid(font, "GAME OVER", { 255, 255, 255, 255 });
				SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, surface);
				SDL_Rect position { (WIDTH - surface->w) >> 1, (HEIGHT - surface->h) >> 1, surface->w, surface->h };
				
				SDL_SetRenderDrawColor(m_renderer, 50, 50, 50, 255);
				SDL_RenderClear(m_renderer);
				SDL_RenderCopy(m_renderer, texture, nullptr, &position);
				SDL_RenderPresent(m_renderer);
				
				TTF_CloseFont(font);
				SDL_FreeSurface(surface);
			}
		}
		SDL_Delay(50);
	}
}

void Game::render() {
	SDL_SetRenderDrawColor(m_renderer, 50, 50, 50, 255);
	SDL_RenderClear(m_renderer);
	m_snake->render(m_renderer);
	if(m_food != nullptr) m_food->render(m_renderer);
	SDL_RenderPresent(m_renderer);
}

void Game::stop() {
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	TTF_Quit();
	SDL_Quit();
}

void Game::place_food() {
	m_food = new Food { m_x_generator(m_engine) * Game::length, m_y_generator(m_engine) * Game::length };
}

void Game::has_been_eaten() {
	if(m_food == nullptr) place_food();
	if(are_they_colliding(&m_snake->m_cells.front(), &m_food->m_rect)) {
		m_food = nullptr;
		m_snake->grow();
	}
}

bool Game::is_outside_window() {
	auto *head = &m_snake->m_cells.front();
	return !(head->x >= 0 && head->x <= (WIDTH - length) && head->y >= 0 && head->y <= (HEIGHT - length));
}

bool are_they_colliding(SDL_Rect *rect_1, SDL_Rect *rect_2) {
	SDL_Rect intersection {};
	SDL_IntersectRect(rect_1, rect_2, &intersection);
	return intersection.w > 0 && intersection.h > 0;
}

Food::Food(int x, int y): m_rect({ x, y, 10, 10 }) {
}
