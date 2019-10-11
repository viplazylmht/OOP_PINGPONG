#include "MainGame.h"


//Descirption: draw board, player and ball

void MainGame::ShowMainMenu()
{
	if (!_initSucess) {
		cout << "An error occurred while create SDL Windows, quit now!\n";
		return;
	}

	// Listener for keyboard
	SDL_Event e;

	bool isInMainMenu = true;
	bool isQuit = false;

	int indexPos = 0;
	
	string fontPath = "Lib\\font\\SP3-TravelingTypewriter.ttf";

	vector<SDL_TextView> listText;
	listText.push_back(SDL_TextView(_render, 530, 300, "Player vs. CPU", 35, fontPath));
	listText.push_back(SDL_TextView(_render, 500, 400, "Player vs. Player", 35, fontPath));
	listText.push_back(SDL_TextView(_render, 560, 500, "Quit Game", 35, fontPath));

	
	listText.push_back(SDL_TextView(_render, 450, 50, "PING PONG", 100, fontPath));

	listText[indexPos].SetFlag(SDL_TextView::SELECTED);

	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
	bool _isPressed = false;

	while (isInMainMenu)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			switch (e.type)
			{

			case SDL_KEYDOWN: {
				_isPressed = true;
				break;
			}
			case SDL_KEYUP: {
				_isPressed = false;
				break;
			}

			//User requests quit
			case SDL_QUIT:
			{
				isInMainMenu = false;
				isQuit = true;
				break;
			}

			default:
				break;
			}

			if (_isPressed) {
				//check key
				if (keyboardState[SDL_SCANCODE_UP])
				{
					listText[indexPos].SetFlag(SDL_TextView::IN_SELECTED);
					indexPos = (indexPos > 0) ? indexPos - 1 : 2;
					listText[indexPos].SetFlag(SDL_TextView::SELECTED);
				}
				if (keyboardState[SDL_SCANCODE_DOWN])
				{
					listText[indexPos].SetFlag(SDL_TextView::IN_SELECTED);
					indexPos = (indexPos < 2) ? indexPos + 1 : 0;
					listText[indexPos].SetFlag(SDL_TextView::SELECTED);
				}

				// Enter on keyboard (do the same command with Enter on numpad)
				if (keyboardState[SDL_SCANCODE_RETURN] || keyboardState[SDL_SCANCODE_KP_ENTER])
				{
					isInMainMenu = false;
				}
			}
		}

		//Clear screen
		SDL_SetRenderDrawColor(_render, 0, 0, 0, 0);
		SDL_RenderClear(_render);

		for (auto text : listText) {
			text.Show();
		}

		//Update screen
		SDL_RenderPresent(_render);
		SDL_Delay(1000 / _fps);
	}

	if (isQuit) return;

	if (indexPos ==	1) {
		Play();
	}
	if (indexPos ==	0) {
		_isCPU = true;
		Play();
	}

}

void MainGame::Play()
{
	if (!_initSucess) {
		cout << "An error occurred while create SDL Windows, quit now!\n";
		return;
	}

	// Listener for keyboard
	SDL_Event e;

	CPU cpu;

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
		// lock player2 if play with computer
		if (!_isCPU)
		{
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
		}
		//play computer
		else
		{
			_player2.Move(cpu.CalcDirection(_ball, _player2, _height));			
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

		//Clear screen
		SDL_SetRenderDrawColor(_render, 0, 0, 0, 0xFF);
		SDL_RenderClear(_render);

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
		}
		if (_ball.Center().y >= _height - _ball.Radius()) {
			_ball.Collide(Ball::BORDER_BOTTOM);
		}

		//goal
		if (_ball.Center().x <= 0 + _ball.Radius()) {
			_ball.Collide(Ball::BORDER_LEFT);
			_winner = 2;
			Win();
		}
		if (_ball.Center().x >= _width - _ball.Radius()) {
			_ball.Collide(Ball::BORDER_RIGHT);
			_winner = 1;
			Win();
		}

		_player1.Draw();
		_player2.Draw();
		_ball.Move();

		cout << "SPEED: " << _ball.Speed() << " I: " << _ball.AxisI() << " J: " << _ball.AxisJ() << endl;
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

	_isCPU = false;
	_winner = 0;

	_initSucess = initSDL(_window, _render, _width, _height);

	//create player 1
	_player1 = Player({0, 0}, 1, _render);

	//create player 2
	_player2 = Player({_width - Player::DEFAULT_WIDTH, 0}, 2, _render);

	//create ball
	_ball = Ball(_render, { 50, 50 }, 20);
}
MainGame::MainGame(int width = DEFAULT_WIDTH, int height = DEFAULT_HEIGHT, int CUSTOM_FPS = DEFAULT_FPS)
{
	_width = width;
	_height = height;
	_fps = CUSTOM_FPS;

	_isPlaying = false;
	_initSucess = false;

	_initSucess = initSDL(_window, _render, width, height);

	_isCPU = false;
	_winner = 0;


	//create player 1
	_player1 = Player({ 0, 0 }, 1, _render);

	//create player 2
	_player2 = Player({ _width - DEFAULT_WIDTH, 0 }, 2, _render);

	//create ball 
	_ball = Ball(_render, { 50, 50 }, 20);

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
				//Initialize the truetype font API.
				if (TTF_Init() < 0)
				{
					SDL_Log("%s", TTF_GetError());
					return false;
				}
				else {
				//Initialize renderer color
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				}
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

	//Shutdown and cleanup the truetype font API.
	TTF_Quit();

	//Quit SDL subsystems
	SDL_Quit();
}
