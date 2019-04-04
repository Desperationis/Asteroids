#include "Button.h"

void Button::render() {
	SDL_SetRenderDrawColor(Game::renderer, bg_color.r, bg_color.g, bg_color.b, bg_color.a);
	SDL_RenderFillRect(Game::renderer, &dest);

	if (font.textureLoaded) {
		TM::DrawTexture(font.texture, font.dest);
	}
	if (textureLoaded) {
		TM::DrawTexture(texture, dest);
	}
}