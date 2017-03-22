//SAMANTHA MARAH
//K00200782

//SAMUEL MACSWEENEY
//K00200955

#ifndef TURRETBODY_H
#define TURRETBODY_H

#include "cocos2d.h"
#include "SecondWorld.h"

class TurretBody : public cocos2d::Sprite
{
public:
	TurretBody();
	~TurretBody();

	void init_turret_body(SecondWorld* SecondWorldScene);

	float set_turret_body_position(float x, float y);

	CREATE_FUNC(TurretBody);

	cocos2d::Sprite* turret_body_sprite;

	cocos2d::PhysicsBody* turret_body_physics;

	float m_position_x;
	float m_position_y;
};
#endif