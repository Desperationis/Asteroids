#include "FontSystem.h"

void FontSystem::setUp(Font& font, const char* file, int ptsize) {
	font.font = TTF_OpenFont(file, ptsize);
}

void FontSystem::setText(Font& font, const char* text) {
	SDL_Surface* tmp = TTF_RenderText_Solid(font.font, text, font.fontColor);

	if (font.textureLoaded) {
		SDL_DestroyTexture(font.fontTexture);
	}
	font.fontTexture = SDL_CreateTextureFromSurface(Game::renderer, tmp);
	SDL_FreeSurface(tmp); tmp = nullptr;
	SDL_QueryTexture(font.fontTexture, NULL, NULL, &font.fontDest.w, &font.fontDest.h);
	font.textureLoaded = true;
}