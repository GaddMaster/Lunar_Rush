//SAMUEL MACSWEENEY

#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "cocos2d.h"
#include "GameObject.h"

class Explosion : public GameObject
{
	public://///////////// PUBLIC FUNCTIONS ////////////

		//CONSTRUCTOR & DE-CONSTRUCTOR
		Explosion();
		~Explosion();
		void DisposeObject();

		cocos2d::Sprite* getSprite();//RETURN SPRITE POINTER
		void animate();//MINE ANIMATION - REPEAT FOREVER
		void explode();//EXPLOSION SPRITE - REPEAT ONLY ONCE
		std::string returnType();//RETUNR OBJECT TYPE - STRING
		bool isDestoryed();//RETURN IF THE OBJECT IS DESTROYED YET
};
#endif//DEFINE - EXPLOSION_H