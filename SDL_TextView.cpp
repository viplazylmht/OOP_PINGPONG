#include "SDL_TextView.h"

void SDL_TextView::Show()
{
	SDL_RenderCopy(_renderer, _texture, NULL, &_rect);
}

void SDL_TextView::SetText(string text)
{
	_text = text;

	SetColor(_color);
}

void SDL_TextView::SetColor(SDL_Color color)
{
	_color = color;
	
	// reinit surface
	SDL_FreeSurface(_surface);
	_surface = TTF_RenderText_Solid(_font, _text.c_str(), _color);
	_texture = SDL_CreateTextureFromSurface(_renderer, _surface);

	SetAlpha(_color.a);
}

void SDL_TextView::SetColorShaded(SDL_Color fg, SDL_Color bg)
{
	_color = fg;
	// reinit surface in Shaded mode
	SDL_FreeSurface(_surface);
	_surface = TTF_RenderText_Shaded(_font, _text.c_str(), fg, bg);
	_texture = SDL_CreateTextureFromSurface(_renderer, _surface);

	SetAlpha(_color.a);
}

void SDL_TextView::SetAlpha(char alpha)
{
	SDL_SetTextureAlphaMod(_texture, alpha);
}

void SDL_TextView::SetFlag(int MODE)
{
	switch (MODE)
	{
	case SELECTED: {
		SetColorShaded(_hightLightColor, _bgWhite);
		break;
	}
	case IN_SELECTED:
	{
		SetColor(_normalColor);
		break;
	}
	default:
		break;
	}
}

bool SDL_TextView::SetFont(string fontName, int fontSize)
{
	// Check if wrong path font cause of Open direct execute program in Output folder instead of Visual Studio
	ifstream f(fontName, ios::in);
	if (f.fail()) {

		// redirect to prev folder that contains font
		fontName = "..\\" + fontName;
	}
	else {
		f.close();
	}

	// Initalize new draw font for SDL_TTF
	_font = TTF_OpenFont(fontName.c_str(), fontSize);
	if (!_font) {
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		return false;
	}
	return true;
}

void SDL_TextView::SetCenterX(int left, int right)
{
	int mainWidth = (right - left);
	int spaceLeft = mainWidth - _rect.w;
	
	//set x for _rect
	_rect.x = left + spaceLeft / 2;
}

SDL_TextView::SDL_TextView(SDL_Renderer* renderer,int x, int y, string text, int fontSize, string fontName)
{
	SetFont(fontName, fontSize);
	_text = text;

	_rect.x = x;
	_rect.y = y;

	// Get width, height of a given text
	int w, h;
	TTF_SizeText(_font, _text.c_str(), &w, &h);
	_rect.w = w;
	_rect.h = h;

	_color = _normalColor;

	_renderer = renderer;
	_surface = TTF_RenderText_Solid(_font, _text.c_str(), _color);
	_texture = SDL_CreateTextureFromSurface(_renderer, _surface);


}

SDL_TextView::SDL_TextView(SDL_Renderer* renderer, int x, int y, string text, int fontSize)
{
	// Default font
	string fontName = "Lib\\font\\VeraMoBd.ttf";
	SetFont(fontName, fontSize);
	
	_text = text;

	_rect.x = x;
	_rect.y = y;

	// Get width, height of a given text
	int w, h;
	TTF_SizeText(_font, _text.c_str(), &w, &h);
	_rect.w = w;
	_rect.h = h;


	_color = _normalColor;

	_renderer = renderer;
	_surface = TTF_RenderText_Solid(_font, _text.c_str(), _color);
	_texture = SDL_CreateTextureFromSurface(_renderer, _surface);
}

SDL_TextView::~SDL_TextView()
{
	if (!_texture) SDL_DestroyTexture(_texture);
	if (!_surface) SDL_FreeSurface(_surface);
}