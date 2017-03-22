//SAMANTHA MARAH
//K00200782

#ifndef THRUSTERPICKUP_H
#define THRUSTERPICKUP_H

//Includes The COCOS2D-X Libraries Into This Header File
#include "cocos2d.h"

//Includes The PickUps Header File Into This Header File
#include "PickUps.h"

//ThrusterPickup Class That Inherits The PickUps Class
class ThrusterPickup : public PickUps
{
	public:
		//ThrusterPickup Constructor
		ThrusterPickup();

		//ThrusterPickup Destructor
		~ThrusterPickup();

		//Returns The ThrusterPickup Sprite
		cocos2d::Sprite* getSprite();

		//Returns The ThrusterPickup Physics Body
		cocos2d::PhysicsBody* getPhysicsBody();

		//Rotates The ThrusterPickup
		void rotate();
};
#endif