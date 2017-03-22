//SAMANTHA MARAH - K00200782

#include "Rocket.h"

//CONSTRUCTOR & DE-CONSTRUCTOR
Rocket::Rocket()
{
	m_type = "rocket";
	sprite = cocos2d::Sprite::create("Weapons/Projectiles/rocket.png");
	mArray[0] = cocos2d::Vec2(-10 / TIscale, -2 / TIscale);
	mArray[1] = cocos2d::Vec2(-10 / TIscale, 2 / TIscale);
	mArray[2] = cocos2d::Vec2(10 / TIscale, 2 / TIscale);
	mArray[3] = cocos2d::Vec2(10 / TIscale, -2 / TIscale);
	mArray[4] = cocos2d::Vec2(-10 / TIscale, -2 / TIscale);
	physicsBody = cocos2d::PhysicsBody::createPolygon(mArray, 5, cocos2d::PhysicsMaterial(1, 1, 1));
	sprite->setPhysicsBody(physicsBody);
	physicsBody->setCollisionBitmask(4);
	physicsBody->setContactTestBitmask(true);
	physicsBody->setAngularDamping(10);
};
Rocket::~Rocket(){};

//RETURN SPRITE POINTER
cocos2d::Sprite* Rocket::getSprite()
{
	return sprite;
}

//RETURN PHYSICS BODY POINTER
cocos2d::PhysicsBody * Rocket::getPhysicsBody()
{
	return physicsBody;
}

//MAIN ANIMATION FOR OBJECT
void Rocket::animate()
{
	for (int i = 0; i < 6; i++)
	{
		auto frame = cocos2d::SpriteFrame::create("Weapons/Projectiles/rocketSprite.png", cocos2d::Rect(20 * i / TIscale, 0 / TIscale, 20 / TIscale, 20 / TIscale));
		animationFrames.pushBack(frame);
	}
	auto animation = cocos2d::Animation::createWithSpriteFrames(animationFrames, 0.1f);
	auto animate = cocos2d::Animate::create(animation);
	sprite->runAction(cocos2d::RepeatForever::create(animate));
}

//OBJECT EXPODES ON CONTACT
void Rocket::explode()
{
	for (int i = 0; i < 10; i++)
	{
		auto frame = cocos2d::SpriteFrame::create("Particles/explosion_small.png", cocos2d::Rect(20 * i / TIscale, 0 / TIscale, 20 / TIscale, 20 / TIscale));
		animationFrames.pushBack(frame);
	}
	auto animation = cocos2d::Animation::createWithSpriteFrames(animationFrames, 0.1f);
	auto animate = cocos2d::Animate::create(animation);
	sprite->runAction(cocos2d::CCSequence::create(cocos2d::Repeat::create(animate, 1), cocos2d::CallFunc::create([this]() { destroyed = true; }), NULL));
}

//RETURN THE OBJECT TYPE - STRING
std::string Rocket::returnType()
{
	return m_type;
}

//RETURN OBJECT STATUS - ALIVE | DESTROYED - OBJECT EXPLODES ON CONTACT
bool Rocket::isDestoryed()
{
	return destroyed;
}

//DELETE OBJECT _ GARBAGE COLLECTION
void Rocket::DisposeObject()
{
	delete this;
}