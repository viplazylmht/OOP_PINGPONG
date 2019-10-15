#include "MainGame.h"


//Descirption: draw board, player and ball

bool MainGame::ShowMainMenu()
{
	if (!_initSucess) {
		cout << "An error occurred while create SDL Windows, quit now!\n";
		return false;
	}

	// Listener for keyboard
	SDL_Event e;

	bool isInMainMenu = true;
	bool isQuit = false;
	bool isInitComplete = false;

	bool _isPressed = false;
	int indexPos = 0;
	
	string fontPath = "Lib\\font\\SP3-TravelingTypewriter.ttf";

	vector<SDL_TextView> listText;
	listText.push_back(SDL_TextView(_render, 530, 300, "Player vs. CPU", 35, fontPath));
	listText[listText.size() - 1].SetCenterX(0, _width);

	listText.push_back(SDL_TextView(_render, 500, 400, "Player vs. Player", 35, fontPath));
	listText[listText.size() - 1].SetCenterX(0, _width);
	
	listText.push_back(SDL_TextView(_render, 560, 500, "Quit Game", 35, fontPath));
	listText[listText.size() - 1].SetCenterX(0, _width);
	
	listText.push_back(SDL_TextView(_render, 450, 50, "PING PONG", 100, fontPath));
	listText[listText.size() - 1].SetCenterX(0, _width);

	listText[indexPos].SetFlag(SDL_TextView::SELECTED);

	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
	
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

	if (indexPos ==	1) {
		isInitComplete = InitData(PLAY_VS_USER);
	}
	if (indexPos ==	0) {
		isInitComplete = InitData(PLAY_VS_CPU);
	}

	_isPlaying = !isQuit && isInitComplete;

	return _isPlaying;
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

	string fontPath = "Lib\\font\\SP3-TravelingTypewriter.ttf";

	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);

	while (ShowMainMenu()) {

		vector< SDL_TextView> listText;
		listText.push_back(SDL_TextView(_render, 200, 300, "Player 1", 50, fontPath));
		listText[listText.size() - 1].SetCenterX(0, _width / 2);

		if (_isCPU) {
			listText.push_back(SDL_TextView(_render, 850, 300, "CPU", 50, fontPath));
		}
		else {
			listText.push_back(SDL_TextView(_render, 850, 300, "Player 2", 50, fontPath));
		}
		listText[listText.size() - 1].SetCenterX(_width / 2, _width);
		
		listText[0].SetColor({ 255, 255, 255, 120 });
		listText[1].SetColor({ 255, 255, 255, 120 });

		// text for layout

		listText.push_back(SDL_TextView(_render, 0, 10, "PING PONG V1", 25, fontPath));
		listText[listText.size() - 1].SetCenterX(0, _width);

		listText[listText.size() - 1].SetColor({ 255, 0, 255, 200 });

		listText.push_back(SDL_TextView(_render, 0, _height - MARGIN_BOTTOM + 15, "Copyright by BHD233 & viplazylmht", 18, fontPath));
		listText[listText.size() - 1].SetCenterX(0, _width);
		listText[listText.size() - 1].SetColor({ 255, 100, 100, 200 });

		int dest = cpu.HardCalcDestination(_ball, _player2, 0 + MARGIN_TOP, _height - MARGIN_BOTTOM, _width);
		while (_isPlaying)
		{
			//play player
			//check key for move player1
			if (keyboardState[SDL_SCANCODE_S])
			{
				if (_player1.Pos().y + _player1.Length() + _player1.Speed() <= _height - MARGIN_BOTTOM)
				{
					_player1.Move(Player::MOVE_DOWN);
				}
			}
			else if (keyboardState[SDL_SCANCODE_W])
			{
				if (_player1.Pos().y - _player1.Speed() >= 0 + MARGIN_TOP)
				{
					_player1.Move(Player::MOVE_UP);
				}
			}
			// lock player2 if play with computer
			if (!_isCPU)
			{
				if (keyboardState[SDL_SCANCODE_DOWN])
				{
					if (_player2.Pos().y + _player2.Length() + _player2.Speed() <= _height - MARGIN_BOTTOM)
					{
						_player2.Move(Player::MOVE_DOWN);
					}
				}

				else if (keyboardState[SDL_SCANCODE_UP])
				{
					if (_player2.Pos().y - _player2.Speed() >= 0 + MARGIN_TOP)
					{
						_player2.Move(Player::MOVE_UP);
					}
				}
			}
			//play computer
			else
			{
				//_player2.Move(cpu.EasyCalcDirection(_ball, _player2, 0 + MARGIN_TOP, _height - MARGIN_BOTTOM));
				cpu.MoveToDest(_player2, dest, 0 + MARGIN_TOP, _height - MARGIN_BOTTOM);
			}

			//detect quit button clicked
			while (SDL_PollEvent(&e) != 0)
			{
				//User requests quit
				if (e.type == SDL_QUIT)
				{
					_isPlaying = false;
					return;
				}
			}

			//Clear screen
			SDL_SetRenderDrawColor(_render, 0, 0, 0, 0xFF);
			SDL_RenderClear(_render);

			//collide player 1
			if (IsCollidePlayer1())
			{
				_ball.Collide(Ball::BORDER_LEFT);
				_ball.LevelUp();
				dest = cpu.HardCalcDestination(_ball, _player2, 0 + MARGIN_TOP, _height - MARGIN_BOTTOM, _width);
			}
			//collide player 2
			if (IsCollidePlayer2()) 
			{
				_ball.Collide(Ball::BORDER_RIGHT);
				_ball.LevelUp();
			}

			//collide wall
			if (_ball.Center().y <= 0 + _ball.Radius() + MARGIN_TOP) {
				_ball.Collide(Ball::BORDER_TOP);
			}
			if (_ball.Center().y >= _height - _ball.Radius() - MARGIN_BOTTOM) {
				_ball.Collide(Ball::BORDER_BOTTOM);
			}

			//goal
			if (_ball.Center().x <= 0 + _ball.Radius() && !IsCollidePlayer1()) {
				_ball.Collide(Ball::BORDER_LEFT);
				_winner = 2;
				Win();
				dest = cpu.HardCalcDestination(_ball, _player2, 0 + MARGIN_TOP, _height - MARGIN_BOTTOM, _width);
				continue;
			}
			if (_ball.Center().x >= _width - _ball.Radius() && !IsCollidePlayer2()) {
				_ball.Collide(Ball::BORDER_RIGHT);
				_winner = 1;
				Win();
				dest = cpu.HardCalcDestination(_ball, _player2, 0 + MARGIN_TOP, _height - MARGIN_BOTTOM, _width);
				continue;
			}

			_ball.Move();

			for (auto text : listText) text.Show();

			DrawCenterLine();
			_player1.Draw();
			_player2.Draw();
			_ball.Draw();

			//fill_circle(render, 100, 100, 50, 0xFF, 0x00, 0xFF, 0xFF);


			//Update screen
			SDL_RenderPresent(_render);
			SDL_Delay(1000 / _fps);
		}

	}
}

