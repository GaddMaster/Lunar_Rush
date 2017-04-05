//SAMUEL MACSWEENEY

#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "cocos2d.h"
#include "GameObject.h"

class Explosion : public GameObject
{
	public://///////////// PUBLIC FUNCTIONS ////////////

		Explosion();
		~Explosion();
		void DisposeObject();
		cocos2d::Sprite* getSprite();
		void animate();
		void explode();
		std::string returnType();
		bool isDestoryed();
};
#endif//DEFINE - EXPLOSION_H