/*
* Samuel MacSweeney
* K00200955
*/

#include "SinglePlayerMenu.h"
#include "MainMenu.h"
#include "FirstWorld.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* SinglePlayerMenu::createScene()
{
	// 'scene' is an autorelease object
	auto SinglePlayerMenuScene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = SinglePlayerMenu::create();

	// add layer as a child to scene
	SinglePlayerMenuScene->addChild(layer);

	// return the scene
	return SinglePlayerMenuScene;
}

bool SinglePlayerMenu::init()
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
	auto background = Sprite::create("MainMenu/background.png");
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(background);

	auto logo = MenuItemImage::create("MainMenu/logo.png", "MainMenu/logo.png");
	logo->setPosition(650, 650);

	auto NewGame = MenuItemImage::create("SinglePlayerMenu/newgame.png", "SinglePlayerMenu/newgameselected.png", CC_CALLBACK_1(SinglePlayerMenu::NewGame, this));
	NewGame->setPosition(650, 500);
	NewGame->setScale(0.5);

	auto goBack = MenuItemImage::create("SinglePlayerMenu/return.png", "SinglePlayerMenu/returnselected.png", CC_CALLBACK_1(SinglePlayerMenu::goBack, this));
	goBack->setPosition(650, 350);
	goBack->setScale(0.5);

	auto *menu1 = Menu::create(logo, NewGame, goBack, NULL);
	menu1->setPosition(Point(0, 0));
	this->addChild(menu1);

	return true;
}

void SinglePlayerMenu::NewGame(cocos2d::Ref *pSender)
{

	auto FirstWorldScene = FirstWorld::createScene();
	Director::getInstance()->replaceScene(FirstWorldScene);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Menu1.mp3");
}

void SinglePlayerMenu::goBack(cocos2d::Ref *pSender)
{
	auto scene = MainMenu::createScene();
	Director::getInstance()->replaceScene(TransitionPageTurn::create(1.5, scene, true));
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Menu1.mp3");
}