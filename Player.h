#pragma once

#include "LibGame.h"
#define SDL_MAIN_HANDLED
#include "SDL.h"
class Player
{
public:
	// const
	static const int DEFAULT_LENGTH = 100;
	static const int DEFAULT_WIDTH = 10;
	static const int DEFAULT_SPEED = 10;
	//attributes:
private:
	Point _pos;		
	int _length;
	int _width;
	int _speed;
	int _id;		//1 or 2
	
	//frontend
	SDL_Renderer* _render;
	SDL_Rect _rect;

public:
	Point Pos() { return _pos; }
	int Length() { return _length; }
	int Width() { return _width; }
	int Speed() { return _speed; }
	int ID() { return _id; }
	
	//void SetRender(SDL_Renderer* render) { _render = render; }

//constructor and destructor:
public:
	Player();
	//Description: create a player with given pos and id. All remain use default value (can use for 1280x720)
	Player(Point pos, int id, SDL_Renderer* render);
	Player(Point pos, int length, int width, int speed, int id, SDL_Renderer* render);
	~Player();

//method
public:
	//Description: change position of x, and y base on give char
	//dir: 'u' for move up, 'd' for move down
	void Move(char dir);

	//Description: show player to the board
	void Draw();

};

