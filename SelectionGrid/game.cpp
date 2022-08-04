#include "game.h"

SDL_Window* window;
SDL_Renderer* renderer;

//SelectionGrid<10,10>* grid = new SelectionGrid<10, 10>(0,0);     //long and repetitive

auto Grid = new SelectionGrid<14, 12>(0, 0); //This is way cleaner with the auto key word!  <columns, rows>(positionX,positionY)

struct coord {
	int x;
	int y;
};

coord coord1 = { 0,0 };
coord coord2 = { 0,0 };
bool Lpressed = false;
SDL_Rect mouseRect= {0, 0, 0, 0};
// :: means in the scope of the struct/class

Game::Game() {}; //constructor
Game::~Game() {}; //deconstructor


int Game::init(const char* title, int w, int h, bool fullscreen) {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,w,h, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 120, 0, 200, 255); //Also the color of renderClear()

	//Center the whole gride
	Grid->xPos = (w/2) - Grid->columns*40/2;  //Ideally 40 would be a parameter (it is used in selectionGrid.update())
	Grid->yPos = (h/2) - Grid->rows*40/2;

	return true;
};

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	case SDL_MOUSEBUTTONDOWN: 
		switch (event.button.button) { //get which mouse button
			
			case SDL_BUTTON_LEFT: 
				std::cout << "-----pressed-----" << std::endl;
				coord1 = { event.button.x,event.button.y };
				mouseRect.x = coord1.x;
				mouseRect.y = coord1.x;
				Lpressed = true;
				break;
			
			default:
				break;
		}
	
	case SDL_MOUSEMOTION:
		if (Lpressed) {
			coord2 = { event.button.x,event.button.y };
			int smallestX = coord1.x;
			int biggestX = coord2.x;
			int smallestY = coord1.y;
			int biggestY = coord2.y;

			mouseRect = {smallestX,smallestY,biggestX-smallestX,biggestY-smallestY};

			if (coord2.x - coord1.x < 0) {smallestX = coord2.x; biggestX = coord1.x;}
			if (coord2.y - coord1.y < 0) { smallestY = coord2.y; biggestY = coord1.y; }


			for (int r = 0;r < Grid->rows;r++) {
				for (int c = 0;c < Grid->columns;c++) {
					auto t = Grid->grid[c][r];
					if (smallestX < t.rect.x +t.rect.w
						&& biggestX >t.rect.x//+t.rect.w
						&& smallestY < t.rect.y +t.rect.h 
						&& biggestY >t.rect.y /* + t.rect.h*/) {

						Grid->grid[c][r].glow = true;
					}
					else Grid->grid[c][r].glow = false;
				}
			}
		}
		break;

	case SDL_MOUSEBUTTONUP:
		
		switch (event.button.button) {

		case SDL_BUTTON_LEFT:
			if (event.button.state == SDL_RELEASED) {
				std::cout << "-----Not pressed-----" << std::endl;
				Lpressed = false;
				mouseRect = { 0,0,0,0 };
				for (int r = 0;r < Grid->rows;r++) {
					for (int c = 0;c < Grid->columns;c++) {
						auto t = Grid->grid[c][r];
						Grid->grid[c][r].glow = false;
					}
				}
			}	
			break;

		default:
			break;
		}
	default:
		break;
	}
};

void Game::update() {
	Grid->update();
};

void Game::render() {
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
	SDL_RenderClear(renderer);
	Grid->render(renderer);

	SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255);
	SDL_RenderDrawRect(renderer, &mouseRect);

	SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_BLEND); //Fill the mouseRect but enable transparency to see the grid behind
	SDL_SetRenderDrawColor(renderer, 200, 200, 200, 45); //The last parameter is only for blendmode
	SDL_RenderFillRect(renderer, &mouseRect);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

	SDL_RenderPresent(renderer);
};

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
};