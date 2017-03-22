//SAMUAL SWEENEY - BASE GAME OBJECT WITH PHYSICS BODY
#ifndef GAME_OBJECT_PHYSICS_H
#define GAME_OBJECT_PHYSICS_H

#include "cocos2d.h"
#include "GameObject.h"

class GameObjectPhysics : public GameObject
{
	public:

		virtual cocos2d::PhysicsBody* getPhysicsBody() = 0;

	protected:

		GameObjectPhysics(){};
		virtual ~GameObjectPhysics(){};
		cocos2d::PhysicsBody* physicsBody;
};

#endif