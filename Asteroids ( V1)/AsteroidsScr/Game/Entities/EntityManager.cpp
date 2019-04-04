#include "EntityManager.h"
#include "Spaceship/Spaceship.h"
#include "Asteroids/NormalAsteroid.h"

SDL_Texture* EntityManager::spritesheet;

EntityManager::EntityManager()
{
	spritesheet = TM::LoadTexture("Assests\\MeteorsAssests.png");
	spaceship = new Spaceship(800,800);
	asteroid = new NormalAsteroid(900, 500);
}


void EntityManager::update()
{
	spaceship->update();
	asteroid->update(spaceship->bullets);
}


void EntityManager::render()
{
	spaceship->render();
	asteroid->render();
}