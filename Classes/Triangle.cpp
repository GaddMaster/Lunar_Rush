//SAMUAL SWEENEY - TRIANGLE CPP OBJECT INHERITS BASE OBJECT - OBSTACLES
#include "Triangle.h"

USING_NS_CC;

//CONSTRUCTOR & DE-CONSTRUCTOR
Triangle::Triangle()
{
	m_type = "triangle";
	sprite = Sprite::create("Obstacles/triangle.png");
	mArray[0] = Vec2(-10 / TIscale, -11 / TIscale);
	mArray[1] = Vec2(-13 / TIscale, -7 / TIscale);
	mArray[2] = Vec2(-3 / TIscale, 13 / TIscale);
	mArray[3] = Vec2(3 / TIscale, 13 / TIscale);
	mArray[4] = Vec2(13 / TIscale, -7 / TIscale);
	mArray[5] = Vec2(10 / TIscale, -11 / TIscale);
	mArray[6] = Vec2(-10 / TIscale, -11 / TIscale);
	physicsBody = PhysicsBody::createPolygon(mArray, 7, PhysicsMaterial(1, 1, 1));
	sprite->setPhysicsBody(physicsBody);
	physicsBody->setCollisionBitmask(4);
	physicsBody->setContactTestBitmask(true);
	physicsBody->setVelocityLimit(15);
	physicsBody->setAngularDamping(10);
}
Triangle::~Triangle()
{

}

//RETURN SPRITE POINTER
cocos2d::Sprite* Triangle::getSprite()
{
	return sprite;
}

//RETURN PHYSICS BODY POINTER
cocos2d::PhysicsBody* Triangle::getPhysicsBody()
{
	return physicsBody;
}

//MAIN ANIMATION FOR OBJECT
void Triangle::animate()
{
	for (int i = 0; i < 6; i++)
	{
		auto frame = SpriteFrame::create("Obstacles/triangleSprite.png", Rect(50 * i / TIscale, 0 / TIscale, 50 / TIscale, 50 / TIscale));
		animationFrames.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(animationFrames, 0.1f);
	auto animate = Animate::create(animation);
	sprite->runAction(RepeatForever::create(animate));
}

//OBJECT EXPODES ON CONTACT
void Triangle::explode()
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
std::string Triangle::returnType()
{
	return m_type;
}

//RETURN OBJECT STATUS - ALIVE | DESTROYED - OBJECT EXPLODES ON CONTACT
bool Triangle::isDestoryed()
{
	return destroyed;
}


//DELETE OBJECT _ GARBAGE COLLECTION
void Triangle::DisposeObject()
{
	delete this;
}