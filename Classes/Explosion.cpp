#include "Explosion.h"

//CONSTRUCTOR & DE-CONSTRUCTOR
Explosion::Explosion()
{
	m_type = "explosion";
	sprite = cocos2d::Sprite::create("Particles/explosionTest.png");
};
Explosion::~Explosion() {};

//RETURN SPRITE POINTER
cocos2d::Sprite * Explosion::getSprite()
{
	return sprite;
}

//MAIN ANIMATION FOR OBJECT
void Explosion::animate()
{
}

//OBJECT EXPODES ON CONTACT
void Explosion::explode()
{
	for (int i = 0; i < 12; i++)
	{
		auto frame = cocos2d::SpriteFrame::create("Particles/explosionSprite.png", cocos2d::Rect(20 * i / TIscale, 0 / TIscale, 20 / TIscale, 20 / TIscale));
		animationFrames.pushBack(frame);
	}
	auto animation = cocos2d::Animation::createWithSpriteFrames(animationFrames, 0.05f);
	auto animate = cocos2d::Animate::create(animation);
	sprite->runAction(cocos2d::CCSequence::create(cocos2d::Repeat::create(animate, 1), cocos2d::CallFunc::create([this]() { isDestoryed(); }), NULL));
}

//RETURN THE OBJECT TYPE - STRING
std::string Explosion::returnType()
{
	return std::string();
}

//RETURN OBJECT STATUS - ALIVE | DESTROYED - OBJECT EXPLODES ON CONTACT
bool Explosion::isDestoryed()
{
	return destroyed;
}

//DELETE OBJECT _ GARBAGE COLLECTION
void Explosion::DisposeObject()
{
	delete this;
}