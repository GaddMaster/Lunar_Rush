#include "ExplosionLarge.h"

//CONSTRUCTOR & DE-CONSTRUCTOR
ExplosionLarge::ExplosionLarge()
{
	m_type = "ExplosionLarge";
	sprite = cocos2d::Sprite::create("Particles/explosionTest.png");
};
ExplosionLarge::~ExplosionLarge() {};

//RETURN SPRITE POINTER
cocos2d::Sprite * ExplosionLarge::getSprite()
{
	return sprite;
}

//MAIN ANIMATION FOR OBJECT
void ExplosionLarge::animate()
{
}

//OBJECT EXPODES ON CONTACT
void ExplosionLarge::explode()
{
	for (int i = 0; i < 11; i++)
	{
		auto frame = cocos2d::SpriteFrame::create("Particles/ExplosionLarge.png", cocos2d::Rect(80 * i / TIscale, 0 / TIscale, 80 / TIscale, 80 / TIscale));
		animationFrames.pushBack(frame);
	}
	auto animation = cocos2d::Animation::createWithSpriteFrames(animationFrames, 0.05f);
	auto animate = cocos2d::Animate::create(animation);
	sprite->runAction(cocos2d::CCSequence::create(cocos2d::Repeat::create(animate, 1), cocos2d::CallFunc::create([this]() { isDestoryed(); }), NULL));
}

//RETURN THE OBJECT TYPE - STRING
std::string ExplosionLarge::returnType()
{
	return std::string();
}

//RETURN OBJECT STATUS - ALIVE | DESTROYED - OBJECT EXPLODES ON CONTACT
bool ExplosionLarge::isDestoryed()
{
	return destroyed;
}

//DELETE OBJECT _ GARBAGE COLLECTION
void ExplosionLarge::DisposeObject()
{
	delete this;
}