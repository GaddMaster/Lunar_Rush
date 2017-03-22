//SAMANTHA MARAH
//K00200782

#ifndef THRUSTERBAR_H
#define THRUSTERBAR_H

#include "cocos2d.h"
#include "SecondWorld.h"

class ThrusterBar : public cocos2d::Sprite
{
	public:
		ThrusterBar();
		~ThrusterBar();

		void init_thruster_bar(SecondWorld* SecondWorldScene);

		float set_thruster_bar_position(float x, float y);

		CREATE_FUNC(ThrusterBar);

		cocos2d::Sprite* thruster_bar_sprite;

		float m_position_x;
		float m_position_y;
};

#endif