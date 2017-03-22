/*
* Samuel MacSweeney
* K00200955
*/

#include "MainMenu.h"
#include "SinglePlayerMenu.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
	// 'scene' is an autorelease object
	auto MainMenuScene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainMenu::create();

	// add layer as a child to scene
	MainMenuScene->addChild(layer);

	// return the scene
	return MainMenuScene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	//audio set up
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	
	//Pre-load music
	audio->preloadBackgroundMusic("race.mp3");
	audio->preloadEffect("Sounds/menuclick.mp3");

	// set the background music and continuously play it.
	audio->playBackgroundMusic("race.mp3", true);

	//Adding Images and menu items
	auto background = Sprite::create("MainMenu/background.png");
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(background);

	auto logo = MenuItemImage::create("MainMenu/logo.png", "MainMenu/logo.png");
	logo->setPosition(650, 650);

	auto SinglePlayer = MenuItemImage::create("MainMenu/singleplayer.png", "MainMenu/singleplayerselected.png", CC_CALLBACK_1(MainMenu::singlePlayer, this));
	SinglePlayer->setPosition(650, 500);
	SinglePlayer->setScale(0.5);

	/*auto MultiPlayer = MenuItemImage::create("MainMenu/multiplayer.png", "MainMenu/multiplayerselected.png", CC_CALLBACK_1(MainMenu::multiPlayer, this));
	MultiPlayer->setPosition(650, 350);
	MultiPlayer->setScale(0.5);*/

	auto Exit = MenuItemImage::create("MainMenu/exit.png", "MainMenu/exitselected.png", CC_CALLBACK_1(MainMenu::menuCloseCallback, this));
	Exit->setPosition(650, 200);
	Exit->setScale(0.5);

	auto *menu = Menu::create(logo, SinglePlayer, /*MultiPlayer,*/ Exit, NULL);
	menu->setPosition(Point(0, 0));
	this->addChild(menu);

	return true;
}

void MainMenu::singlePlayer(cocos2d::Ref *pSender)
{;
	auto SinglePlayerMenuScene = SinglePlayerMenu::createScene();
	Director::getInstance()->replaceScene(TransitionPageTurn::create(1.5, SinglePlayerMenuScene, true));
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sounds/menuclick.mp3");
}

/*void MainMenu::multiPlayer(cocos2d::Ref *pSender)
{
	//auto scene2 = SinglePlayerMenu::createScene();
	//Director::getInstance()->replaceScene(scene2);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sounds/menuclick.mp3");
}*/

void MainMenu::menuCloseCallback(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sounds/menuclick.mp3");
	Director::getInstance()->end();
}