#pragma once

#include "LibGame.h"
<<<<<<< HEAD
<<<<<<< HEAD
#define SDL_MAIN_HANDLED
#include "SDL.h"

//default value with 1280x720
#define DEFAULT_LENGTH 100
#define DEFAULT_WIDTH 20
#define DEFAULT_SPEED 10

class Player
{
public:
	// const
	static const int DEFAULT_LENGTH = 100;
	static const int DEFAULT_WIDTH = 20;
	static const int DEFAULT_SPEED = 10;
	//attributes:
private:
	//backend
	Point _pos;
=======

class Player
{
//attributes:
private:
	Point _pos;		
>>>>>>> parent of ae03b0e... Merge pull request #5 from viplazylmht/PlayerObject
=======

class Player
{
//attributes:
private:
	Point _pos;		
>>>>>>> parent of ae03b0e... Merge pull request #5 from viplazylmht/PlayerObject
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
	int ID() { return _id; }
	
	//void SetRender(SDL_Renderer* render) { _render = render; }

//constructor and destructor:
public:
	Player();
<<<<<<< HEAD
<<<<<<< HEAD
	//Description: create a player with given pos and id. All remain use default value (can use for 1280x720)
	Player(Point pos, int id, SDL_Renderer* render);
	Player(Point pos, int length, int width, int speed, int id, SDL_Renderer* render);
=======
=======
>>>>>>> parent of ae03b0e... Merge pull request #5 from viplazylmht/PlayerObject
	Player(Point pos, int length, int width, int speed, int id);
>>>>>>> parent of ae03b0e... Merge pull request #5 from viplazylmht/PlayerObject
	~Player();

//method
public:
	//Description: change position of x, and y base on give char
	//dir: 'l' for move left, 'r' for move right
<<<<<<< HEAD
<<<<<<< HEAD
	//render: render for draw and hide
=======
>>>>>>> parent of ae03b0e... Merge pull request #5 from viplazylmht/PlayerObject
=======
>>>>>>> parent of ae03b0e... Merge pull request #5 from viplazylmht/PlayerObject
	void Move(char dir);

	//Description: show player to the board
	void Draw();
<<<<<<< HEAD
<<<<<<< HEAD

	//Description: hide player
	void Hide();
=======
>>>>>>> parent of ae03b0e... Merge pull request #5 from viplazylmht/PlayerObject
=======
>>>>>>> parent of ae03b0e... Merge pull request #5 from viplazylmht/PlayerObject
};

