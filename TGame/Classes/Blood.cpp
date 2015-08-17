#include "Blood.h"
bool Blood::init(int type)
{
	switch (type)
	{
	case 1:
		bloodRect = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("MonsterHP02.png"));
		blood = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("MonsterHP01.png"));
		pt = ProgressTimer::create(blood);
		pt->setType(ProgressTimer::Type::BAR);
		pt->setPercentage(100.0f);
		pt->setMidpoint(Point(0, 1));
		pt->setBarChangeRate(Point(1, 0));
	
		
		break;
	case 2:
		
		break;
	}
	addChild(bloodRect, 0);
	addChild(pt, 2);
	return true;
}
Blood* Blood::create(int type)
{
	Blood* blood = new Blood();
	if (blood&&blood->init(type))
	{
		blood->autorelease();
		return blood; 
	}
	else
	{
		CC_SAFE_DELETE(blood);
		return nullptr;
	}
}