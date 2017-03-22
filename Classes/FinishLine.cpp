//SAMANTHA MARAH
//K00200782

//Includes The FinishLine Header File
#include "FinishLine.h"

USING_NS_CC;

//FinishLine Constructor
FinishLine::FinishLine()
{
	//Creates Sprite And Parses In Image Location For
	//finishLineSprite
	finishLineSprite = Sprite::create("FinishLine/finishline.png");

	//Sets finishLineSprite Anchor Point
	finishLineSprite->setAnchorPoint(Vec2(0.0, 0.0));

	//Sets The Scale For The finishLineSprite Image
	//I Have Reduced The Size To Where It Will Fit
	finishLineSprite->setScaleX(0.7);
};

//FinishLine Destructor
FinishLine::~FinishLine()
{};

//Returns The Finish Line Sprites
cocos2d::Sprite* FinishLine::getFinishLineSprite()
{
	return finishLineSprite;
};