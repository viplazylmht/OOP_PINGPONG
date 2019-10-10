#include "Player.h"


//Description: change position of x, and y base on give char
//amd draw player base on new position (hide the old and draw the new one)
//dir: 'u' for move up, 'd' for move down
//render: render for draw and hide
void Player::Move(char dir)
{
	//hide old one
	Hide();

	//calcualte new position
	if (dir == 'u')
	{
		_pos.y -= _speed;
	}
	else if (dir == 'd')
	{
		_pos.y += _speed;
	}

	_rect.y = _pos.y;

	//draw new one
	Draw();
}

//Description: show player to the board
void Player::Draw()
{
	SDL_SetRenderDrawColor(_render, 0, 0, 255, 255);

	SDL_SetRenderDrawColor(_render, 0, 0, 255, 255);

	SDL_RenderFillRect(_render, &rect);

	SDL_RenderPresent(_render);
}

//Description: hide player
void Player::Hide()
{
	//draw black rectangle
	SDL_SetRenderDrawColor(_render, 0, 0, 0, 255);

	SDL_RenderFillRect(_render, &rect);

	SDL_RenderPresent(_render);
}

//Description: create a player with pos (0, 0) and all default value (can use for 1280x720)
Player::Player()
{
	_render = nullptr;
	_pos.x = 0;
	_pos.y = 0;
	_length = DEFAULT_LENGTH;
	_width = DEFAULT_WIDTH;
	_speed = DEFAULT_SPEED;
	_id = 0;

	//fontend
	_rect.x = _pos.x;
	_rect.y = _pos.y;
	_rect.h = _length;
	_rect.w = _width;

}

Player::Player(Point pos, int id, SDL_Renderer* render)
{
	//backend
	_pos = pos;
	_length = DEFAULT_LENGTH;
	_width = DEFAULT_WIDTH;
	_speed = DEFAULT_SPEED;
	_id = id;
	_render = render;
}

Player::Player(Point pos, int length, int width, int speed, int id, SDL_Renderer* render)
{
	//backend
	_pos = pos;
	_length = length;
	_width = width;
	_speed = speed;
	_id = id;
	_render = render;
}

Player::~Player()
{
	//do something
}