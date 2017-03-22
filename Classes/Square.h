//SAMUAL SWEENEY - SQUARE CPP OBJECT INHERITS BASE OBJECT - OBSTACLES
#ifndef SQUARE_H
#define SQUARE_H

#include "cocos2d.h"
#include "GameObjectPhysics.h"

class Square : public GameObjectPhysics
{
public://///////////// PUBLIC FUNCTIONS ////////////

	   //CONSTRUCTOR & DE-CONSTRUCTOR
	Square();
	~Square();
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
