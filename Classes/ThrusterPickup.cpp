//SAMANTHA MARAH
//K00200782

//Includes The ThrusterPickup Header File
#include "ThrusterPickup.h"

USING_NS_CC;

//ThrusterPickup Constructor
ThrusterPickup::ThrusterPickup()
{
	//Set The Image For The ThrusterPickup Sprite
	sprite = Sprite::create("PickUps/thrusterrestore.png");

	//Sets The Anchor Point To The Middle Of The Sprite
	sprite->setAnchorPoint(Vec2(0.5, 0.5));

	//Sets The Size Scale Of The Sprite
	sprite->setScale(0.1);

	//Creates The Type Of Physics Body -> Box Physics Body Is Being Created Here
	physicsBody = PhysicsBody::createBox(sprite->getContentSize(), PhysicsMaterial(0, 0, 0));

	//Sets The Physics Body's Collision Bitmask Which Will Be Used When The Sprite
	//Is Collided With. Collision Bitmask Gives Me More Control Over What Happens When
	//The Sprite Is In Contact With Another Sprite. It Also Allows The Program To
	//Know What Sprite Has Collided With Another.
	physicsBody->setCollisionBitmask(6);

	//Sets The Physics Body Contact To True. This Makes The Sprite Collidable
	physicsBody->setContactTestBitmask(true);

	//Sets The Physics Body Dynamics To False. This Makes The Sprite Immovable
	physicsBody->setDynamic(false);

	//Sets The Physics Body Onto The Sprite Itself
	sprite->setPhysicsBody(physicsBody);
};

//ThrusterPickup Destructor
ThrusterPickup::~ThrusterPickup()
{};

//Returns The ThrusterPickup Sprite
cocos2d::Sprite* ThrusterPickup::getSprite()
{
	return sprite;
};

//Returns The ThrusterPickup Physics Body
cocos2d::PhysicsBody* ThrusterPickup::getPhysicsBody()
{
	return physicsBody;
};

//Rotates The ThrusterPickup
void ThrusterPickup::rotate()
{
	//Creates The Rotate Function That Rotates 350 Degrees In Two Seconds
	auto rotate = RotateBy::create(2.0f, 350.f);
	sprite->runAction(RepeatForever::create(rotate));
};