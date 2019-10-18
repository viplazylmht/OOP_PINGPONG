#pragma once

#include "Ball.h"
#include "Player.h"
#include "LibGame.h"

class CPU
{
public:
	const int DEFAULT_ERROR = 30;
private:
	int _error;		//is dental to make it easier
	bool _waitToNextMove;		//detect if it is time to move to right dest or not (just for hard CPU)
								//true if it is time to move to hit ball
								//false if it is time to follow the ball

public:
	bool WaitToNextMove(); 
	void SetWaitToNextMove(bool);

	CPU();
	CPU(int error);
	~CPU();

public:
	//Description: calculate direction of player base on ball player easy level
	//top: top of screen
	//bottom: bottom of screen
	//player: player that CPU control
	//Return: direction (up or down) or 0 if want CPU stand still
	char EasyCalcDirection(Ball ball, Player player, int top, int bottom);

	//Description: calculate direction of player base on ball player hard level
	//top: top of screen
	//bottom: bottom of screen
	//realWidth: acttual width of screen
	//player: player that CPU control
	//Return: possision y that player have to move to
	int HardCalcDestination(Ball ball, Player player, int top, int bottom, int realWidth);
	//Description: make player move to destination
	//top: top of screen
	//bottom: bottom of screen
	void MoveToDest(Player &player, int dest, int top, int bottom);
};

