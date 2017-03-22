//SAMANTHA MARAH
//K00200782

#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include "cocos2d.h"
#include "SecondWorld.h"

class HealthBar : public cocos2d::Sprite
{
	public:
		HealthBar();
		~HealthBar();

		void init_health_bar(SecondWorld* SecondWorldScene);

		float set_health_bar_position(float x, float y);

		CREATE_FUNC(HealthBar);

		cocos2d::Sprite* health_bar_sprite;

		float m_position_x;
		float m_position_y;
};
#endif