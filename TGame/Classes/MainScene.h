#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "Monster.h"
#include "cocos2d.h"
#include "Background.h"
#include "Gun.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "PauseLayer.h"
USING_NS_CC;
using namespace cocos2d::ui;
class MainScene : public Layer
{
public:
    static Scene* createScene();
    virtual bool init();
	CREATE_FUNC(MainScene);
	Point getPos(Point p);//将世界坐标系转换为Tmx地图对应格子
	void moveUpdate(float dt);
	bool canSetGun(Vec2 position,Rect rect);
	void addBg();//添加背景图片
public:
	static Vector<Bullet*> *bullets;//子弹容器
	static Vector<Gun*> *guns;//已放置的武器的容器
	static Vector<Monster*> *mons;//放置敌人的容器
	Sprite* menuSp;//菜单精灵
	Vector<Node*> vectorMove;//敌人移动路径
	Vector<Gun*> gunPics;//武器图片库
	Gun* touchingGun;//选中的武器
	experimental::TMXLayer* gunPos;//武器可放置区域
	Vector<SpriteFrame*> bloodPics;//血量图片集合1-9
	int bloodIndex;//血量下标
	CC_SYNTHESIZE(int,money,Money);//金币数量
private:
	Sprite* fanwei;//塔攻击范围
	int moveTime;
	bool isDoubleSpeed;//是否双倍速度
	int copyMonsSpeed;//怪物生成时间间隔
private:
	void addListen();
	Vector<Node*> getMoveVec(const std::string &name);
	void addAnything();
	void addCache();
	void doubleSpeed();
	bool onTouchBegan(Touch* t, Event* e); 
	void onTouchMoved(Touch* t, Event* e);
	void onTouchEnded(Touch* t, Event* e);
};

#endif // __HELLOWORLD_SCENE_H__
