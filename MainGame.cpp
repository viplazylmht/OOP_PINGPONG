#include "MainGame.h"

//Descirption: draw board, player and ball

void MainGame::Play()
{
	if (!_initSucess) {
		cout << "An error occurred while create SDL Windows, quit now!\n";
		return;
	}

	// Listener for keyboard
	SDL_Event e;

	_isPlaying = true;

	while (_isPlaying)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				_isPlaying = false;
			}
		}

		////Clear screen
		//SDL_SetRenderDrawColor(_render, 0, 0, 0, 0xFF);
		//SDL_RenderClear(_render);

		if (_ball.Center().x <= 0 + _ball.Radius()) {
			_ball.Collide(Ball::BORDER_LEFT);
			_ball.LevelUp();
		}
		if (_ball.Center().x >= _width - _ball.Radius()) {
			_ball.Collide(Ball::BORDER_RIGHT);
			_ball.LevelUp();
		}
		if (_ball.Center().y <= 0 + _ball.Radius()) {
			_ball.Collide(Ball::BORDER_TOP);
			_ball.LevelUp();
		}
		if (_ball.Center().y >= _height - _ball.Radius()) {
			_ball.Collide(Ball::BORDER_BOTTOM);
			_ball.LevelUp();
		}

		_ball.Move();

		cout << "SPEED: " << _ball.Speed() << endl;
		//fill_circle(render, 100, 100, 50, 0xFF, 0x00, 0xFF, 0xFF);


		//Update screen
		SDL_RenderPresent(_render);
		SDL_Delay(1000 / _fps);
	}


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
	_width = DEFAULT_WIDTH;
	_height = DEFAULT_HEIGHT;
	_fps = DEFAULT_FPS;

	_isPlaying = false;
	_initSucess = false;

	_keyChar1 = 0;
	_keyChar2 = 0;

	_initSucess = initSDL(_window, _render, _width, _height);

	//create player 1
	_player1 = Player({0, 0}, 1, _render);

	//create player 2
	_player2 = Player({_width - DEFAULT_WIDTH, 0}, 2, _render);

	//create ball
	_ball = Ball(_render, { 50, 50 }, 20, 4, 5);

}
MainGame::MainGame(int width = DEFAULT_WIDTH, int height = DEFAULT_HEIGHT, int CUSTOM_FPS=DEFAULT_FPS)
{
	_width = width;
	_height = height;
	_fps = CUSTOM_FPS;

	_isPlaying = false;
	_initSucess = false;

	_initSucess = initSDL(_window, _render, width, height);

	_keyChar1 = 0;
	_keyChar2 = 0;


	//create player 1
	_player1 = Player({ 0, 0 }, 1, _render);

	//create player 2
	_player2 = Player({ _width - DEFAULT_WIDTH, 0 }, 2, _render);

	//create ball 
	_ball = Ball(_render, { 50, 50 }, 20, 4, 5);

}
MainGame::~MainGame()
{
	closeSDL(_window, _render);
}


bool MainGame::initSDL(SDL_Window*& window, SDL_Renderer*& renderer, int SCREEN_WIDTH = DEFAULT_WIDTH, int SCREEN_HEIGHT = DEFAULT_HEIGHT)
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("PING PONG", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

			}
		}
	}
	return success;
}

void MainGame::closeSDL(SDL_Window*& window, SDL_Renderer*& renderer)
{
	//Destroy window    
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}
