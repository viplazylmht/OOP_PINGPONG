#include <iostream>
#include "Player.h"

#define SDL_MAIN_HANDLED
#include <SDL.h>


using namespace std;
int main() {

	//Initializes  the subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Unable to initialize SDL %s\n", SDL_GetError());
		return -1;
	}

	SDL_Window* window = NULL;
	window = SDL_CreateWindow("PING PONG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Could not create window %s\n", SDL_GetError());
		return -1;
	}
	SDL_Renderer* render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	Point x;
	x.x = 0;
	x.y = 0;
	Player a(x, 1, render);
	x.x = 1280 - a.Width();
	Player b(x, 2, render);


	//game play
	SDL_Event event; 
	int alien_x = 0, alien_y = 0;
	for (;;)
	{
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				/* Look for a keypress */
			case SDL_KEYDOWN:
				/* Check the SDLKey values and move change the coords */
				switch (event.key.keysym.sym) {
				case SDLK_UP:
					a.Move('u');
					break;
				case SDLK_DOWN:
					a.Move('d');
					break;
				case SDLK_s:
					SDL_DestroyWindow(window);
				default:
					break;
				}
			}
		}
	}



	SDL_Delay(5000);

	//Destroy a window
	SDL_DestroyWindow(window);
	//This function cleans up all initialized subsystems
	SDL_Quit();

	cout << "Hello World!\n";
	return 0;
}