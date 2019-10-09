#include "MainGame.h"

//Descirption: draw board, player and ball
//Return: -1 if failse
void MainGame::DrawGame()
{
	//draw board
	//............................

	//add player
	_player1.Draw();
	_player2.Draw();

	//add ball
	//...............................

	SDL_Delay(5000);		//this will change to Play() when Play() ready
}
void MainGame::Play()
{

}
void MainGame::GetKey1()
{

}
void MainGame::GetKey2()
{

}
void MainGame::Win()
{

}

MainGame::MainGame()
{
	_width = DEFAULT_HEIGHT;
	_height = DEFAULT_HEIGHT;
	_fps = DEFAULT_FPS;
	_isPlaying = false;
	_keyChar1 = 0;
	_keyChar2 = 0;

	//Create window and render
	//Initializes  the subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Unable to initialize SDL %s\n", SDL_GetError());
	}
	//create new window
	_window = NULL;
	_window = SDL_CreateWindow("PING PONG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, SDL_WINDOW_SHOWN);
	if (_window == NULL)
	{
		printf("Could not create window %s\n", SDL_GetError());
	}
	//create new render for show object
	_render = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	
	//create pos for player 1
	Point pos1;
	pos1.x = 0;
	pos1.y = 0;
	_player1 = Player(pos1, 1, _render);

	//create pos for player 2
	Point pos2;
	pos2.x = _width - DEFAULT_WIDTH;
	pos2.y = 0;
	_player2 = Player(pos2, 2, _render);

	//create ball....


}
MainGame::MainGame(int width, int height)
{
	_width = width;
	_height = height;
	_fps = DEFAULT_FPS;
	_isPlaying = false;
	_keyChar1 = 0;
	_keyChar2 = 0;

	//create pos for player 1
	Point pos1;
	pos1.x = 0;
	pos1.y = 0;
	_player1 = Player(pos1, 1, _render);

	//create pos for player 2
	Point pos2;
	pos2.x = _width - DEFAULT_WIDTH;
	pos2.y = 0;
	_player2 = Player(pos2, 2, _render);

	//create ball....


}
MainGame::~MainGame()
{
	//Destroy a window
	SDL_DestroyWindow(_window);
	//This function cleans up all initialized subsystems
	SDL_Quit();
}
