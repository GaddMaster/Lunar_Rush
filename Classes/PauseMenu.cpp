/*
* Samuel MacSweeney
* K00200955
*/

#include "MainMenu.h"
#include "PauseMenu.h"
#include "FirstWorld.h"
#include "SecondWorld.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* PauseMenu::createScene()
{
	// 'scene' is an autorelease object
	auto PauseMenuScene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = PauseMenu::create();

	// add layer as a child to scene
	PauseMenuScene->addChild(layer);

	// return the scene
	return PauseMenuScene;
}

bool PauseMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	//import audio engine
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();

	//Preload sounds goes here
	//audio->preloadBackgroundMusic();
	//audio->preloadEffect();

	//Adding Images and menu items
	auto logo = MenuItemImage::create("MainMenu/logo.png", "MainMenu/logo.png");
	logo->setPosition(650, 650);

	auto goBack = MenuItemImage::create("SinglePlayerMenu/return.png", "SinglePlayerMenu/returnselected.png", CC_CALLBACK_1(PauseMenu::goBack, this));
	goBack->setPosition(650, 350);
	goBack->setScale(0.5);

	return true;
}

void PauseMenu::PauseGame(cocos2d::Ref *pSender)
{

	auto FirstWorldScene = FirstWorld::createScene();
	Director::getInstance()->replaceScene(FirstWorldScene);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Menu1.mp3");
}

void PauseMenu::goBack(cocos2d::Ref *pSender)
{
	auto scene = MainMenu::createScene();
	Director::getInstance()->replaceScene(TransitionPageTurn::create(1.5, scene, true));
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Menu1.mp3");
}