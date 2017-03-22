//SAMANTHA MARAH
//K00200782

#ifndef BACKGROUNDBAR_H
#define BACKGROUNDAR_H

#include "cocos2d.h"
#include "SecondWorld.h"

class BackgroundBar : public cocos2d::Sprite
{
	public:
		BackgroundBar();
		~BackgroundBar();

		void init_background_bar(SecondWorld* HUD);

		float set_background_bar_position(float x, float y);

		CREATE_FUNC(BackgroundBar);

		cocos2d::Sprite* background_bar_sprite;

		float m_position_x;
		float m_position_y;
};
#endif