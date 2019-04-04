#include "NormalAsteroid.h"


NormalAsteroid::NormalAsteroid(int x, int y)
{
	dest.x = this->x = x;
	dest.y = this->y = y;
	dest.w = 50; dest.h = 50;

	float randomAngle = rand() % 360;
	dx = (float)cos(randomAngle * DEGTORAD) * 5.0f;
	dy = (float)sin(randomAngle * DEGTORAD) * 5.0f;
	std::cout << randomAngle << std::endl;
}

void NormalAsteroid::update(std::vector<Bullet> bullets)
{
	x += dx; y += dy;
	dest.x = x; dest.y = y;
	UpdateRect();
	if (left > (int)CONSOLE::WINDOW_WIDTH) {
		x = (0 - width);
		UpdateRect();
	}
	else if (right < 0) {
		x = (int)CONSOLE::WINDOW_WIDTH;
		UpdateRect();
	}
	if (top > (int)CONSOLE::WINDOW_HEIGHT) {
		y = (1 - height);
	}
	else if (bottom < 0) {
		y = (int)CONSOLE::WINDOW_HEIGHT;
	}
}

void NormalAsteroid::render()
{
	FillRect(dest,255,255,255);
}


