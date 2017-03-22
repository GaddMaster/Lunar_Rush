//SAMANTHA MARAH - K00200782

#include "LandMine.h"

USING_NS_CC;

//CONSTRUCTOR & DE-CONSTRUCTOR
LandMine::LandMine()
{
	m_type = "mine";
	sprite = Sprite::create("Weapons/Mine/mine.png");
};
LandMine::~LandMine(){};

//RETURN SPRITE POINTER
cocos2d::Sprite* LandMine::getSprite()
{
	return sprite;
}

//MAIN ANIMATION FOR OBJECT
void LandMine::animate()
{
	for (int i = 0; i < 6; i++)
	{
		auto frame = SpriteFrame::create("Weapons/Mine/mineSprite.png", Rect(20 * i / TIscale, 0 / TIscale, 20 / TIscale, 20 / TIscale));
		animationFrames.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(animationFrames, 0.1f);
	auto animate = Animate::create(animation);
	sprite->runAction(RepeatForever::create(animate));
}

//OBJECT EXPODES ON CONTACT
void LandMine::explode()
{
	for (int i = 0; i < 10; i++)
	{
		auto frame = SpriteFrame::create("Particles/explosion_small.png", Rect(20 * i / TIscale, 0 / TIscale, 20 / TIscale, 20 / TIscale));
		animationFrames.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(animationFrames, 0.1f);
	auto animate = Animate::create(animation);
	sprite->runAction(cocos2d::CCSequence::create(cocos2d::Repeat::create(animate, 1), cocos2d::CallFunc::create([this]() { destroyed = true; }), NULL));
}

//RETURN THE OBJECT TYPE - STRING
std::string LandMine::returnType()
{
	return std::string();
}

//RETURN OBJECT STATUS - ALIVE | DESTROYED - OBJECT EXPLODES ON CONTACT
bool LandMine::isDestoryed()
{
	return destroyed;
}

//DELETE OBJECT _ GARBAGE COLLECTION
void LandMine::DisposeObject()
{
	delete this;
}