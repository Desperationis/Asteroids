#pragma once
#include "../../Entities/EntityManager.h"

struct Font {
	TTF_Font* font;
	SDL_Color fontColor{ 255,255,255,255 };
	SDL_Texture* fontTexture;
	SDL_Rect fontDest;
	bool textureLoaded = false;
};

class FontSystem {
public:

	static void setUp(Font& font, const char* file, int ptsize);
	static void setText(Font& font, const char* text);
};