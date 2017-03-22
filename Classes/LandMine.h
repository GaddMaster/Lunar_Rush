//SAMANTHA MARAH - K00200782

#ifndef LANDMINE_H
#define LANDMINE_H

#include "cocos2d.h"
#include "GameObject.h"

class LandMine : public GameObject
{
public://///////////// PUBLIC FUNCTIONS ////////////

	   //CONSTRUCTOR & DE-CONSTRUCTOR
	LandMine();
	~LandMine();
	void DisposeObject();

	//GET SPRITE & PHYSICS BODY POINTER
	cocos2d::Sprite* getSprite();

	void animate();//MAIN ANIMATION 
	void explode();//PROJECTILE EXPLODES ON CONTACT
	std::string returnType();//RETURN OBJECT TYPE
	bool isDestoryed();//RETURN IF THE OBJECT IS DESTROYED YET
};
#endif