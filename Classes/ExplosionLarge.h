//SAMUEL MACSWEENEY

#ifndef EXPLOSIONLARGE_H
#define EXPLOSIONLARGE_H

#include "cocos2d.h"
#include "GameObject.h"

class ExplosionLarge : public GameObject
{
	public://///////////// PUBLIC FUNCTIONS ////////////

		//CONSTRUCTOR & DE-CONSTRUCTOR
		ExplosionLarge();
		~ExplosionLarge();
		void DisposeObject();

		cocos2d::Sprite* getSprite();//RETURN SPRITE POINTER
		void animate();//MINE ANIMATION - REPEAT FOREVER
		void explode();//EXPLOSION SPRITE - REPEAT ONLY ONCE
		std::string returnType();//RETUNR OBJECT TYPE - STRING
		bool isDestoryed();//RETURN IF THE OBJECT IS DESTROYED YET
};
#endif//DEFINE - EXPLOSIONLARGE_H