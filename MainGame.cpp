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

	_player1.Draw();
	_player2.Draw();

	_isPlaying = true;

	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);

	while (_isPlaying)
	{
		//check key for move player
		if (keyboardState[SDL_SCANCODE_S])
		{
			if (_player1.Pos().y + _player1.Length() + _player1.Speed() <= _height)
			{
				_player1.Move('d');
			}
		}
		else if (keyboardState[SDL_SCANCODE_W])
		{
			if (_player1.Pos().y - _player1.Speed() >= 0)
			{
				_player1.Move('u');
			}
		}

		if (keyboardState[SDL_SCANCODE_DOWN])
		{
			if (_player2.Pos().y + _player2.Length() + _player2.Speed() <= _height)
			{
				_player2.Move('d');
			}
		}

		else if (keyboardState[SDL_SCANCODE_UP])
		{
			if (_player2.Pos().y - _player2.Speed() >= 0)
			{
				_player2.Move('u');
			}
		}

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

		//collide player 1
		if (_ball.Center().x <= 0 + _ball.Radius() + _player1.Width()
			&& _ball.Center().y >= _player1.Pos().y
			&& _ball.Center().y <= _player1.Pos().y + _player1.Length()) 
		{
			_ball.Collide(Ball::BORDER_LEFT);
			_ball.LevelUp();
		}
		//collide player 1
		if (_ball.Center().x >= _width - _ball.Radius() - _player2.Width()
			&& _ball.Center().y >= _player2.Pos().y
			&& _ball.Center().y <= _player2.Pos().y + _player2.Length()) {
			_ball.Collide(Ball::BORDER_RIGHT);
			_ball.LevelUp();
		}

		//collide wall
		if (_ball.Center().y <= 0 + _ball.Radius()) {
			_ball.Collide(Ball::BORDER_TOP);
			//_ball.LevelUp();
		}
		if (_ball.Center().y >= _height - _ball.Radius()) {
			_ball.Collide(Ball::BORDER_BOTTOM);
			//_ball.LevelUp();
		}

		//goal
		if (_ball.Center().x <= 0 + _ball.Radius()) {
			_ball.Collide(Ball::BORDER_LEFT);
			_winner = 2;
			Win();
			//_ball.LevelUp();
		}
		if (_ball.Center().x >= _width - _ball.Radius()) {
			_ball.Collide(Ball::BORDER_RIGHT);
			_winner = 1;
			Win();
			//_ball.LevelUp();
		}

		_ball.Move();

		cout << "SPEED: " << _ball.Speed() << endl;
		//fill_circle(render, 100, 100, 50, 0xFF, 0x00, 0xFF, 0xFF);


		//Update screen
		SDL_RenderPresent(_render);
		SDL_Delay(1000 / _fps);
	}

}


void MainGame::Win()
{
	_isPlaying = false;

}

MainGame::MainGame()
{
	_width = DEFAULT_WIDTH;
	_height = DEFAULT_HEIGHT;
	_fps = DEFAULT_FPS;

	_isPlaying = false;
	_initSucess = false;

	_winner = 0;

	_initSucess = initSDL(_window, _render, _width, _height);

	//create player 1
	_player1 = Player({0, 0}, 1, _render);

	//create player 2
	_player2 = Player({_width - Player::DEFAULT_WIDTH, 0}, 2, _render);

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

	_winner = 0;


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
