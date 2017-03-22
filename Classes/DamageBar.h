//SAMANTHA MARAH
//K00200782

#ifndef DAMAGEBAR_H
#define DAMAGEBAR_H

#include "cocos2d.h"
#include "SecondWorld.h"

class DamageBar : public cocos2d::Sprite
{
	public:
		DamageBar();
		~DamageBar();

		void init_damage_bar(SecondWorld* SecondWorldScene);

		float set_damage_bar_position(float x, float y);

		CREATE_FUNC(DamageBar);

		cocos2d::Sprite* damage_bar_sprite;

		float m_position_x;
		float m_position_y;
};
#endif
