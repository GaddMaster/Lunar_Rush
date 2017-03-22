//SAMANTHA MARAH
//K00200782

#ifndef ENDINGCREDITS_H
#define ENDINGCREDITS_H

//Adds In The Cocos2d-x Libraries
#include "cocos2d.h"

//EndingCredits Class Inherits The Cocos2d-x Layer Class
class EndingCredits : public cocos2d::Layer
{
	//Public Functions
	public:
		static cocos2d::Scene* createScene();
		virtual bool init() override;

		//The CREATE_FUNC Is A Macro That Defines The
		//create(), init() And autorelease() Functions
		//You Can Create Your Own But It's A Shortcut Helper Macro
		CREATE_FUNC(EndingCredits);

		void update(float) override;

		cocos2d::Sprite* ending_credits;
};

#endif