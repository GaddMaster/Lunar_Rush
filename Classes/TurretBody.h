//SAMUEL MACSWEENEY
//K00200955

#ifndef TURRETBODY_H
#define TURRETBODY_H

#include "cocos2d.h"
#include "SecondWorld.h"

class TurretBody
{
public:
	TurretBody();
	~TurretBody();

	cocos2d::Sprite* getSprite();
	cocos2d::PhysicsBody* getPhysicsBody();

	cocos2d::Sprite* sprite;

	cocos2d::PhysicsBody* physics;
};
#endif