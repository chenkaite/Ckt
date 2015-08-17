#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Bullet : public Sprite
{
public:
	virtual bool init();
	CREATE_FUNC(Bullet);
	CC_SYNTHESIZE(float,dt,Dt);
	CC_SYNTHESIZE(int, speed, Speed);
	CC_SYNTHESIZE(int, attack, Attack);

};