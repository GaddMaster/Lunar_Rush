//SAMUEL
#include "CircleCircuit.h"

USING_NS_CC;

CircleCircuit::CircleCircuit()
{};

CircleCircuit::~CircleCircuit()
{};

void CircleCircuit::init_CircleCircuit(SecondWorld* SecondWorldScene)
{
	//CircleCircuit OBSTACLE
	CircleCircuitSprite = Sprite::create("Obstacles/circlecircuit.png");
	CircleCircuitSprite->setPosition(Vec2(m_position_x, m_position_y));
	CircleCircuitSprite->setScale(0.1);

	CircleCircuitPhysicsBody = PhysicsBody::createCircle(CircleCircuitSprite->getContentSize().width / 2, PhysicsMaterial(0, 0, 0));

	CircleCircuitPhysicsBody->setCollisionBitmask(5);

	CircleCircuitPhysicsBody->setAngularDamping(10);
	CircleCircuitPhysicsBody->setVelocityLimit(10);

	CircleCircuitPhysicsBody->setContactTestBitmask(true);
	CircleCircuitPhysicsBody->setDynamic(true);

	CircleCircuitSprite->setPhysicsBody(CircleCircuitPhysicsBody);

	SecondWorldScene->addChild(CircleCircuitSprite, 2);
};

float CircleCircuit::set_CircleCircuit_position(float x, float y)
{
	m_position_x = x;
	m_position_y = y;

	return m_position_x, m_position_y;
};