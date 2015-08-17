#include "Bullet.h"
bool Bullet::init()
{
	initWithSpriteFrameName("Star-11.png");
	speed = 5;
	attack = 20;
	return true;
	
}
