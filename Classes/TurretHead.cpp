//SAMUEL MACSWEENEY
//K00200955

#include "TurretHead.h"

USING_NS_CC;

TurretHead::TurretHead()
{
	turret_head_sprite = Sprite::create("Turret/turrethead.png");
	turret_head_sprite->setAnchorPoint(Vec2(0.5, 0.5));
	turret_head_sprite->setScale(0.5);
	turret_head_sprite->setPosition(Vec2(m_position_x, m_position_y));
};

TurretHead::~TurretHead()
{};

void TurretHead::turretmove()
{
	//Creates The Rotate Function That Rotates 350 Degrees In Two Seconds
	auto rotate = RotateBy::create(2.0f, 350.f);

	//Repeats The rotate Action Forever
	turret_head_sprite->runAction(RepeatForever::create(rotate));
};

void TurretHead::set_turret_head_position(float x, float y)
{
	m_position_x = x;
	m_position_y = y;
};

float TurretHead::get_turret_head_position()
{
	return m_position_x, m_position_y;
};


cocos2d::Sprite* TurretHead::getSprite()
{
	return turret_head_sprite;
};

cocos2d::Vec2 TurretHead::getPosition()
{
	return turret_head_sprite->getPosition();
};

void TurretHead::setPosition(cocos2d::Vec2 pos)
{
	position.x = pos.x;
	position.y = pos.y;
	turret_head_sprite->setPosition(position);
};