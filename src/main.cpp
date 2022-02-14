#include <atomic>
#include "snake.hpp"
#include "game.hpp"

int main() {
	Game game {};
	game.start();
	game.stop();
	return EXIT_SUCCESS;
}
