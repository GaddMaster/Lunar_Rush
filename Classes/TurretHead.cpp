//SAMANTHA MARAH
//K00200782

//SAMUEL MACSWEENEY
//K00200955

#include "TurretHead.h"

USING_NS_CC;

TurretHead::TurretHead()
{
	turret_head_sprite = Sprite::create("Turret/turrethead.png");
	turret_head_sprite->setAnchorPoint(Vec2(0.25, 0.5));
	turret_head_sprite->setScale(0.5);
	turret_head_sprite->setPosition(Vec2(m_position_x, m_position_y));
};

TurretHead::~TurretHead()
{};

void TurretHead::turretmove()
{
	auto rotate_turret_head1 = RotateTo::create(m_position_a, m_position_b);
	auto rotate_turret_head2 = RotateTo::create(m_position_c, m_position_d);

	auto delay_time = DelayTime::create(4);

	turret_head_sprite->runAction(RepeatForever::create(cocos2d::Sequence::create(rotate_turret_head1, delay_time, rotate_turret_head2, delay_time, NULL)));
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

void TurretHead::setRotateHead1(float a, float b)
{
	m_position_a = a;
	m_position_b = b;
};

float TurretHead::getRotateHead1()
{
	return m_position_a, m_position_b;
};

void TurretHead::setRotateHead2(float c, float d)
{
	m_position_c = c;
	m_position_d = d;
};

float TurretHead::getRotateHead2()
{
	return m_position_c, m_position_d;
};

void TurretHead::setRotationBool1(bool ro1)
{
	m_rotate1 = ro1;
};

bool TurretHead::getRotationBool1()
{
	return m_rotate1;
};

void TurretHead::setRotationBool2(bool ro2)
{
	m_rotate2 = ro2;
};

bool TurretHead::getRotationBool2()
{
	return m_rotate2;
};

cocos2d::Sprite* TurretHead::getSprite()
{
	return turret_head_sprite;
};