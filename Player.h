#pragma once
class Player
{
//attributes:
private:
	int _x, _y;		//will be point
	int _length;
	int _width;
	int _speed;
	int _id;		//1 or 2

public:
	int X() { return _x; }
	int Y() { return _y; }
	int Length() { return _length; }
	int ID() { return _id; }

//constructor and destructor:
public:
	Player();
	Player(int x, int y, int length, int width, int speed, int id);
	~Player();

//method
public:
	//Description: change position of x, and y base on give char
	//dir: 'l' for move left, 'r' for move right
	void Move(char dir);

	//Description: show player to the board
	void Draw();
};

