//SAMANTHA MARAH
//K00200782

//SAMUEL MACSWEENEY
//K00200955

#include "FinishLine.h"

USING_NS_CC;

FinishLine::FinishLine()
{};

FinishLine::~FinishLine()
{};

void FinishLine::init_finish_line(SecondWorld* SecondWorldScene)
{
	finish_line_sprite = Sprite::create("FinishLine/finishline.png");

	finish_line_sprite->setPosition(Vec2(m_position_x, m_position_y));
	finish_line_sprite->setAnchorPoint(Vec2(0.0, 0.0));
	finish_line_sprite->setScaleX(0.7);

	SecondWorldScene->addChild(finish_line_sprite, 0);

	finish_line_detector_sprite = Sprite::create();

	finish_line_detector_physics = PhysicsBody::createEdgeSegment((Vec2(m_position_a, m_position_b)), (Vec2(m_position_c, m_position_d)), PhysicsMaterial(0, 0, 0), 10);

	finish_line_detector_physics->setCollisionBitmask(2);
	finish_line_detector_physics->setContactTestBitmask(true);
	finish_line_detector_physics->setDynamic(false);

	finish_line_detector_sprite->setPhysicsBody(finish_line_detector_physics);

	SecondWorldScene->addChild(finish_line_detector_sprite, 1);

	finish_line_pre_detector_sprite = Sprite::create();

	finish_line_pre_detector_physics = PhysicsBody::createEdgeSegment((Vec2(m_position_e, m_position_f)), (Vec2(m_position_g, m_position_h)), PhysicsMaterial(0, 0, 0), 10);
	finish_line_pre_detector_physics->setCollisionBitmask(3);
	finish_line_pre_detector_physics->setContactTestBitmask(true);
	finish_line_pre_detector_physics->setDynamic(false);

	finish_line_pre_detector_sprite->setPhysicsBody(finish_line_pre_detector_physics);

	SecondWorldScene->addChild(finish_line_pre_detector_sprite, 1);
};

float FinishLine::set_finish_line_position(float x, float y)
{
	m_position_x = x;
	m_position_y = y;

	return m_position_x, m_position_y;
};

float FinishLine::set_finish_line_detector_position(float a, float b, float c, float d)
{
	m_position_a = a;
	m_position_b = b;
	m_position_c = c;
	m_position_d = d;

	return m_position_a, m_position_b, m_position_c, m_position_d;
};

float FinishLine::set_finish_line_pre_detector_position(float e, float f, float g, float h)
{
	m_position_e = e;
	m_position_f = f;
	m_position_g = g;
	m_position_h = h;

	return m_position_e, m_position_f, m_position_g, m_position_h;
};