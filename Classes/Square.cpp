//SAMUAL SWEENEY - SQUARE HEADER OBJECT INHERITS BASE OBJECT - OBSTACLES
#include "Square.h"

USING_NS_CC;

//CONSTRUCTOR & DE-CONSTRUCTOR
Square::Square()
{
	m_type = "square";
	sprite = Sprite::create("Obstacles/square.png");
	mArray[0] = cocos2d::Vec2(-8 / TIscale, -11 / TIscale);
	mArray[1] = cocos2d::Vec2(-11 / TIscale, -8 / TIscale);
	mArray[2] = cocos2d::Vec2(-11 / TIscale, 8 / TIscale);
	mArray[3] = cocos2d::Vec2(-8 / TIscale, 11 / TIscale);
	mArray[4] = cocos2d::Vec2(8 / TIscale, 11 / TIscale);
	mArray[5] = cocos2d::Vec2(11 / TIscale, 8 / TIscale);
	mArray[6] = cocos2d::Vec2(11 / TIscale, -8 / TIscale);
	mArray[7] = cocos2d::Vec2(8 / TIscale, -11 / TIscale);
	mArray[8] = cocos2d::Vec2(-8 / TIscale, -11 / TIscale);
	physicsBody = cocos2d::PhysicsBody::createPolygon(mArray, 9, PhysicsMaterial(1, 1, 1));
	sprite->setPhysicsBody(physicsBody);
	physicsBody->setCollisionBitmask(4);
	physicsBody->setContactTestBitmask(true);
	physicsBody->setVelocityLimit(15);
	physicsBody->setAngularDamping(10);
}
Square::~Square()
{

}

//RETURN SPRITE POINTER
cocos2d::Sprite* Square::getSprite()
{
	return sprite;
}

//RETURN PHYSICS BODY POINTER
cocos2d::PhysicsBody* Square::getPhysicsBody()
{
	return physicsBody;
}

//MAIN ANIMATION FOR OBJECT
void Square::animate()
{
	for (int i = 0; i < 6; i++)
	{
		auto frame = SpriteFrame::create("Obstacles/squareSprite.png", Rect(50 * i / TIscale, 0 / TIscale, 50 / TIscale, 50 / TIscale));
		animationFrames.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(animationFrames, 0.1f);
	auto animate = Animate::create(animation);
	sprite->runAction(RepeatForever::create(animate));
}

//OBJECT EXPODES ON CONTACT
void Square::explode()
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
std::string Square::returnType()
{
	return m_type;
}

//RETURN OBJECT STATUS - ALIVE | DESTROYED - OBJECT EXPLODES ON CONTACT
bool Square::isDestoryed()
{
	return destroyed;
}


//DELETE OBJECT _ GARBAGE COLLECTION
void Square::DisposeObject()
{
	delete this;
}