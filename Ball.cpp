#include "Ball.h"

Ball::Ball()
{
	_center.x = 0;
	_center.y = 0;

	_radius = 5;
	_i = _j = 1;

	SyncSpeed();

}

void Ball::SyncSpeed()
{
	_speed = sqrt((double)_i * (double)_i + (double)_j * (double)_j);
}

void Ball::SetCenter(Point point)
{
	_center = point;
}

void Ball::SetCenter(int x, int y)
{
	_center.x = x;
	_center.y = y;
}

void Ball::SetRadius(int radius)
{
	_radius = radius;
}

void Ball::SetAxisI(int i)
{
	_i = i;
	SyncSpeed();
}

void Ball::SetAxisJ(int j)
{
	_j = j;
	SyncSpeed();
}

bool Ball::Collide(int DIRECTION)
{
	switch (DIRECTION)
	{
	case BORDER_LEFT: 
	{
		_i = (_i > 0) ? _i : -_i;
		break;
	}
	case BORDER_RIGHT:
	{
		_i = (_i < 0) ? _i : -_i;
		break;
	}
	case BORDER_TOP:
	{
		_j = (_j > 0) ? _j : -_j;
		break;
	}
	case BORDER_BOTTOM:
	{
		_j = (_j < 0) ? _j : -_j;
		break;
	}
	case BORDER_CORNER:
	{
		_j = -_j;
		_i = -_i;
		break;
	}
	default:
		return false;
	}

	return true;
}

Ball::Ball(Point firstLocation, int radius, int axisI, int axisJ)
{
	_center = firstLocation;
	_radius = radius;

	_i = axisI;
	_j = axisJ;

	SyncSpeed();
}


void Ball::Move()
{
	// move one step 
	_center.x += AxisI();
	_center.y += AxisJ();
}

void Ball::Draw()
{
	// Draw to graphic here  
}

void Ball::LevelUp()
{
	// increase speed until current speed greater than MAX_SPEED
	if (Speed() < MAX_SPEED) {

		_i += _i / 10;
		_j += _j / 10;

		SyncSpeed();
	}
}