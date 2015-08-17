#pragma once
#include "cocos2d.h"
USING_NS_CC;

class Blood : public Node
{
public:
	virtual bool init(int type);
	static Blood* create(int type);
	ProgressTimer* pt;
	Sprite* blood;
	Sprite* bloodRect;
};