//SAMANTHA MARAH
//K00200782

#include "Bullet.h"

USING_NS_CC;

//CONSTRUCTOR & DE-CONSTRUCTOR
Bullet::Bullet()
{
	m_type = "bullet";
	sprite = Sprite::create("Weapons/Projectiles/bullet.png");
	physicsBody = PhysicsBody::createBox(sprite->getContentSize(), PhysicsMaterial(0, 0, 0));
	sprite->setPhysicsBody(physicsBody);
	physicsBody->setCollisionBitmask(4);
	physicsBody->setContactTestBitmask(true);
};
Bullet::~Bullet() {};

//RETURN SPRITE POINTER
cocos2d::Sprite* Bullet::getSprite()
{
	return sprite;
}

//RETURN PHYSICS BODY POINTER
cocos2d::PhysicsBody* Bullet::getPhysicsBody()
{
	return physicsBody;
}

//MAIN ANIMATION FOR OBJECT
void Bullet::animate()
{
	for (int i = 0; i < 4; i++)
	{
		auto frame = SpriteFrame::create("Weapons/Projectiles/bulletSprite.png", Rect(10 * i / TIscale, 0 / TIscale, 10 / TIscale, 3 / TIscale));
		animationFrames.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(animationFrames, 0.1f);
	auto animate = Animate::create(animation);
	sprite->runAction(RepeatForever::create(animate));
}

//OBJECT EXPODES ON CONTACT
void Bullet::explode()
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
	sprite->runAction(cocos2d::CCSequence::create(cocos2d::Repeat::create(animate, 1),  cocos2d::CallFunc::create([this]() { destroyed = true; }), NULL));
}

//RETURN THE OBJECT TYPE - STRING
std::string Bullet::returnType()
{
	return m_type;
}

//RETURN OBJECT STATUS - ALIVE | DESTROYED - OBJECT EXPLODES ON CONTACT
bool Bullet::isDestoryed()
{
	return destroyed;
}

//DELETE OBJECT _ GARBAGE COLLECTION
void Bullet::DisposeObject()
{
	delete this;
}