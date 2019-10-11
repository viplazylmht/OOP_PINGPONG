#pragma once
#include "LibGame.h"
#include <math.h>
#include <random>
#include <time.h>   //for random
#define SDL_MAIN_HANDLED

#include <SDL.h>


class Ball
{
// CONST VALUE
public:
	// const for check collide
	static const int BORDER_LEFT = 1;
	static const int BORDER_RIGHT = 2;
	static const int BORDER_TOP = 3;
	static const int BORDER_BOTTOM = 4;
	static const int BORDER_CORNER = 5;

	// const for speed per FPS
	static const int MAX_SPEED = 25;

private:
	// Position
	Point _center;
	int _radius;


	// SDL windows
	SDL_Renderer* _render;

	// Vector speed
	float _i;
	float _j;

	float _speed;


// private method
private:
	void SyncSpeed();

// Getter and Setter
public:
	Point Center() { return _center; };
	int Radius() { return _radius; };

	float AxisI() { return _i; };
	float AxisJ() { return _j; };
	int Speed() { return (int)_speed; };

	void SetCenter(Point);
	void SetCenter(int, int);
	void SetRadius(int);
	void SetAxisI(int);
	void SetAxisJ(int);

// method
public:

	// Description: Directional the vector speed to right way 
	bool Collide(int);

	// Description: Make the ball move one step 
	void Move();

	// Description: Show the ball to the board 
	void Draw();

	// Description: Hide the ball
	void Hide();
	
	// Description: Increase speed of the ball
	void LevelUp();

// constructor and destructor
public:

	// Description: Default init
	Ball();

	// Description: Init tha ball with default pos, radius and vector speed
	Ball(SDL_Renderer* render, Point firstLocation, int radius);
};

// Description: Create and fill a cricle with given RGBA color 
void fill_circle(SDL_Renderer*, int, int, int, Uint8, Uint8, Uint8, Uint8);

//Desctiption: Random axits for ball
void RandIandJ(float& i, float& j);