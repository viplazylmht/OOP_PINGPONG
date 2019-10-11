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

	//constructor and destructor
public:
	MainGame();
	MainGame(int, int, int);
	~MainGame();

	//method
public:
	//Descirption: draw board, player and ball
	//Return: -1 if fail
	void ShowMainMenu();
	void Play();
	bool initSDL(SDL_Window*&, SDL_Renderer*&, int, int);
	void closeSDL(SDL_Window*&, SDL_Renderer*&);

private:
	void GetKey1();
	void GetKey2();
	void Win();
};

