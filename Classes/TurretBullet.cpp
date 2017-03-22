//SAMUEL MACSWEENEY
//K00200955

#include "TurretBullet.h"

USING_NS_CC;

TurretBullet::TurretBullet()
{};

TurretBullet::~TurretBullet()
{};

void TurretBullet::set_turret_bullet_velocity(float a, float b)
{
	m_velocity_a;
	m_velocity_b;
};

float TurretBullet::get_turret_bullet_velocity()
{
	return m_velocity_a, m_velocity_b;
};

void TurretBullet::set_turret_bullet_position(float x, float y)
{
	m_position_x = x;
	m_position_y = y;
};

float TurretBullet::get_turret_bullet_position()
{

	return m_position_x, m_position_y;
};

void TurretBullet::setmove(float c, float d)
{
	m_move_c = c;
	m_move_d = d;
};

float TurretBullet::getmove()
{
	return m_move_c, m_move_d;
};

void TurretBullet::init_turret_bullet(SecondWorld* SecondWorldScene)
{
	turret_bullet = Sprite::create("Turret/turretammo.png");
	turret_bullet->setScale(0.1);
	turret_bullet->setPosition(m_position_x, m_position_y);

	turret_bullet_physics = PhysicsBody::createCircle(turret_bullet->getContentSize().width / 2, PhysicsMaterial(0, 0, 0));
	turret_bullet_physics->setCategoryBitmask(3);
	turret_bullet_physics->setCollisionBitmask(4);

	turret_bullet->setPhysicsBody(turret_bullet_physics);

	auto moveTo = MoveTo::create(2, Vec2(m_move_c, m_move_d));
	turret_bullet->runAction(RepeatForever::create(cocos2d::Sequence::create(moveTo, NULL)));

	SecondWorldScene->addChild(turret_bullet, 10);
};