//SAMANTHA MARAH
//K00200782

//INCLUDE THE FINISH LINE HEADER
#include "FinishLine.h"

USING_NS_CC;

////CONSTRUCTOR & DE-CONSTRUCTOR
FinishLine::FinishLine()
{
	sprite = Sprite::create("FinishLine/8by1.png");
};
FinishLine::~FinishLine()
{}

cocos2d::Sprite* FinishLine::getSprite()
{
	return sprite;
}

int FinishLine::returnID()
{
	return m_id;
}

void FinishLine::setID(int ID)
{
	m_id = ID;
}

int FinishLine::getID()
{
	return m_id;
}

bool FinishLine::getActive()
{
	return m_active;
}

void FinishLine::setActive(bool status)
{
	m_active = status;
}

