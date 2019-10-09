#pragma once

#include "LibGame.h"

#define SDL_MAIN_HANDLED

#include "SDL.h"

//default value with 1280x720
#define DEFAULTLENGTH 100
#define DEFAULTWIDTH 20
#define DEFAULTSPEED 10

class Player
{
	//attributes:
private:
	Point _pos;
	int _length;
	int _width;
	int _speed;
	int _id;		//1 or 2

public:
	Point Pos() { return _pos; }
	int Length() { return _length; }
	int ID() { return _id; }

	//constructor and destructor:
public:
	//Description: create a player with pos (0, 0), id = 0 and all default value (can use for 1280x720)
	Player();
	//Description: create a player with given pos and id. All remain use default value (can use for 1280x720)
	Player(Point pos, int id);
	Player(Point pos, int length, int width, int speed, int id);
	~Player();

	//method
public:
	//Description: change position of x, and y base on give char
	//amd draw player base on new position (hide the old and draw the new one)
	//dir: 'l' for move left, 'r' for move right
	//render: render for draw and hide
	void Move(char dir, SDL_Renderer* render);

	//Description: show player to the board
	void Draw(SDL_Renderer* render);

	//Description: hide player
	void Hide(SDL_Renderer* render);
};

