#include "Bullet.h"


Bullet::Bullet(int x_, int y_, float dx, float dy, double angle)
{
	x = (float)x_;
	y = (float)y_;
	scr.x = 16 * 5; scr.y = 0;
	scr.w = scr.h = 16;
	GetRect(x_ - 2, y_ - 10, 5, 5); //spawn the center at location

	this->dx = dx; this->dy = dy;
	this->angle = angle;
}

void Bullet::render()
{
	TM::DrawTextureEx(EntityManager::spritesheet, dest, scr, SDL_FLIP_NONE, angle);
}

void Bullet::update()
{
	x += dx; y += dy;
	dest.x = (int)x; dest.y = (int)y;

	UpdateRect();

	dead = center[0] > (int)CONSOLE::WINDOW_WIDTH || center[0] < 0 || center[1] > (int)CONSOLE::WINDOW_HEIGHT || center[1] < 0;
}
