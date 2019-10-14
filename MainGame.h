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
	//backend
	int _width;
	int _height;
	Player _player1;
	Player _player2;
	Ball _ball;
	bool _isPlaying;
	bool _initSucess;
	int _fps;
	int _winner;
	bool _isCPU;

	//frontend
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
	//Return: -1 if fail
	bool ShowMainMenu();
	void Play();
	bool initSDL(SDL_Window*&, SDL_Renderer*&, int, int);
	void closeSDL(SDL_Window*&, SDL_Renderer*&);

private:
	bool InitData(int);
	void InitLayout();
	void Win();
	void DrawCenterLine();
};

