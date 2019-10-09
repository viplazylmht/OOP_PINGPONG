#include "Player.h"


//Description: change position of x, and y base on give char
//dir: 'l' for move left, 'r' for move right
void Player::Move(char dir)
{
	if (dir == 'l')
	{
		_x -= _speed;
	}
	else if (dir == 'r')
	{
		_x += _speed;
	}
}

//Description: show player to the board
void Player::Draw()
{
	//do something
}


Player::Player()
{
	_x = 0;
	_y = 0;
	_length = 0;
	_width = 0;
	_speed = 0;
	_id = 0;
}

Player::Player(int x, int y, int length, int width, int speed, int id)
{
	_x = x;
	_y = y;
	_length = length;
	_width = width;
	_speed = speed;
	_id = id;
}

Player::~Player()
{
	//do something
}