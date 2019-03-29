#pragma once
#include "../../Entities/EntityManager.h"

struct Font {
	TTF_Font* font;
	SDL_Color color{ 255,255,255,255 };
	SDL_Texture* texture;
	SDL_Rect dest;
	bool textureLoaded = false;
};

class FontSystem {
public:

	static void setUp(Font& font, const char* file, int ptsize);
	static void setText(Font& font, const char* text, SDL_Color& color);
};