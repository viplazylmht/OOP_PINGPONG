#include <iostream>
<<<<<<< HEAD
#include "MainGame.h"
=======

#define SDL_MAIN_HANDLED
#include <SDL.h>

>>>>>>> parent of ae03b0e... Merge pull request #5 from viplazylmht/PlayerObject

using namespace std;
int main() {

<<<<<<< HEAD
	MainGame gamePlay;
=======
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
>>>>>>> parent of ae03b0e... Merge pull request #5 from viplazylmht/PlayerObject

	// game launcher already appeared from here

	gamePlay.Play();

	return 0;
}