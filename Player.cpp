#include "Player.h"


//Description: change position of x, and y base on give char
<<<<<<< HEAD
//amd draw player base on new position (hide the old and draw the new one)
//dir: 'u' for move up, 'd' for move down
//render: render for draw and hide
void Player::Move(char dir)
{
	//hide old one
	Hide();

	//calcualte new position
	if (dir == 'u')
=======
//dir: 'l' for move left, 'r' for move right
void Player::Move(char dir)
{
	if (dir == 'l')
>>>>>>> parent of ae03b0e... Merge pull request #5 from viplazylmht/PlayerObject
	{
		_pos.x -= _speed;
	}
	else if (dir == 'r')
	{
		_pos.x += _speed;
	}
<<<<<<< HEAD

	_rect.y = _pos.y;

	//draw new one
	Draw();
=======
>>>>>>> parent of ae03b0e... Merge pull request #5 from viplazylmht/PlayerObject
}

//Description: show player to the board
void Player::Draw()
{
<<<<<<< HEAD
	SDL_SetRenderDrawColor(_render, 0, 0, 255, 255);


	SDL_RenderFillRect(_render, &_rect);


	SDL_SetRenderDrawColor(_render, 0, 0, 255, 255);

	SDL_RenderFillRect(_render, &rect);

	SDL_RenderPresent(_render);
}

//Description: hide player
void Player::Hide()
{
	//draw black rectangle
	SDL_SetRenderDrawColor(_render, 0, 0, 0, 255);

	SDL_RenderFillRect(_render, &_rect);
	SDL_RenderFillRect(_render, &rect);

	SDL_RenderPresent(_render);
}

//Description: create a player with pos (0, 0) and all default value (can use for 1280x720)
=======
	//do something
}


>>>>>>> parent of ae03b0e... Merge pull request #5 from viplazylmht/PlayerObject
Player::Player()
{

	//backend
	_render = nullptr;
	_pos.x = 0;
	_pos.y = 0;
<<<<<<< HEAD
	_length = DEFAULT_LENGTH;
	_width = DEFAULT_WIDTH;
	_speed = DEFAULT_SPEED;
=======
	_length = 0;
	_width = 0;
	_speed = 0;
>>>>>>> parent of ae03b0e... Merge pull request #5 from viplazylmht/PlayerObject
	_id = 0;

	//fontend
	_rect.x = _pos.x;
	_rect.y = _pos.y;
	_rect.h = _length;
	_rect.w = _width;

}

<<<<<<< HEAD
PlayerObject
//Description: create a player with given pos and id. All remain use default value (can use for 1280x720)

Player::Player(Point pos, int id, SDL_Renderer* render)
{
	//backend
	_pos = pos;
	_length = DEFAULT_LENGTH;
	_width = DEFAULT_WIDTH;
	_speed = DEFAULT_SPEED;
	_id = id;
PlayerObject

	//fontend
	_render = render;
	_rect.x = _pos.x;
	_rect.y = _pos.y;
	_rect.h = _length;
	_rect.w = _width;

	_render = render;

}

Player::Player(Point pos, int length, int width, int speed, int id, SDL_Renderer* render)
=======
Player::Player(Point pos, int length, int width, int speed, int id)
>>>>>>> parent of ae03b0e... Merge pull request #5 from viplazylmht/PlayerObject
{
	//backend
	_pos = pos;
	_length = length;
	_width = width;
	_speed = speed;
	_id = id;

	//fontend
	_render = render;
	_rect.x = _pos.x;
	_rect.y = _pos.y;
	_rect.h = _length;
	_rect.w = _width;

	_render = render;

}

Player::~Player()
{
	//do something
}