bool MainGame::InitData(int FLAG)
{
	_isCPU = false;
	switch (FLAG)
	{
	case PLAY_VS_CPU: _isCPU = true;
	case PLAY_VS_USER:
	{
		//create player 1
		_player1 = Player({ 0, (_height - Player::DEFAULT_LENGTH) / 2 }, 1, _render);

		//create player 2
		_player2 = Player({ _width - Player::DEFAULT_WIDTH, (_height + Player::DEFAULT_LENGTH) / 2 }, 2, _render);

		//create ball
		_ball = Ball(_render, { 50, 50 }, 15);

		return true;
	}
	
	default:
		return false;
	}
}

void MainGame::InitLayout()
{
	_verticalLine.w = 1;
	_verticalLine.h = _height - MARGIN_BOTTOM - MARGIN_TOP;
	_verticalLine.x = _width / 2 - _verticalLine.w / 2;
	_verticalLine.y = MARGIN_TOP;

	_hozinotalTop.h = 6;
	_hozinotalTop.w = _width;
	_hozinotalTop.x = 0;
	_hozinotalTop.y = 0 + MARGIN_TOP - _hozinotalTop.h;

	_hozinotalBottom.h = 6;
	_hozinotalBottom.w = _width;
	_hozinotalBottom.x = 0;
	_hozinotalBottom.y = _height - MARGIN_BOTTOM;
}

