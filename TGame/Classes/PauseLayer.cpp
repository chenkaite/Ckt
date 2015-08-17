#include "PauseLayer.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
bool PauseLayer::init()
{
	if (!LayerColor::init())
	{
		return false;
	}
	initWithColor(Color4B(112, 128, 144, 100), 800, 450);
	auto menuBg = Sprite::createWithSpriteFrameName("menu_bg.png");
	addChild(menuBg,20);
	menuBg->setPosition(getContentSize()/2);
	auto resume_normal = Sprite::createWithSpriteFrameName("menu_resume_normal_CN.png");
	auto resume_pressed = Sprite::createWithSpriteFrameName("menu_resume_pressed_CN.png");
	auto quit_normal = Sprite::createWithSpriteFrameName("menu_quit_normal_CN.png");
	auto quit_pressed = Sprite::createWithSpriteFrameName("menu_quit_pressed_CN.png");
	auto restart_normal = Sprite::createWithSpriteFrameName("menu_restart_normal_CN.png");
	auto restart_pressed = Sprite::createWithSpriteFrameName("menu_restart_pressed_CN.png");
	auto quit = MenuItemSprite::create(quit_normal,quit_pressed,nullptr);
	auto resume = MenuItemSprite::create(resume_normal, resume_pressed, nullptr);
	auto restart = MenuItemSprite::create(restart_normal, restart_pressed, nullptr);
	auto menu = Menu::create(quit,resume,restart,nullptr);
	restart->setPositionY(2);
	quit->setPositionY(-61);
	resume->setPositionY(62.5);
	addChild(menu,21);
	
	return true;
}