#pragma once
#include "Ball.h"
#include "Player.h"
#include "CPU.h"
#include <stdio.h>
#include <iostream>
#include <vector>

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "SDL_TextView.h"

using namespace std;

class MainGame
{
public:
	// const 
	static const int DEFAULT_WIDTH = 1280;
	static const int DEFAULT_HEIGHT = 720;
	static const int DEFAULT_FPS = 60;

	static const int PLAY_VS_USER = 1;
	static const int PLAY_VS_CPU = 2;
	
	// margin by pixel
	static const int MARGIN_TOP = 50;
	static const int MARGIN_BOTTOM = 50;

	//attribute:
private:

	//window screen size
	int _width;
	int _height;

	// Object
	Player _player1;
	Player _player2;
	Ball _ball;

	// Control
	bool _isPlaying;
	bool _initSucess;
	int _fps;
	int _winner;
	
	// CPU
	bool _isCPU;
	int _cpuLevel;

	//SDL Framework
	SDL_Window* _window;
	SDL_Renderer* _render;
	SDL_Rect _verticalLine, _hozinotalTop, _hozinotalBottom;

	//constructor and destructor
public:
	MainGame();
	MainGame(int, int, int);
	~MainGame();

	//method
public:
	//Descirption: draw board, player and ball
	//Return: false if user want to quit game, else return false
	bool ShowMainMenu();

	//Descirption: Run main game
	void Play();

	// Description: Create and Init SDL, TTF framework
	bool InitSDL(SDL_Window*&, SDL_Renderer*&, int, int);

	// Description: Free and close SDL, TTF framework
	void CloseSDL(SDL_Window*&, SDL_Renderer*&);

private:
	// Description: Init players and ball
	// Parameter: + FLAG: Init the type of gamePlay (Player vs Player or Player vs CPU) 
	bool InitData(int);

	// Description: Init the border and center line in game
	void InitLayout();

	// Description: Show Win layout and wait user select next action
	// Parameter: The score of last game play
	//Return: true if player hit quit button, false if not
	bool Win(int);

	// Description: Draw the border and center line while playing game
	void DrawLayout();

	// Description: Check collide with Player1 (left)
	// Return: true if ball collide with Player1
	bool IsCollidePlayer1();

	// Description: Check collide with Player2 (right)
	// Return: true if ball collide with Player2
	bool IsCollidePlayer2();
};

