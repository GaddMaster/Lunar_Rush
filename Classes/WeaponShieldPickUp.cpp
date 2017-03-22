//SAMANTHA MARAH
//K00200782

//Includes The WeaponShieldPickup Header File
#include "WeaponShieldPickup.h"

USING_NS_CC;

//WeaponShieldPickup Constructor
WeaponShieldPickup::WeaponShieldPickup()
{
	//Set The Image For The WeaponShieldPickup Sprite
	sprite = Sprite::create("PickUps/weaponshieldpickup.png");

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
	physicsBody->setCollisionBitmask(8);

	//Sets The Physics Body Contact To True. This Makes The Sprite Collidable
	physicsBody->setContactTestBitmask(true);

	//Sets The Physics Body Dynamics To False. This Makes The Sprite Immovable
	physicsBody->setDynamic(false);

	//Sets The Physics Body Onto The Sprite Itself
	sprite->setPhysicsBody(physicsBody);
};

//WeaponShieldPickup Destructor
WeaponShieldPickup::~WeaponShieldPickup()
{};

//Returns The WeaponShieldPickup Sprite
cocos2d::Sprite* WeaponShieldPickup::getSprite()
{
	return sprite;
};

//Returns The WeaponShieldPickup Physics Body
cocos2d::PhysicsBody* WeaponShieldPickup::getPhysicsBody()
{
	return physicsBody;
};

//Rotates The WeaponShieldPickup
void WeaponShieldPickup::rotate()
{
	//Creates The Rotate Function That Rotates 350 Degrees In Two Seconds
	auto rotate = RotateBy::create(2.0f, 350.f);
	sprite->runAction(RepeatForever::create(rotate));
};

void WeaponShieldPickup::seeID()
{
	CCLOG("WeaponShield Pickup ID: %d", m_ID);
};