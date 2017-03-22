//SAMANTHA MARAH - K00200782

#ifndef BULLET_H
#define BULLET_H

#include "cocos2d.h"
#include "GameObjectPhysics.h"

class Bullet : public GameObjectPhysics
{
	public://///////////// PUBLIC FUNCTIONS ////////////

		//CONSTRUCTOR & DE-CONSTRUCTOR
		Bullet();
		~Bullet();
		void DisposeObject();

		//GET SPRITE & PHYSICS BODY POINTER
		cocos2d::Sprite* getSprite();
		cocos2d::PhysicsBody* getPhysicsBody();

		void animate();//MAIN ANIMATION 
		void explode();//PROJECTILE EXPLODES ON CONTACT
		std::string returnType();//RETURN OBJECT TYPE
		bool isDestoryed();//RETURN IF THE OBJECT IS DESTROYED YET
};
#endif