void MainGame::Win()
{
	SDL_Event e;

	bool isInWin = true;
	bool isQuit = false;

	int indexPos = 0;

	string fontPath = "Lib\\font\\SP3-TravelingTypewriter.ttf";

	vector<SDL_TextView> listText;
	listText.push_back(SDL_TextView(_render, 100, 500, "Play Again", 35, fontPath));
	listText[listText.size() - 1].SetCenterX(0, _width / 2);

	listText.push_back(SDL_TextView(_render, 1000, 500, "Main Menu", 35, fontPath));
	listText[listText.size() - 1].SetCenterX(_width / 2, _width);

	//set text for winner
	string winText = "Player " + to_string(_winner) + " Win!!!";
	
	if (_isCPU && _winner == 2)
	{
		winText = "CPU Win!!";
	}

	//other posision if cpu win
	if (winText == "CPU Win!!")
	{
		listText.push_back(SDL_TextView(_render, 520, 300, winText, 80, fontPath));
	}
	else
	{
		listText.push_back(SDL_TextView(_render, 400, 300, winText, 80, fontPath));
	}
	listText[listText.size() - 1].SetCenterX(0, _width);
	listText.push_back(SDL_TextView(_render, 450, 50, "PING PONG", 100, fontPath));
	listText[listText.size() - 1].SetCenterX(0, _width);

	listText[indexPos].SetFlag(SDL_TextView::SELECTED);

	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
	bool _isPressed = false;

	while (isInWin)
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
				isInWin = false;
				isQuit = true;
				break;
			}

			default:
				break;
			}

			if (_isPressed) {
				//check key
				if (keyboardState[SDL_SCANCODE_LEFT])
				{
					listText[indexPos].SetFlag(SDL_TextView::IN_SELECTED);
					indexPos = (indexPos > 0) ? indexPos - 1 : 1;
					listText[indexPos].SetFlag(SDL_TextView::SELECTED);
				}
				if (keyboardState[SDL_SCANCODE_RIGHT])
				{
					listText[indexPos].SetFlag(SDL_TextView::IN_SELECTED);
					indexPos = (indexPos < 1) ? indexPos + 1 : 0;
					listText[indexPos].SetFlag(SDL_TextView::SELECTED);
				}

				// Enter on keyboard (do the same command with Enter on numpad)
				if (keyboardState[SDL_SCANCODE_RETURN] || keyboardState[SDL_SCANCODE_KP_ENTER])
				{
					isInWin = false;
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
		_player1.Draw();
		_player2.Draw();
		_ball.Draw();
		SDL_RenderPresent(_render);
		SDL_Delay(1000 / _fps);
	}

	if (isQuit)
	{
		_isPlaying = false;
	}
	else if (indexPos == 0) {
		if (_isCPU) {
			InitData(PLAY_VS_CPU);
		}
		else
		{
			InitData(PLAY_VS_USER);
		}
		_isPlaying = true;
	}
	else if (indexPos == 1) {
		_isPlaying = false;
	}

}

void MainGame::DrawCenterLine()
{
	SDL_SetRenderDrawColor(_render, 255, 255, 255, 5);

	SDL_RenderFillRect(_render, &_verticalLine);
	SDL_RenderFillRect(_render, &_hozinotalBottom);
	SDL_RenderFillRect(_render, &_hozinotalTop);

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

	InitData(NULL);

	InitLayout();

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

	InitData(NULL);

	InitLayout();
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

bool MainGame::IsCollidePlayer1()
{
	if (_ball.Center().x <= 0 + _ball.Radius() + _player1.Width()
		&& _ball.Center().y >= _player1.Pos().y
		&& _ball.Center().y <= _player1.Pos().y + _player1.Length())
	{
		return true;
	}

	return false;
}

bool MainGame::IsCollidePlayer2()
{
	if (_ball.Center().x >= _width - _ball.Radius() - _player2.Width()
		&& _ball.Center().y >= _player2.Pos().y
		&& _ball.Center().y <= _player2.Pos().y + _player2.Length())
	{
		return true;
	}

	return false;
}