
#include "game.h"
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;
int FPS;
int cnt;

Game game;

int main (int argc, char* argv[]) {

	if (game.init("Hello", 800, 640, 0)) game.isRunning = true; 
	else std::cout << "Initialization failed." << std::endl;

	
	while (game.isRunning) {
		
		
		auto t1 = Clock::now();

		game.handleEvents();
		game.update();
		game.render();

		auto t2 = Clock::now();
		
		/*
		std::cout << "Delta t2-t1: "
			<< std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()
			<< " nanoseconds" << std::endl;
		*/

		FPS = 1000000000 / std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();

		cnt++;
		if (cnt > 1000) {
			std::cout << FPS << " FPS" << std::endl;
			cnt = 0;
		}
	
	}

	game.clean();

	return 0;
}