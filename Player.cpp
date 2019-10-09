#include "Player.h"


//Description: change position of x, and y base on give char
//amd draw player base on new position (hide the old and draw the new one)
//dir: 'u' for move up, 'd' for move down
//render: render for draw and hide
void Player::Move(char dir, SDL_Renderer* render)
{
	//hide old one
	Hide(render);

	//calcualte new position
	if (dir == 'u')
	{
		_pos.y -= _speed;
	}
	else if (dir == 'd')
	{
		_pos.y += _speed;
	}

	//draw new one
	Draw(render);
}

//Description: show player to the board
void Player::Draw(SDL_Renderer* render)
{
	//do something
	SDL_Rect rect;
	rect.x = _pos.x;
	rect.y = _pos.y;
	rect.h = _length;
	rect.w = _width;

	SDL_SetRenderDrawColor(render, 0, 0, 255, 255);

	SDL_RenderFillRect(render, &rect);

	SDL_RenderPresent(render);
}

//Description: hide player
void Player::Hide(SDL_Renderer* render)
{
	SDL_Rect rect;
	rect.x = _pos.x;
	rect.y = _pos.y;
	rect.h = _length;
	rect.w = _width;

	//draw black rectangle
	SDL_SetRenderDrawColor(render, 0, 0, 0, 255);

	SDL_RenderFillRect(render, &rect);

	SDL_RenderPresent(render);
}

//Description: create a player with pos (0, 0) and all default value (can use for 1280x720)
Player::Player()
{
	_pos.x = 0;
	_pos.y = 0;
	_length = DEFAULT_LENGTH;
	_width = DEFAULT_WIDTH;
	_speed = DEFAULT_SPEED;
	_id = 0;
}

Player::Player(Point pos, int id)
{
	_pos = pos;
	_length = DEFAULT_LENGTH;
	_width = DEFAULT_WIDTH;
	_speed = DEFAULT_SPEED;
	_id = id;
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