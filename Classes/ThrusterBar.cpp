//SAMANTHA MARAH
//K00200782

#include "ThrusterBar.h"

USING_NS_CC;

ThrusterBar::ThrusterBar()
{};

ThrusterBar::~ThrusterBar()
{};

void ThrusterBar::init_thruster_bar(SecondWorld* SecondWorldScene)
{
	thruster_bar_sprite = Sprite::create("Bars/thrusterbar.png");
	thruster_bar_sprite->setAnchorPoint(Vec2(0.5, 0.5));
	thruster_bar_sprite->setScale(0.1);
	thruster_bar_sprite->setPosition(Vec2(m_position_x, m_position_y));

	SecondWorldScene->addChild(thruster_bar_sprite, 4);
};

float ThrusterBar::set_thruster_bar_position(float x, float y)
{
	m_position_x = x;
	m_position_y = y;

	return m_position_x, m_position_y;
};