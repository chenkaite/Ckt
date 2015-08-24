#include "GameOverLayer.h"
#include "ObjectTag.h"
#include "MainScene.h"
bool GameOverLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	initWithColor(Color4B(112, 128, 144, 150), 800, 450);
	auto bg = Sprite::createWithSpriteFrameName("lose_bg.png");
	addChild(bg);
	bg->setPosition(getContentSize()/2);
	auto restart = Sprite::createWithSpriteFrameName("menu_restart_normal_CN.png");
	addChild(restart);
	restart->setPosition(getContentSize().width / 2, getContentSize().height / 2 - 50);
	auto et = EventListenerTouchOneByOne::create();
	et->onTouchBegan = [restart](Touch* t, Event* e)->bool
	{
		if (restart->getBoundingBox().containsPoint(t->getLocation()))
		{
			
			Director::getInstance()->getRunningScene()->removeAllChildrenWithCleanup(true);
			Director::getInstance()->getRunningScene()->removeAllComponents();
			Director::getInstance()->getRunningScene()->stopAllActions();
			auto scene = MainScene::createScene();
			Director::getInstance()->runWithScene(scene);
			Director::getInstance()->resume();
		}
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(et, this);
	return true;
}