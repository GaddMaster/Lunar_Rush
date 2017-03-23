//SAMANTHA MARAH
//K00200782

//Includes The EndingCredits Header
#include "EndingCredits.h"

USING_NS_CC;

//createScene Function
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

	//Set The Image For endingCredits Sprite
	endingCreditsSprite = Sprite::create("EndingCredits/endingcredits.png");

	//Sets The Position Of The Sprite Relative To The X, Y Co-ordinates
	//The Co-ordinates Are 0,0 Which In The Window Is The Bottom Left Corner Of The Window
	endingCreditsSprite->setPosition(0, -1000);

	//Sets The Anchor Point Of The Sprite
	endingCreditsSprite->setAnchorPoint(Vec2(0.0, 0.0));

	//You Use addChild() To Put The Sprite Into The Display List
	//This Displays The Sprite Onto The Screen
	this->addChild(endingCreditsSprite, 0);

	//Schedules An Update Of The Scene Functions
	this->scheduleUpdate();

	return true;
};

//update Function
void EndingCredits::update(float move)
{
	//Gets The Position Of The endingCredits Sprite
	//And Assigns It To The Variable position
	auto position = endingCreditsSprite->getPosition();

	//Increments The Variable position's Y Co-Ordinate
	position.y += 100 * move;

	//It Will Increment And Set The New Y Co-Ordinate
	//20 Times Which Scrolls The endingCredits Sprite
	//Vertically
	for (int i = 0; i < 20; i++)
	{
		endingCreditsSprite->setPosition(position);
	}
};