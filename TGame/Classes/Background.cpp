#include "Background.h"

bool Background::init()
{
	mapInfo = experimental::TMXTiledMap::create("bgMap.tmx");
	addChild(mapInfo);
	mapInfo->setAnchorPoint(Vec2(0.5, 0.5));
	mapInfo->setPosition(mapInfo->getContentSize()/2);
	return true;
}

