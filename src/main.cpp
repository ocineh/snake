#include <atomic>
#include "Snake.hpp"
#include "game.hpp"

int main() {
	Game game {};
	game.start();
	game.stop();
	return EXIT_SUCCESS;
}
