#pragma once

#include "Ball.h"
#include "Player.h"

class CPU
{
public:
	const int DEFAULT_ERROR = 30;
private:
	int _error;		//is dental to make it easier

public:
	CPU();
	CPU(int error);
	~CPU();

public:
	//Description: calculate direction of player base on ball player
	//height: acttual height of screen
	char CalcDirection(Ball ball, Player player, int height);
};

