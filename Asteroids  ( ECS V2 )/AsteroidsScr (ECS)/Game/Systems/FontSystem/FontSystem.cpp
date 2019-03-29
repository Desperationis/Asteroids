#include "FontSystem.h"

void FontSystem::setUp(Font& font, const char* file, int ptsize) {
	font.font = TTF_OpenFont(file, ptsize);
}

void FontSystem::setText(Font& font, const char* text, SDL_Color& color) {
	SDL_Surface* tmp = TTF_RenderText_Solid(font.font, text, color);

	if (font.textureLoaded) {
		SDL_DestroyTexture(font.texture);
	}
	font.texture = SDL_CreateTextureFromSurface(Game::renderer, tmp);
	SDL_FreeSurface(tmp); tmp = nullptr;
	SDL_QueryTexture(font.texture, NULL, NULL, &font.dest.w, &font.dest.h);
	font.textureLoaded = true;
}