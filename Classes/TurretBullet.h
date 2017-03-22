//SAMUEL MACSWEENEY
//K00200955

#ifndef TURRETBULLET_H
#define TURRETBULLET_H

#include "cocos2d.h"
#include "SecondWorld.h"

class TurretBullet : public cocos2d::Sprite
{
	public:
		TurretBullet();
		~TurretBullet();

		cocos2d::Sprite* turret_bullet;
		cocos2d::PhysicsBody* turret_bullet_physics;

		void init_turret_bullet(SecondWorld* SecondWorldScene);
		void set_turret_bullet_position(float x, float y);
		float get_turret_bullet_position();
		void set_turret_bullet_velocity(float a, float b);
		float get_turret_bullet_velocity();
		void setmove(float c, float d);
		float getmove();

		float m_velocity_a;
		float m_velocity_b;

		float m_position_x;
		float m_position_y;

		float m_move_c;
		float m_move_d;
};
#endif