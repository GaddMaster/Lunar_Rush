//SAMUEL MACSWEENEY
//K00200955

#include "TurretBody.h"

USING_NS_CC;

TurretBody::TurretBody()
{
	sprite = Sprite::create("Turret/turretbase.png");
	sprite->setAnchorPoint(Vec2(0.5, 0.5));
	sprite->setScale(0.5);

	physics = PhysicsBody::createBox(sprite->getContentSize(), PhysicsMaterial(0, 0, 0));
	physics->setCollisionBitmask(10);
	physics->setContactTestBitmask(true);
	physics->setDynamic(false);

	sprite->setPhysicsBody(physics);
};

TurretBody::~TurretBody()
{};

cocos2d::Sprite* TurretBody::getSprite()
{
	return sprite;
};

cocos2d::PhysicsBody* TurretBody::getPhysicsBody()
{
	return physics;
};

