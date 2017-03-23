//SAMANTHA MARAH
//K00200782

#ifndef HEALTHPICKUP_H
#define HEALTHPICKUP_H

//Includes The COCOS2D-X Libraries Into This Header File
#include "cocos2d.h"

//Includes The PickUps Header File Into This Header File
#include "PickUps.h"

//HealthPickup Class That Inherits The PickUps Class
class HealthPickup : public PickUps
{
public:
	//HealthPickup Constructor
	HealthPickup();

	//HealthPickup Destructor
	~HealthPickup();

	//Returns The HealthPickup Sprite
	cocos2d::Sprite* getSprite();

	//Returns The HealthPickup Physics Body
	cocos2d::PhysicsBody* getPhysicsBody();

	//Rotates The HealthPickup
	void rotate();
};
#endif