#pragma once

#include "LibGame.h"

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
	Player();
	Player(Point pos, int length, int width, int speed, int id);
	~Player();

//method
public:
	//Description: change position of x, and y base on give char
	//dir: 'l' for move left, 'r' for move right
	void Move(char dir);

	//Description: show player to the board
	void Draw();
};

