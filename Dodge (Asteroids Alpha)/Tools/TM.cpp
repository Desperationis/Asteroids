#pragma once
#include "stdafx.h"
#include "TM.h"

//Basic Rendering Capabilities
void TM::DrawTexture(SDL_Texture*& texture, SDL_Rect& dest, SDL_Rect& scr){
	SDL_RenderCopy(Game::renderer, texture, &scr, &dest);
}
void TM::DrawTexture(SDL_Texture*& texture, SDL_Rect& dest){
	SDL_RenderCopy(Game::renderer, texture, NULL, &dest);
}
void TM::DrawTexture(SDL_Texture*& texture) { SDL_RenderCopy(Game::renderer, texture, NULL, NULL); }

//Complex Rendering Capabilities

void TM::DrawTextureEx(SDL_Texture*& texture, SDL_Rect& dest, SDL_Rect& scr, SDL_RendererFlip SDL_Flip,SDL_Point& p,  double angle = 0.0)
{
	SDL_RenderCopyEx(Game::renderer, texture, &scr, &dest, angle, &p, SDL_Flip);
}

void TM::DrawTextureEx(SDL_Texture*& texture, SDL_Rect& dest, SDL_Rect& scr, SDL_RendererFlip SDL_Flip, double angle = 0.0)
{
	SDL_RenderCopyEx(Game::renderer, texture, &scr, &dest, angle, NULL, SDL_Flip);
}

void TM::DrawTextureEx(SDL_Texture*& texture, SDL_Rect& dest, SDL_RendererFlip SDL_Flip, double angle = 0.0)
{
	SDL_RenderCopyEx(Game::renderer, texture, NULL, &dest, angle, NULL , SDL_Flip);
}



//Loading Capabilities

SDL_Texture* TM::LoadTexture(const char* texture)
{
	SDL_Surface* temp = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, temp);
	SDL_FreeSurface(temp);
	return tex;
}

SDL_Texture* TM::LoadBWTexture(const char* texture)
{
	SDL_Surface* tmp = IMG_Load(texture);
	if (tmp != NULL)
	{
		tmp = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_ARGB8888, 0);
		SDL_Texture* tex = SDL_CreateTexture(Game::renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, tmp->w, tmp->h);


		Uint32 * pixels = static_cast<Uint32*>(tmp->pixels);
		for (int y = 0; y < tmp->h; y++)
		{
			for (int x = 0; x < tmp->w; x++)
			{
				Uint32 pixel = pixels[y * tmp->w + x];
				Uint8 r = pixel >> 16 & 0xFF;
				Uint8 g = pixel >> 8 & 0xFF;
				Uint8 b = pixel & 0xFF;
				Uint8 v = 0.212671f * r
					+ 0.715160f * g
					+ 0.072169f * b;
				pixel = (0xFF << 24) | (v << 16) | (v << 8) | v;
				pixels[y * tmp->w + x] = pixel;
			}
		}

		SDL_UpdateTexture(tex, NULL, tmp->pixels, tmp->w * sizeof(Uint32));
		SDL_FreeSurface(tmp);

		return tex;
	}
}

//Blending Capabilities

void TM::SetAlphaBlending(SDL_Texture*& texture)
{
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
}
void TM::RemoveAlphaBlending(SDL_Texture*& texture)
{
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE);
}
void TM::SetAlpha(SDL_Texture*& texture, Uint8 alpha)
{
	SDL_SetTextureAlphaMod(texture, alpha);
}

//Altering Capabilities

void TM::SetColorMod(SDL_Texture*& texture, Uint8 R, Uint8 G, Uint8 B)
{
	SDL_SetTextureColorMod(texture, R, G, B);
}
