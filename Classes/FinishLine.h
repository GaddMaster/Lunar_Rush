//SAMANTHA MARAH - K00200782

#ifndef FINISHLINE_H
#define FINISHLINE_H

#include "cocos2d.h"

class FinishLine 
{
	public://///PUBLIC/////////////////

		//CONSTRUCTOR & DE-CONSTRUCTOR
		FinishLine();
		~FinishLine();

		//RETURN SPRITE POINTER
		cocos2d::Sprite* getSprite();

		int returnID();
		void setID(int ID);
		int getID();
		bool getActive();
		void setActive(bool status);

		//SPRITE
		cocos2d::Sprite* sprite;
		int m_id;
		bool m_active;
};
#endif