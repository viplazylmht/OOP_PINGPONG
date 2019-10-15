#include "Ball.h"

Ball::Ball()
{
	_render = nullptr;

	_center.x = 0;
	_center.y = 0;

	_radius = 5;

	RandIandJ(_i, _j);

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

Ball::Ball(SDL_Renderer* render, Point firstLocation, int radius)
{
	_render = render;

	_center = firstLocation;
	_radius = radius;

	//_i = axisI;
	//_j = axisJ;

	RandIandJ(_i, _j);

	SyncSpeed();
}


void Ball::Move()
{
	// move one step 
	_center.x += AxisI();
	_center.y += AxisJ();

	// Draw new ball
	//Draw();
}

void Ball::Draw()
{
	// Draw Blue circle to graphic here  
	fill_circle(_render,_center.x, _center.y, _radius, 0xFF, 0, 0, 0xFF);

	//SDL_RenderPresent(_render);
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

void fill_circle(SDL_Renderer* render, int cx, int cy, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	for (double dy = 1; dy <= radius; dy += 1.0)
	{
		 //This loop is unrolled a bit, only iterating through half of the
		 //height of the circle.  The result is used to draw a scan line and
		 //its mirror image below it.

		 //The following formula has been simplified from our original.  We
		 //are using half of the width of the circle because we are provided
		 //with a center and we need left/right coordinates.

		double dx = floor(sqrt((2.0 * radius * dy) - (dy * dy)));
		int x = cx - dx;
		SDL_SetRenderDrawColor(render, r, g, b, a);

		// Draw first half of circle
		SDL_RenderDrawLine(render, cx - dx, cy + dy - radius, cx + dx, cy + dy - radius);
		
		// Draw second half of circle
		SDL_RenderDrawLine(render, cx - dx, cy - dy + radius, cx + dx, cy - dy + radius);

	}
}

void RandIandJ(float& i, float& j)
{
	srand(time(NULL));
	float nextRand = rand() % 3 + 4;
	i = nextRand;

	nextRand = rand() % 100 % 3 + 4;
	j = nextRand;
}