//SAMANTHA MARAH
//K00200782

#ifndef HUD_LAYER_H
#define HUD_LAYER_H

#include "cocos2d.h"
#include "SecondWorld.h"

class HudLayer : public cocos2d::Layer 
{
	public:
		HudLayer();
		~HudLayer();

		//HUD LAYER
		void init_hud_layer(SecondWorld* SecondWorldScene);
		float set_hud_layer_position(float x, float y);
		cocos2d::Size set_hud_layer_size(cocos2d::Size a);

		//LAP NUMBER
		void init_lap_number(SecondWorld* SecondWorldScene);
		float set_lap_number_position(float c, float d);
		int set_lap_number(int b);

		CREATE_FUNC(HudLayer);

		float m_position_x;
		float m_position_y;
		float m_position_c;
		float m_position_d;
		int m_number_b;

		cocos2d::LayerGradient* HUD;
		cocos2d::Size m_size_a;
		cocos2d::Label* lap_number;
};
#endif