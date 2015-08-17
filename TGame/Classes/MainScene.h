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
	Point getPos(Point p);//����������ϵת��ΪTmx��ͼ��Ӧ����
	void moveUpdate(float dt);
	bool canSetGun(Vec2 position,Rect rect);
	void addBg();//��ӱ���ͼƬ
public:
	static Vector<Bullet*> *bullets;//�ӵ�����
	static Vector<Gun*> *guns;//�ѷ��õ�����������
	static Vector<Monster*> *mons;//���õ��˵�����
	Sprite* menuSp;//�˵�����
	Vector<Node*> vectorMove;//�����ƶ�·��
	Vector<Gun*> gunPics;//����ͼƬ��
	Gun* touchingGun;//ѡ�е�����
	experimental::TMXLayer* gunPos;//�����ɷ�������
	Vector<SpriteFrame*> bloodPics;//Ѫ��ͼƬ����1-9
	int bloodIndex;//Ѫ���±�
	CC_SYNTHESIZE(int,money,Money);//�������
private:
	Sprite* fanwei;//��������Χ
	int moveTime;
	bool isDoubleSpeed;//�Ƿ�˫���ٶ�
	int copyMonsSpeed;//��������ʱ����
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
