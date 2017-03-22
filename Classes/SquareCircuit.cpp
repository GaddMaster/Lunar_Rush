//SAMUEL
#include "SquareCircuit.h"

USING_NS_CC;

SquareCircuit::SquareCircuit()
{};

SquareCircuit::~SquareCircuit()
{};

void SquareCircuit::init_SquareCircuit(SecondWorld* SecondWorldScene)
{
	SquareCircuitSprite = Sprite::create("Obstacles/squarecircuit.png");
	SquareCircuitSprite->setPosition(Vec2(m_position_x, m_position_y));
	SquareCircuitSprite->setScale(0.1);

	SquareCircuitPhysicsBody = PhysicsBody::createBox(SquareCircuitSprite->getContentSize(), PhysicsMaterial(0, 0, 0));

	SquareCircuitPhysicsBody->setCollisionBitmask(5);

	SquareCircuitPhysicsBody->setAngularDamping(10);
	SquareCircuitPhysicsBody->setVelocityLimit(10);

	SquareCircuitPhysicsBody->setContactTestBitmask(true);
	SquareCircuitPhysicsBody->setDynamic(true);

	SquareCircuitSprite->setPhysicsBody(SquareCircuitPhysicsBody);

	SecondWorldScene->addChild(SquareCircuitSprite, 2);
};

float SquareCircuit::set_SquareCircuit_position(float x, float y)
{
	m_position_x = x;
	m_position_y = y;

	return m_position_x, m_position_y;
};