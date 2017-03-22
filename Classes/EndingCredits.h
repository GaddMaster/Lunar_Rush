//SAMANTHA MARAH
//K00200782

#ifndef ENDINGCREDITS_H
#define ENDINGCREDITS_H

//Includes The COCOS2D-X Libraries Into This Header File
#include "cocos2d.h"

//EndingCredits Class That Inherits The COCOS2-X Layer Class
class EndingCredits : public cocos2d::Layer
{
public:
	//Creates The Scene For The EndingCredits
	static cocos2d::Scene* createScene();

	//Main Function For EndingCredits
	//Functions Are Called Into This Function
	//To Add Them To The Scene
	virtual bool init() override;

	//This Function Updates The Position
	//Of The endingCredits Sprite
	//So That The Sprite Image Will Scroll Vertically
	//Up The Screen
	void update(float) override;

	//Variables
	cocos2d::Sprite* endingCreditsSprite;
};
#endif