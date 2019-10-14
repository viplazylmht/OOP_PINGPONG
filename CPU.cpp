#include "CPU.h"

//Description: calculate direction of player base on ball player
//height: acttual height of screen
char CPU::CalcDirection(Ball ball, Player player, int height)
{
	int centerOfPlayer = player.Pos().y + player.Length() / 2;
	if (ball.Center().y < centerOfPlayer - _error
		&& player.Pos().y > 0)
	{
		return 'u';
	}
	else if (ball.Center().y > centerOfPlayer + _error
		&& player.Pos().y + player.Length() < height)
	{
		return 'd';
	}
	else
	{
		return 0;
	}
}

CPU::CPU()
{
	_error = DEFAULT_ERROR;
}

CPU::CPU(int error)
{
	_error = error;
}

CPU::~CPU()
{
	//do somthing
}