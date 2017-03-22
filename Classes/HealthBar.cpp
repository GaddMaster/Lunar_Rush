//SAMANTHA MARAH
//K00200782

#include "HealthBar.h"

USING_NS_CC;

HealthBar::HealthBar()
{};

HealthBar::~HealthBar()
{};

void HealthBar::init_health_bar(SecondWorld* SecondWorldScene)
{
	health_bar_sprite = Sprite::create("Bars/healthbar.png");
	health_bar_sprite->setAnchorPoint(Vec2(0.0, 0.0));
	health_bar_sprite->setScale(0.1);
	health_bar_sprite->setPosition(Vec2(m_position_x, m_position_y));

	SecondWorldScene->addChild(health_bar_sprite, 4);
};

float HealthBar::set_health_bar_position(float x, float y)
{
	m_position_x = x;
	m_position_y = y;

	return m_position_x, m_position_y;
};