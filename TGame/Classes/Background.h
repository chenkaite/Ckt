#pragma once
#include "cocos2d.h"
USING_NS_CC;

class Background : public Sprite
{
public:
	experimental::TMXTiledMap* mapInfo;
	bool init();
	CREATE_FUNC(Background);

};