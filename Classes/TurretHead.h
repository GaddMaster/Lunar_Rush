//SAMUEL MACSWEENEY
//K00200955

#ifndef TURRETHEAD_H
#define TURRETHEAD_H

#include "cocos2d.h"

class TurretHead
{
public:
	TurretHead();
	~TurretHead();

	void set_turret_head_position(float x, float y);
	float get_turret_head_position();

	void setRotateHead1(float a, float b);
	float getRotateHead1();

	void setRotateHead2(float c, float d);
	float getRotateHead2();

	void setRotationBool1(bool ro1);
	bool getRotationBool1();

	void setRotationBool2(bool ro2);
	bool getRotationBool2();

	void turretmove();

	cocos2d::Sprite* getSprite();

	cocos2d::Vec2 getPosition();
	void setPosition(cocos2d::Vec2 pos);

	cocos2d::Sprite* turret_head_sprite;
	cocos2d::PhysicsBody* turret_head_physics;

	float m_position_x;
	float m_position_y;

	float m_position_a;
	float m_position_b;

	float m_position_c;
	float m_position_d;

	bool m_rotate1;
	bool m_rotate2;

	cocos2d::Vec2 position;
};

#endif