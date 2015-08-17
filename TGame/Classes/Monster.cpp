#include "Monster.h"
#include <string>
#include "MainScene.h"
#include "json/rapidjson.h" 
#include "json/document.h"
using namespace std;
bool Monster::init(int level)
{
	auto num = String::createWithFormat("sprite/monster/monster_%d.png", level);
	this->initWithFile(num->_string);//根据怪物的等级创建不同的怪物
	Vector<SpriteFrame*> vecSp;
	startNum = 0;//出生点下标
	speed = 1;//移动速度
	distancePos = Vec2(0,0);
	//添加血条
	blood = Blood::create(1);
	blood->pt->setPercentage(100.0f);
	blood->setPositionX(getPositionX()+getContentSize().width/2);
	blood->setPositionY( getPositionY()+getContentSize().height+5);
	addChild(blood);
	this->schedule(schedule_selector(Monster::moveUpdate), 0.01f); 
	switch (level)
	{
	case 1:
		hp = 100;
		money = 10;
		break;
	case 2:
		hp = 150;
		money = 20;
		break;
	default:
		break;
	}
	return true;
}

Monster* Monster::create(int level)
{
	auto monster = new Monster();
	if (monster&&monster->init(level))
	{
		monster->autorelease();
		return monster;
	}
	else
	{
		delete monster;
		monster = NULL;
		return NULL;
	}
}

void Monster::moveUpdate(float dt)
{
	if (startNum == goalVec.size()-1)
		return;
	auto selfPos = getPosition();
	auto goalPos = goalVec.at(startNum + 1)->getPosition();
	auto finalPos = goalPos - selfPos;
	if (distancePos == Vec2(0, 0))
	{
		distancePos = goalPos-goalVec.at(startNum)->getPosition();
	}
	if (abs(finalPos.x) > abs(finalPos.y))
	{
		if (finalPos.x > 0)
		{
			setPositionX(getPositionX() + speed);
			if (distancePos.x < 0)
			{
				startNum += 1;
				distancePos = Vec2(0, 0);
				return;
			}
		}
		else if (finalPos.x<0)
		{
			if (distancePos.x > 0)
			{
				startNum += 1;
				distancePos = Vec2(0, 0);
				return;
			}
			setPositionX(getPositionX() - speed);
		}
		else if (finalPos.x == 0)
		{
			startNum += 1;
			distancePos = Vec2(0, 0);
		}
	}
	else
	{
		if (finalPos.y > 0)
		{
			setPositionY(getPositionY() + speed);
			if (distancePos.y < 0)
			{
				startNum += 1;
				distancePos = Vec2(0, 0);
				return;
			}
		}
		else if (finalPos.y<0)
		{
			setPositionY(getPositionY() - speed);
			if (distancePos.y > 0)
			{
				startNum += 1;
				distancePos = Vec2(0, 0);
				return;
			}
		}
		else if (finalPos.y == 0)
		{
			startNum += 1;
			distancePos = Vec2(0, 0);
		}
	}
}
