//SAMANTHA MARAH
//K00200782

//SAMUEL MACSWEENEY
//K00200955

#include "TurretBody.h"

USING_NS_CC;

TurretBody::TurretBody()
{};

TurretBody::~TurretBody()
{};

void TurretBody::init_turret_body(SecondWorld* SecondWorldScene)
{
	turret_body_sprite = Sprite::create("Turret/turretbase.png");
	turret_body_sprite->setAnchorPoint(Vec2(0.5, 0.5));
	turret_body_sprite->setScale(0.5);
	turret_body_sprite->setPosition(Vec2(m_position_x, m_position_y));

	turret_body_physics = PhysicsBody::createBox(turret_body_sprite->getContentSize(), PhysicsMaterial(0, 0, 0));
	turret_body_physics->setCollisionBitmask(9);
	turret_body_physics->setContactTestBitmask(true);
	turret_body_physics->setDynamic(false);

	turret_body_sprite->setPhysicsBody(turret_body_physics);

	SecondWorldScene->addChild(turret_body_sprite, 2);
};

float TurretBody::set_turret_body_position(float x, float y)
{
	m_position_x = x;
	m_position_y = y;

	return m_position_x, m_position_y;
};