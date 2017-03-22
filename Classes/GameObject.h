//SAMUAL SWEENEY - BASE GAME OBJECT 
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "cocos2d.h"

class GameObject
{
	public:

		virtual cocos2d::Sprite* getSprite() = 0;
		virtual void animate() = 0;
		virtual void explode() = 0;
		virtual std::string returnType() = 0;
		virtual bool isDestoryed() = 0;
		virtual void DisposeObject() = 0;


	protected:

		GameObject(){};
		virtual ~GameObject(){};
		cocos2d::Sprite* sprite;
		float TIscale = 1.7068;
		std::string m_type;
		bool destroyed = false;
		cocos2d::Vector<cocos2d::SpriteFrame*> animationFrames;
		cocos2d::Vector<cocos2d::SpriteFrame*> animationFramesII;
		cocos2d::Vec2 mArray[20];//CHILD CLASSES COULD USE LESS - BUT ENOUGH GIVEN FOR ALL 
};

#endif