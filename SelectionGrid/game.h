#pragma once

#include "SDL.h"
#include <iostream>
#include "SDL_image.h"
#include "selectionGrid.h"


struct Game {
	
	bool isRunning = false;

	Game();
	~Game();

	int init(const char* title, int w, int h, bool fullscreen);

	void handleEvents();
	void update();
	void render();

	void clean();

};