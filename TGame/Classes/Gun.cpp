#include "Gun.h"
#include "Bullet.h"
#include "MainScene.h"
bool Gun::init(int level)
{
	bullet = nullptr;
	fanwei = nullptr;
	firedMons = nullptr;
	sellSp = nullptr;
	updateSp = nullptr;
	firePosition = Vec2(0, 0);
	switch (level)
	{
	case 1:
		initWithSpriteFrameName("ss_towers_11.png");
		setLevel(1);
		speed = 0.4f;
		break;
	case 2:
		initWithSpriteFrameName("PStar31.png");
		attack = 20;
		speed = 0.4f;
		setLevel(2);
		startFrameNum = 11;
		frameName = "PStar";
		
		auto action = createAnimation(frameName, 5, 0.05f, startFrameNum);
		AnimationCache::getInstance()->addAnimation(action,"PStar");
		break;
	}
	return true;
}
Gun* Gun::create(int level)
{
	auto gun = new Gun();
	if (gun&&gun->init(level))
	{
		gun->autorelease();
		return gun;
	}
	else
	{
		CC_SAFE_DELETE(gun);
		return NULL;
	}
}
Animation* Gun::createAnimation(std::string prefixName, int framesNum, float delay,int startNum)
{
	Vector<SpriteFrame*> vec;
	for (int i = startNum; i < (framesNum+startNum); i++)
	{
		char buffer[20] = { 0 };
		sprintf(buffer, "-%d.png", i);
		std::string frameName = prefixName + buffer;
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
		vec.pushBack(frame);
	}
	return Animation::createWithSpriteFrames(vec,delay);
}
void Gun::fire()
{
	if (MainScene::mons->size()>1 && bullet == nullptr&&this->isRunning())
	{
		if (firePosition == Vec2(0, 0))
		{
			this->schedule(schedule_selector(Gun::updateFire), 0.5f);
			return;
		}
		this->unschedule(schedule_selector(Gun::updateFire));
		auto bullet = Bullet::create();
		auto layer = getParent();
		layer->addChild(bullet);
		bullet->setPosition(getPosition());
		MainScene::bullets->pushBack(bullet);
		auto func = CallFuncN::create(CC_CALLBACK_0(Gun::fire, this));
		auto func2 = CallFuncN::create(CC_CALLBACK_1(Gun::getFireMonsters, this));
		auto boom = Animate::create(AnimationCache::getInstance()->getAnimation("PStar"));
		MoveTo* move = MoveTo::create(speed, firePosition);
		auto sq = Sequence::create(move, boom, CCCallFunc::create([&, bullet]
		{
			bullet->removeFromParent();
		}), func2,func, NULL);
		bullet->runAction(sq);
	}


}
void Gun::getFireMonsters(bool isTrue)
{
	if (isRunning())
	{
		Vec2 nowPos = Vec2(0, 0);
		for (int i = 0; i < MainScene::mons->size(); i++)
		{
			if (this != nullptr)
			{
				auto monster = MainScene::mons->at(i);
				auto mosPos = monster->getPosition();
				if (fanwei != nullptr&&fanwei->getBoundingBox().intersectsRect(monster->getBoundingBox()))
				{
					if (monster->getBlood()->pt->getPercentage() > 0)
					{
						nowPos = monster->getPosition();
						firePosition = monster->getPosition();
						log("%d", i);
						return;
					}
				}
				if (i == MainScene::mons->size())
				{
					log("end");
					firePosition = Vec2(0, 0);
				}
			}
		}
		firePosition = Vec2(0, 0);
	}
}
void Gun::updateFire(float dt)
{
	if (MainScene::mons->size() > 0 && MainScene::guns->size() > 0)
	{
		if (this->isRunning())
			getFireMonsters(true);
		else
			return;
		if (firePosition!=Vec2(0,0))
		{
			fire();
		}
	}
}
