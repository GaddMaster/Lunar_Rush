//SAMANTHA MARAH
//K00200782

#ifndef FINISHLINE_H
#define FINISHLINE_H

#include "cocos2d.h"

class FinishLine
{
public:
	//FinishLine Constructor
	FinishLine();

	//FinishLine Destructor
	~FinishLine();

	//Returns The Finish Line Sprites
	cocos2d::Sprite* getFinishLineSprite();

	//Variables
	cocos2d::Sprite* finishLineSprite;
};
#endif