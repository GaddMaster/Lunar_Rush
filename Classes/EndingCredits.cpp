//SAMANTHA MARAH
//K00200782

//Includes The EndingCredits Header
#include "EndingCredits.h"

//This Is The Cocos2d-x Equivalent Of "using namespace cocos2d;"
USING_NS_CC;

//createScene Function
//There Is A Scene Pointer That Points To This Specific Scene
Scene* EndingCredits::createScene()
{
	//Creates The Scene
	auto EndingCreditsScene = Scene::create();

	//Creates The EndingCredits Layer
	auto layer = EndingCredits::create();

	//Parses The EndingCredits Layer Into The Scene
	EndingCreditsScene->addChild(layer);

	//Returns The Scene
	return EndingCreditsScene;
};

//init Function
bool EndingCredits::init()
{
	if (!Layer::init())
	{
		return false;
	}

	ending_credits = Sprite::create("EndingCredits/endingcredits.png");

	//Sets The Position Of The Sprite Relative To The X, Y Co-ordinates
	//The Co-ordinates Are 0,0 Which In The Window Is The Bottom Left Corner Of The Window
	ending_credits->setPosition(0, -1000);

	//This Sets The Centerpoint Of The Sprite Itself
	ending_credits->setAnchorPoint(Vec2(0.0, 0.0));

	//You Use addChild() To Put The Sprite Into The Display List
	//This Displays The Sprite Onto The Screen
	this->addChild(ending_credits, 0);
	this->scheduleUpdate();

	return true;
};

void EndingCredits::update(float move)
{
	auto position = ending_credits->getPosition();
	position.y += 100 * move;

	for (int i = 0; i < 20; i++)
	{
		ending_credits->setPosition(position);
	}
};