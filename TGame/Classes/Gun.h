#pragma once
#include "cocos2d.h"
#include "Bullet.h"
#include "Monster.h"
#include "Bullet.h"
USING_NS_CC;

class Gun : public Sprite
{
public:
	virtual bool init(int level);
	static Gun* create(int level);
	Animation* createAnimation(std::string prefixName, int framesNum, float delay,int startNum);
	void fire();
	void updateFire(float dt);
	void fireMove(float dt);
	void addFanwei();
	void getFireMonsters(bool isTrue);
public:
	Vec2 firePosition;
	Monster* firedMons;
	int fireNum;
	Bullet* bullet;
	CC_SYNTHESIZE(Sprite*, sellSp, SellSp);
	CC_SYNTHESIZE(Sprite*, updateSp, UpdateSp);
	CC_SYNTHESIZE(Sprite*, fanwei, Fanwei);
	CC_SYNTHESIZE(int, level, Level);
	CC_SYNTHESIZE(float, speed, Speed);
	CC_SYNTHESIZE(int, attack, Attack);
	CC_SYNTHESIZE(Vector<Monster*>, monster, Monster);
	Vector<Bullet*> vector_bullet;
	
private:
	int startFrameNum;
	std::string frameName;
private:
	
	
};