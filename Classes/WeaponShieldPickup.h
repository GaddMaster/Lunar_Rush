//SAMANTHA MARAH
//K00200782

#ifndef WEAPONSHIELDPICKUP_H
#define WEAPONSHIELDPICKUP_H

//Includes The COCOS2D-X Libraries Into This Header File
#include "cocos2d.h"

//Includes The PickUps Header File Into This Header File
#include "PickUps.h"

//WeaponShieldPickup Class That Inherits The PickUps Class
class WeaponShieldPickup : public PickUps
{
public:
	//WeaponShieldPickup Constructor
	WeaponShieldPickup();

	//WeaponShieldPickup Destructor
	~WeaponShieldPickup();

	//Returns The WeaponShieldPickup Sprite
	cocos2d::Sprite* getSprite();

	//Returns The WeaponShieldPickup Physics Body
	cocos2d::PhysicsBody* getPhysicsBody();

	//Rotates The WeaponShieldPickup
	void rotate();

	void seeID();
};

#endif