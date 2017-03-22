//SAMUAL SWEENEY - CIRCLE HEADER OBJECT INHERITS BASE OBJECT - OBSTACLES
#ifndef CIRCLE_H
#define CIRCLE_H

#include "cocos2d.h"
#include "GameObjectPhysics.h"

class Circle : public GameObjectPhysics
{
	public://///////////// PUBLIC FUNCTIONS ////////////

		//CONSTRUCTOR & DE-CONSTRUCTOR
		Circle();
		~Circle();
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
