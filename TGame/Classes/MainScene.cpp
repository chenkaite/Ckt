#include "MainScene.h"
#include "ObjectTag.h"
#include <cmath> 
#include "Blood.h"
#include "GameOverLayer.h"
using namespace cocostudio::timeline;
using namespace std;
Vector<Gun*> *MainScene::guns = new Vector<Gun*>();
Vector<Monster*> *MainScene::mons = new Vector<Monster*>();
Vector<Bullet*> *MainScene::bullets = new Vector<Bullet*>();
Scene* MainScene::createScene()
{
    auto scene = Scene::create();
	auto mainLayer = MainScene::create();
	scene->addChild(mainLayer,MainLayerTag);
    return scene;
}

bool MainScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	
	isDoubleSpeed = false;
	mons->clear();
	guns->clear();
	bullets->clear();
	auto size = Director::getInstance()->getVisibleSize();
	bloodIndex = 4;//Ѫ��ͼƬ�ڼ����е��±�
	copyMonsSpeed = 20;//��������ʱ����
	money = 100;//�������
	fanwei = nullptr;//����������Χ
	moveTime = 0;//��������ʱ���ʱ����ʼ��
	addCache();//���ͼƬ����
	addBg();//��ӱ���
	addAnything();//�������
	auto listen = EventListenerTouchOneByOne::create(); //��ӵ��㴥��
	listen->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this);
	listen->onTouchMoved = CC_CALLBACK_2(MainScene::onTouchMoved, this);
	listen->onTouchEnded = CC_CALLBACK_2(MainScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listen, this);
	schedule(schedule_selector(MainScene::moveUpdate), 0.1f);
    return true;
}
void MainScene::addBg()
{
	auto bg = Background::create();//����ͼƬ
	addChild(bg);//��ӱ���ͼƬ������
	bg->setTag(BackGroundInfo);
	bg->setPosition(bg->getContentSize() / 2);//���ñ�������
	vectorMove = getMoveVec("move1");//�õ������ƶ������б�
	touchingGun = nullptr;//ѡ�е�����
	gunPos = bg->mapInfo->getLayer("gunPos");//�õ�����������
	gunPos->setVisible(false);
}
void MainScene::moveUpdate(float dt)
{
	moveTime++;
	if (bloodIndex == -1)//��Ѫ��Ϊ0ʱ������Ϸ����ҳ��
	{
		if (getChildByTag(GameOverTag) == nullptr)
		{
			auto gameOverLayer = GameOverLayer::create();
			addChild(gameOverLayer, GameOverTag);
			Director::getInstance()->pause();
		}
		else
		{
			Director::getInstance()->resume();
			removeChildByTag(GameOverTag);
		}
		
	}
	if (moveTime >= copyMonsSpeed)//���ɹ���
	{
		auto mons2 = Monster::create(2);
		if (isDoubleSpeed)
			mons2->setSpeed(mons2->getSpeed()*2);
		mons2->setPosition(vectorMove.at(0)->getPosition());
		addChild(mons2);
		mons2->setGoalVec(vectorMove);
		mons->pushBack(mons2);
		moveTime = 0;
	}
	for (auto i =0; i < mons->size();i++)//ˢ�½�Ǯ����
	{
		if (mons->at(i)->getBlood()->pt->getPercentage() <= 0&&mons->at(i)->isVisible())
		{
			money += mons->at(i)->getMoney();
			char countBuf[16] = "";
			sprintf(countBuf, "%d", money);
			String cs = countBuf;
			auto moneyNum = cs.getCString();
			static_cast<Label*>(getChildByTag(MoneyLabel))->setString(moneyNum);
			mons->at(i)->setVisible(false);
		}
	}
	for (auto i = 0; i < mons->size(); i++)
	{
		auto item = mons->at(i);
		if (item->getStartNum()==vectorMove.size()-1)
		{
			if (item->isVisible())//��һ�����ŵĹ����ߵ��յ�ʱ��Ѫ����1
			{
				bloodIndex -= 1;
			}
			mons->eraseObject(item);
			item->removeFromParent();
			if (bloodIndex >= 0)//�л�Ѫ��ͼƬ
			{
				static_cast<Sprite*>(getChildByTag(SelfBloodSprite))->setSpriteFrame(bloodPics.at(bloodIndex));
			}
		}
	}
	for (int i = 0; i < bullets->size(); i++)//����ӵ��Ƿ����Ŀ��
	{
		for (int a = 0; a < mons->size(); a++)
		{
			auto item = mons->at(a);
			if (bullets->at(i)->getBoundingBox().intersectsRect(item->getBoundingBox()))
			{
				item->getBlood()->pt->setPercentage(item->getBlood()->pt->getPercentage()-bullets->at(i)->getAttack());
				bullets->eraseObject(bullets->at(i));
				return;
			}
		}
	}
}

