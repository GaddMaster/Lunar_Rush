//SAMANTHA MARAH
//K00200782

//SAMUEL MACSWEENEY
//K00200955

#ifndef FINISHLINE_H
#define FINISHLINE_H

#include "cocos2d.h"
#include "SecondWorld.h"

class FinishLine : public cocos2d::Sprite
{
public:
	FinishLine();
	~FinishLine();

	void init_finish_line(SecondWorld* SecondWorldScene);

	float set_finish_line_position(float x, float y);

	float set_finish_line_detector_position(float a, float b, float c, float d);

	float set_finish_line_pre_detector_position(float e, float f, float g, float h);

	CREATE_FUNC(FinishLine);

	cocos2d::Sprite* finish_line_sprite;
	cocos2d::Sprite* finish_line_detector_sprite;
	cocos2d::Sprite* finish_line_pre_detector_sprite;

	cocos2d::PhysicsBody* finish_line_detector_physics;
	cocos2d::PhysicsBody* finish_line_pre_detector_physics;

	float m_position_x;
	float m_position_y;

	float m_position_a;
	float m_position_b;
	float m_position_c;
	float m_position_d;

	float m_position_e;
	float m_position_f;
	float m_position_g;
	float m_position_h;
};
#endif