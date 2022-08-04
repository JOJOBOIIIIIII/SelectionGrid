#pragma once
#include "Game.h"

struct Tile {
	SDL_Rect rect = {0,0,32,32};
	bool glow=false;
};


template<int C, int R>
struct SelectionGrid {

	int columns;
	int rows;
	int xPos;
	int yPos;


	Tile grid[C][R]; //2d array of tiles

	SelectionGrid(int x,int y) {
		columns = C;
		rows = R;
		xPos = x;
		yPos = y;
	};

	~SelectionGrid() {};

	void update() {
		for (int r = 0;r < R;r++) {
			for (int c = 0;c < C;c++) {
				grid[c][r].rect.x = xPos + c * 40;
				grid[c][r].rect.y = yPos + r * 40;
			}
		}
	};

	void render(SDL_Renderer* ren) {
		//std::cout << "HI!" << std::endl;

		for (int r = 0;r < R;r++) {
			for (int c = 0;c < C;c++) { 

				auto tile = grid[c][r];

				if (tile.glow) { SDL_SetRenderDrawColor(ren, 240, 240, 0, 255); } //becomes yellow
				else SDL_SetRenderDrawColor(ren, 0, 0, 0, 255); 
				SDL_RenderDrawRect(ren, &tile.rect);

				//std::cout << SDL_GetError() << std::endl;
			}
		}
	
	
	};
};



