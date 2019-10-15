#include "CPU.h"
#include <math.h>
#include <iostream>

using namespace std;

//Description: calculate direction of player base on ball player
//top: top of screen
//bottom: bottom of screen
//player: player that CPU control
//Return: direction (up or down) or 0 if want CPU stand still
char CPU::EasyCalcDirection(Ball ball, Player player, int top, int bottom)
{
	int centerOfPlayer = player.Pos().y + player.Length() / 2;
	if (ball.Center().y < centerOfPlayer - _error
		&& player.Pos().y > top)
	{
		return Player::MOVE_UP;
	}
	else if (ball.Center().y > centerOfPlayer + _error
		&& player.Pos().y + player.Length() < bottom)
	{
		return Player::MOVE_DOWN;
	}
	else
	{
		return 0;
	}
}

//Description: calculate direction of player base on ball player
//top: top of screen
//bottom: bottom of screen
//realWidth: acttual width of screen
//player: player that CPU control
//Return: direction (up or down) or 0 if want CPU stand still
int CPU::HardCalcDestination(Ball ball, Player player, int top, int bottom, int realWidth)
{
	//let ball move
	while (ball.Center().x + ball.Radius() < realWidth)
	{
		//collide wall
		if (ball.Center().y <= ball.Radius() + top) {
			ball.Collide(Ball::BORDER_TOP);
		}
		if (ball.Center().y >= bottom - ball.Radius()) {
			ball.Collide(Ball::BORDER_BOTTOM);
		}
		ball.Move();
	}

	return ball.Center().y;
}

//Description: make player move to destination
void CPU::MoveToDest(Player &player, int dest, int top, int bottom)
{
	if ((player.Pos().y + player.Length() / 2 < dest) && player.Pos().y < bottom)
	{
		player.Move(Player::MOVE_DOWN);
	}
	if ((player.Pos().y + player.Length() / 2 > dest) && player.Pos().y > top)
	{
		player.Move(Player::MOVE_UP);
	}
}

bool CPU::WaitToNextMove()
{
	return _waitToNextMove;
}

void CPU::SetWaitToNextMove(bool value)
{
	_waitToNextMove = value;
}

CPU::CPU()
{
	_waitToNextMove = false;
	_error = DEFAULT_ERROR;
}

CPU::CPU(int error)
{
	_waitToNextMove = false;
	_error = error;
}

CPU::~CPU()
{
	//do somthing
}