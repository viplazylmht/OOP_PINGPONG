#pragma once
#include "Ball.h"
#include "Player.h"
#include <stdio.h>

#define SDL_MAIN_HANDLED
#include <SDL.h>

//default variable
#define DEFAULT_WIDTH 1280
#define DEFAULT_HEIGHT 720
#define DEFAULT_FPS 60

class MainGame
{
	//attribute:
private:
	//backend
	int _width;
	int _height;
	Player _player1;
	Player _player2;
	Ball _ball;
	bool _isPlaying;
	char _keyChar1;
	char _keyChar2;
	int _fps;

	//frontend
	SDL_Window* _window;
	SDL_Renderer* _render;

	//constructor and destructor
public:
	MainGame();
	MainGame(int width, int height);
	~MainGame();

	//method
public:
	//Descirption: draw board, player and ball
	//Return: -1 if failse
	void DrawGame();
	void Play();
private:
	void GetKey1();
	void GetKey2();
	void Win();
};

