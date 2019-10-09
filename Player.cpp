#include "Player.h"


//Description: change position of x, and y base on give char
//dir: 'l' for move left, 'r' for move right
void Player::Move(char dir)
{
	if (dir == 'l')
	{
		_pos.x -= _speed;
	}
	else if (dir == 'r')
	{
		_pos.x += _speed;
	}
}

//Description: show player to the board
void Player::Draw()
{
	//do something
}


Player::Player()
{
	_pos.x = 0;
	_pos.y = 0;
	_length = 0;
	_width = 0;
	_speed = 0;
	_id = 0;
}

Player::Player(Point pos, int length, int width, int speed, int id)
{
	_pos = pos;
	_length = length;
	_width = width;
	_speed = speed;
	_id = id;
}

Player::~Player()
{
	//do something
}