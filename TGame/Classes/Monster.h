#pragma once
#include "cocos2d.h"
#include "Monster.h"
#include "Blood.h"
USING_NS_CC;

class Monster : public Sprite
{
public:
	static Monster* create(int level);
	bool init(int level);
	CC_SYNTHESIZE(int,speed,Speed);
	CC_SYNTHESIZE(Vector<Node*>,goalVec,GoalVec);
	CC_SYNTHESIZE(int, hp, Hp);
	CC_SYNTHESIZE(int, titlePosX, TitlePosX);
	CC_SYNTHESIZE(int, titlePosY, TitlePosY);
	CC_SYNTHESIZE(Blood*, blood, Blood);
	CC_SYNTHESIZE(int, money, Money);
	CC_SYNTHESIZE(int, startNum, StartNum);
	Animation* createAnimation(std::string prefixName, int framesNum, float delay);
private:
	void moveUpdate(float dt);
	Vec2 distancePos;
	bool getMonsterConfig();

};