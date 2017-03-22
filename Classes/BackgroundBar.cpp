//SAMANTHA MARAH
//K00200782

#include "BackgroundBar.h"

USING_NS_CC;

BackgroundBar::BackgroundBar()
{};

BackgroundBar::~BackgroundBar()
{};

void BackgroundBar::init_background_bar(SecondWorld* HUD)
{
	background_bar_sprite = Sprite::create("Bars/backgroundbar.png");
	background_bar_sprite->setAnchorPoint(Vec2(0.0, 0.0));
	background_bar_sprite->setScale(0.1);
	background_bar_sprite->setPosition(Vec2(m_position_x, m_position_y));

	HUD->addChild(background_bar_sprite, 6);
};

float BackgroundBar::set_background_bar_position(float x, float y)
{
	m_position_x;
	m_position_y;

	return m_position_x, m_position_y;
};