//SAMANTHA MARAH
//K00200782

#include "DamageBar.h"

USING_NS_CC;

DamageBar::DamageBar()
{};

DamageBar::~DamageBar()
{};

void DamageBar::init_damage_bar(SecondWorld* SecondWorldScene)
{
	damage_bar_sprite = Sprite::create("Bars/damagebar.png");
	damage_bar_sprite->setAnchorPoint(Vec2(0.0, 0.0));
	damage_bar_sprite->setScale(0.1);
	damage_bar_sprite->setPosition(Vec2(m_position_x, m_position_y));

	SecondWorldScene->addChild(damage_bar_sprite, 4);
};

float DamageBar::set_damage_bar_position(float x, float y)
{
	m_position_x = x;
	m_position_y = y;

	return m_position_x, m_position_y;
};