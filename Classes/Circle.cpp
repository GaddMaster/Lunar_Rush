//SAMUAL SWEENEY - CIRCLE CPP OBJECT INHERITS BASE OBJECT - OBSTACLES
#include "Circle.h"

USING_NS_CC;

//CONSTRUCTOR & DE-CONSTRUCTOR
Circle::Circle()
{
	m_type = "circle";
	sprite = Sprite::create("Obstacles/circlecircuit.png");
	sprite->setScale(0.1);
	physicsBody = PhysicsBody::createCircle(10 / TIscale, PhysicsMaterial(0.1, 0, 0));
	sprite->setPhysicsBody(physicsBody);
	physicsBody->setCollisionBitmask(9);
	physicsBody->setContactTestBitmask(true);
	physicsBody->setVelocityLimit(30);
	physicsBody->setAngularDamping(10);
}
Circle::~Circle()
{

}

//RETURN SPRITE POINTER
cocos2d::Sprite* Circle::getSprite()
{
	return sprite;
}

//RETURN PHYSICS BODY POINTER
cocos2d::PhysicsBody* Circle::getPhysicsBody()
{
	return physicsBody;
}

//MAIN ANIMATION FOR OBJECT
void Circle::animate()
{
	for (int i = 0; i < 6; i++)
	{
		auto frame = SpriteFrame::create("Obstacles/circleSprite.png", Rect(50 * i / TIscale, 0 / TIscale, 50 / TIscale, 50 / TIscale));
		animationFrames.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(animationFrames, 0.1f);
	auto animate = Animate::create(animation);
	sprite->runAction(RepeatForever::create(animate));
}

//OBJECT EXPODES ON CONTACT
void Circle::explode()
{
	//EXPLOSION SPRITE 
	for (int i = 0; i < 10; i++)
	{
		auto frame = SpriteFrame::create("Particles/explosion_small.png", Rect(20 * i / TIscale, 0 / TIscale, 20 / TIscale, 20 / TIscale));
		animationFrames.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(animationFrames, 0.1f);
	auto animate = Animate::create(animation);
	sprite->runAction(Repeat::create(animate, 1));//REPEAT ONLY ONCE
}

//RETURN THE OBJECT TYPE - STRING
std::string Circle::returnType()
{
	return m_type;
}

//RETURN OBJECT STATUS - ALIVE | DESTROYED - OBJECT EXPLODES ON CONTACT
bool Circle::isDestoryed()
{
	return destroyed;
}


//DELETE OBJECT _ GARBAGE COLLECTION
void Circle::DisposeObject()
{
	delete this;
}
