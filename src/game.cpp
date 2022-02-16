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
}

void Game::handle_input() {
	while(SDL_PollEvent(&m_events)) {
		switch(m_events.type) {
			case SDL_QUIT: m_is_open = false;
				break;
			case SDL_KEYDOWN: SDL_Log("+key");
				if(m_events.key.keysym.scancode == SDL_SCANCODE_W || m_events.key.keysym.scancode == SDL_SCANCODE_UP)
					m_snake->turn(Up);
				else if(m_events.key.keysym.scancode == SDL_SCANCODE_S ||
						m_events.key.keysym.scancode == SDL_SCANCODE_DOWN)
					m_snake->turn(Down);
				else if(m_events.key.keysym.scancode == SDL_SCANCODE_A ||
						m_events.key.keysym.scancode == SDL_SCANCODE_LEFT)
					m_snake->turn(Left);
				else if(m_events.key.keysym.scancode == SDL_SCANCODE_D ||
						m_events.key.keysym.scancode == SDL_SCANCODE_RIGHT)
					m_snake->turn(Right);
				break;
			case SDL_KEYUP: SDL_Log("-key");
				break;
			default: break;
		}
	}
}

void Game::start() {
	while(m_is_open) {
		handle_input();
		has_been_eaten();
		render();
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

bool are_they_colliding(SDL_Rect *rect_1, SDL_Rect *rect_2) {
	SDL_Rect intersection {};
	SDL_IntersectRect(rect_1, rect_2, &intersection);
	return intersection.w > 0 && intersection.h > 0;
}

Food::Food(int x, int y): m_rect({ x, y, 10, 10 }) {
}