Vector<Node*> MainScene::getMoveVec(const std::string &name)
{
	auto bg = static_cast<Background*>(getChildByTag(BackGroundInfo));
	auto moveBg = bg->mapInfo->getObjectGroup(name);
	auto obj = moveBg->getObjects();
	Vector < Node* > vec;
	for (auto item : obj)
	{
		auto map = item.asValueMap();
		auto x = map["x"].asInt();
		auto y = map["y"].asInt();
		auto node = Node::create();
		node->setPositionX(x);
		node->setPositionY(y);
		vec.pushBack(node);
	}
	return vec;
}
bool MainScene::canSetGun(Vec2 position,Rect rect)
{
	if (gunPos->getTileAt(getPos(position))!=nullptr)
	{
			for (int i = 0; i < guns->size(); i++)
			{
				if (guns->at(i)->getBoundingBox().intersectsRect(rect))
				{
					return false;
				}
			}
			return true;
	}
	return false;
}
Point MainScene::getPos(Point p)
{
	auto bg = static_cast<Background*>(getChildByTag(BackGroundInfo));
	int x = p.x / bg->mapInfo->getTileSize().width;
	int y = (bg->mapInfo->getMapSize().height * 10 - p.y) / bg->mapInfo->getTileSize().height;
	return Point(x, y);
}
void MainScene::addAnything()
{
	auto size = Director::getInstance()->getVisibleSize();
	auto org = Director::getInstance()->getVisibleOrigin();
	//Ѫ��ͼƬ1-9
	for (int i = 1; i < 10; i++)
	{
		char buffer[20] = {0};
		sprintf(buffer,"%d.png",i);
		std::string s = "BossHP0";
		std::string sb = s + buffer;
		auto sp = SpriteFrameCache::getInstance()->getSpriteFrameByName(sb);
		bloodPics.pushBack(sp);
	}
	auto sp = Sprite::createWithSpriteFrameName("MenuBG.png");//�����������
	addChild(sp);
	sp->setPosition(Director::getInstance()->getVisibleSize().width/2,(Director::getInstance()->getVisibleSize().height)-(sp->getContentSize().height/2));
	auto gun2 = Gun::create(2);
	gun2->setPosition(org.x+40, (Director::getInstance()->getVisibleSize().height) - (sp->getContentSize().height / 2)+5);
	addChild(gun2);
	gunPics.pushBack(gun2);//��ӵ�����ͼƬ��
	//��Ǯ����
	char countBuf[16] = "";
	sprintf(countBuf, "%d", money);
	String cs = countBuf;
	auto moneyNum = cs.getCString();
	auto moneyLabel = Label::createWithTTF(moneyNum, "gameFont.ttf", 30);
	addChild(moneyLabel);
	moneyLabel->setTag(MoneyLabel);
	moneyLabel->setPosition(org.x + 180, size.height - moneyLabel->getContentSize().height / 2);
	//�Լ�Ѫ��
	auto selfBlood = Sprite::createWithSpriteFrame(bloodPics.at(bloodIndex));
	selfBlood->setPosition((sp->getPositionX()+sp->getContentSize().width/2)-selfBlood->getContentSize().width,sp->getPositionY()+5);
	addChild(selfBlood);
	selfBlood->setTag(SelfBloodSprite);
	//��Ӳ˵���ť
	menuSp = Sprite::createWithSpriteFrameName("menu02.png");
	addChild(menuSp);
	menuSp->setPosition(size - menuSp->getContentSize() / 2);
	//��Ӽ��ٰ�ť
	auto speed = Sprite::createWithSpriteFrameName("speed11.png");
	addChild(speed);
	speed->setTag(SpeedButoon);
	speed->setPositionX(selfBlood->getPositionX() - speed->getContentSize().width );
	speed->setPositionY(selfBlood->getPositionY()-7);
}
void MainScene::addCache()
{
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("TStar-hd.plist", "TStar-hd.png");
	cache->addSpriteFramesWithFile("Items00-hd.plist", "Items00-hd.png");
	cache->addSpriteFramesWithFile("Items02-hd.plist", "Items02-hd.png");
	cache->addSpriteFramesWithFile("gamemenu-hd.plist", "gamemenu-hd.png");
	cache->addSpriteFramesWithFile("gameover0-hd.plist", "gameover0-hd.png");
	cache->addSpriteFramesWithFile("Monsters02-hd.plist", "Monsters02-hd.png");
	cache->addSpriteFramesWithFile("stages_theme3-hd.plist", "stages_theme3-hd.png");
}
void MainScene::doubleSpeed()
{
	if (!isDoubleSpeed)
	{
		auto ss = (Sprite*)getChildByTag(SpeedButoon);
		ss->setSpriteFrame("speed22.png");
		isDoubleSpeed = true;
		copyMonsSpeed = copyMonsSpeed / 2;

		for (int i = 0; i < mons->size(); i++)
		{
			auto item = mons->at(i);
			item->setSpeed(item->getSpeed() * 2);
		}
		for (int i = 0; i < guns->size(); i++)
		{
			auto item = guns->at(i);
			item->setSpeed(item->getSpeed() / 2);
		}
	}
	else
	{
		auto ss = (Sprite*)getChildByTag(SpeedButoon);
		ss->setSpriteFrame("speed11.png");
		isDoubleSpeed = false;
		copyMonsSpeed = copyMonsSpeed * 2;
		for (int i = 0; i < mons->size(); i++)
		{
			auto item = mons->at(i);
			item->setSpeed(item->getSpeed() / 2);
		}
		for (int i = 0; i < guns->size(); i++)
		{
			auto item = guns->at(i);
			item->setSpeed(item->getSpeed() * 2);
		}
	}
}
bool MainScene::onTouchBegan(Touch* t, Event* e)
{
	auto speedBt = (Sprite*)getChildByTag(SpeedButoon);
	if (speedBt->getBoundingBox().containsPoint(t->getLocation()))//˫���ٶ�
	{
		doubleSpeed();
	}
	if (menuSp->getBoundingBox().containsPoint(t->getLocation()))//�˵���ť
	{
		if (getChildByTag(PauseLayerTag) == nullptr)
		{
			auto layer = PauseLayer::create();
			addChild(layer, 50, PauseLayerTag);
		}
		else
		{
			removeChildByTag(PauseLayerTag);
		}
	}
	for (auto i = 0; i < gunPics.size(); i++)
	{
		//�жϴ������Ƿ�����������
		if (gunPics.at(i)->getBoundingBox().containsPoint(t->getLocation()))
		{
			//��������֮�������
			touchingGun = Gun::create(gunPics.at(i)->getLevel());
			touchingGun->setOpacity(150);
			touchingGun->setPosition(gunPics.at(i)->getPosition());
			addChild(touchingGun);
			//��ӷ�ΧȦȦ
			fanwei = Sprite::createWithSpriteFrameName("range_100.png");
			fanwei->setPosition(touchingGun->getPosition());
			addChild(fanwei);
			if (isDoubleSpeed)
				touchingGun->setSpeed(touchingGun->getSpeed() / 2);
			break;
		}
	}
	for (int i = 0; i < guns->size(); i++)//���������������ť
	{
		auto gun = guns->at(i);
		if (gun->getFanwei()->isVisible())
		{
			if (gun->getSellSp()->getBoundingBox().containsPoint(t->getLocation()))
			{
				gun->getSellSp()->removeFromParent();
				gun->getUpdateSp()->removeFromParent();
				gun->getFanwei()->setVisible(false);
				gun->setVisible(false);
				return false;
			}
			else if (gun->getUpdateSp()->getBoundingBox().containsPoint(t->getLocation()))
			{
				log("update");
				return false;
			}
		}
		if (gun->getBoundingBox().containsPoint(t->getLocation()))
		{
			if (!gun->getFanwei()->isVisible())
			{
				if (gun->getSellSp() == nullptr)
				{
					auto sellSp = Sprite::createWithSpriteFrameName("sell_128.png");
					sellSp->setPosition(gun->getPositionX() + sellSp->getContentSize().width, gun->getPositionY());
					gun->setSellSp(sellSp);
					sellSp->setScale(0.8f);
					addChild(sellSp);
					auto updateSp = Sprite::createWithSpriteFrameName("upgrade_180.png");
					updateSp->setScale(0.8f);
					gun->setUpdateSp(updateSp);
					updateSp->setPosition(gun->getPositionX() - updateSp->getContentSize().width, gun->getPositionY());
					addChild(updateSp);
				}
				gun->getSellSp()->setVisible(true);
				gun->getFanwei()->setVisible(true);
				gun->getUpdateSp()->setVisible(true);
			}
			else
			{
				gun->getUpdateSp()->setVisible(false);
				gun->getSellSp()->setVisible(false);
				gun->getFanwei()->setVisible(false);
			}
		}
	}
	return true;
}
void MainScene::onTouchMoved(Touch* t, Event* e)
{
	if (touchingGun == nullptr)
	{

	}
	if (touchingGun != nullptr)
	{
		touchingGun->setPosition(t->getLocation());
		gunPos->setVisible(true);
		fanwei->setPosition(t->getLocation());
	}
}
void MainScene::onTouchEnded(Touch* t, Event* e)
{
	if (touchingGun != nullptr)
	{
		if (!canSetGun(t->getLocation(), touchingGun->getBoundingBox()))
		{
			touchingGun->removeFromParent();
			fanwei->removeFromParent();
		}
		else
		{
			guns->pushBack(touchingGun);
			touchingGun->setOpacity(255);
			touchingGun->setFanwei(fanwei);
			touchingGun->schedule(schedule_selector(Gun::updateFire), 0.5f);
			fanwei->setVisible(false);
		}
		touchingGun = nullptr;
	}
	gunPos->setVisible(false);
}