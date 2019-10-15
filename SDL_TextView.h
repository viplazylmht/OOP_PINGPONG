#pragma once
#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <fstream>


using namespace std;

class SDL_TextView
{
public:
	static const int SELECTED = 1;
	static const int IN_SELECTED = 2;

private:
	string _text;
	TTF_Font* _font;

	SDL_Color _color;
	SDL_Color _hightLightColor = { 255, 0, 0, 255 };
	SDL_Color _normalColor = { 0, 255, 0, 255 };
	SDL_Color _bgWhite = { 255, 255, 255, 255 };

	SDL_Surface* _surface;
	SDL_Texture* _texture;
	SDL_Rect _rect;
	SDL_Renderer* _renderer;

public:

	void Show();

	void SetText(string);
	void SetColor(SDL_Color);
	void SetColorShaded(SDL_Color, SDL_Color);
	void SetAlpha(char);
	void SetFlag(int);
	bool SetFont(string, int);
	SDL_TextView(SDL_Renderer* renderer, int x, int y, string text, int fontSize, string fontName);
	SDL_TextView(SDL_Renderer* renderer, int x, int y, string text, int fontSize);
	~SDL_TextView();


	void SetCenterX(int left, int right);
};

