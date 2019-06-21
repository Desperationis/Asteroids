#include "Spaceship.h"

Spaceship::Spaceship(int x_, int y_)
{
	x = (float)x_; 
	y = (float)y_;
	scr.x = scr.y = 0;
	scr.w = scr.h = 16;
	GetRect(dest.x, dest.y, 40, 40); //sets variables such as left, right, ect.
}



void Spaceship::render()
{
	for (unsigned int i = 0; i < bullets.size(); i++) {
		bullets[i].render();
	}
	TM::DrawTextureEx(EntityManager::spritesheet, dest, scr,SDL_FLIP_NONE, angle + 90);
	Rect::DrawRect(dest, 255, 0, 0);
}

void Spaceship::update()
{
	int offset = 0;
	getInput();


	if (thrust) {
		dx += (float)cos(angle*DEGTORAD) * SPACESHIP::MOVEMENT_SPEED;
		dy += (float)sin(angle*DEGTORAD) * SPACESHIP::MOVEMENT_SPEED;
	}
	else { 
		dx *= SPACESHIP::DRIFT; dy *= SPACESHIP::DRIFT; 
	}
	x += dx; y += dy;
	dest.x = (int)x; dest.y = (int)y;

	hinderSpeed();
	loopAround();
	UpdateRect();

	for (unsigned int i = 0; i < bullets.size(); i++) {
		bullets[i - offset].update();

		if (bullets[i - offset].hasDied()) {
			bullets.erase(bullets.begin() + i - offset);
			offset++;
		}
	}
}

void Spaceship::getInput()
{
	if (Game::input.keys[SDL_SCANCODE_RIGHT]) angle += 5;
	if (Game::input.keys[SDL_SCANCODE_LEFT]) angle -= 5;
	if (Game::input.keys[SDL_SCANCODE_UP]) thrust = true;
	else thrust = false;

	if (Game::input.keys[SDL_SCANCODE_SPACE] && !spacePressed)
	{
		bullets.push_back(Bullet(center[0], center[1],
			((float)cos(angle*DEGTORAD) * SPACESHIP::MOVEMENT_SPEED * (float)BULLET::BULLET_SPEED) + dx,
			((float)sin(angle*DEGTORAD) * SPACESHIP::MOVEMENT_SPEED * (float)BULLET::BULLET_SPEED) + dy, angle + 90));
	}
	spacePressed = Game::input.keys[SDL_SCANCODE_SPACE];
	if (Game::input.keys[SDL_SCANCODE_SPACE] && spacePressed) {
		if (checkTimeInterval(300))
		{
			bullets.push_back(Bullet(center[0], center[1], 
			((float)cos(angle*DEGTORAD) * SPACESHIP::MOVEMENT_SPEED * (float) BULLET::BULLET_SPEED) + dx, 
			((float)sin(angle*DEGTORAD) * SPACESHIP::MOVEMENT_SPEED * (float)BULLET::BULLET_SPEED) + dy, angle + 90));
		}
	}
}
void Spaceship::hinderSpeed()
{
	float speed = sqrt((dx * dx) + (dy * dy));
	if (speed > SPACESHIP::MAX_SPEED)
	{
		dx *= SPACESHIP::MAX_SPEED / speed;
		dy *= SPACESHIP::MAX_SPEED / speed;
	}
}
bool Spaceship::checkTimeInterval(int timer)
{
	now = (Uint64)SDL_GetTicks();
	int timeElapsed = (int)(now - then);
	if (timeElapsed > timer)
	{
		then = now;
		return true;
	}
	return false;
}
void Spaceship::loopAround()
{
	if (left > (int)CONSOLE::WINDOW_WIDTH) {
		x = (0 - width);
		UpdateRect();
	}
	else if (right < 0) {
		x = (int)CONSOLE::WINDOW_WIDTH;
		UpdateRect();
	}
	if (top > (int)CONSOLE::WINDOW_HEIGHT)
	{
		y = (1 - height);
	}
	else if (bottom < 0) {
		y = (int)CONSOLE::WINDOW_HEIGHT;
	}
}