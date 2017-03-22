#include "DirectionWayPoint.h"

USING_NS_CC;

//CONSTRUCTOR & DE-CONSTRUCTOR
DirectionWayPoint::DirectionWayPoint():
m_id(0),
m_active(true),
mDelay(0.2f),
TIscale(1.7068)
{
	
}
DirectionWayPoint::~DirectionWayPoint()
{

}

////GET - SET - ID - ACTIVE - BOOLEAN / ID FOR VARIOUS USES - AI - TRACK DIRECTION - DRIVING - CHANGING LANES - MORE
void DirectionWayPoint::setID(bool active, int id, std::string type)
{
	m_id = id;

	if (type == "1by2")
		sprite = Sprite::create("TrackOne/WayPoints/Directional/1by2.png");
	else if (type == "5by1")
		sprite = Sprite::create("TrackOne/WayPoints/Directional/5by1.png");
	else if (type == "1by3")
		sprite = Sprite::create("TrackOne/WayPoints/Directional/1by3.png");
	else if (type == "2by1")
		sprite = Sprite::create("TrackOne/WayPoints/Directional/2by1.png");
	else if (type == "2by2")
		sprite = Sprite::create("TrackOne/WayPoints/Directional/2by2.png");
	else if (type == "2by3")
		sprite = Sprite::create("TrackOne/WayPoints/Directional/2by3.png");
	else if (type == "2by4")
		sprite = Sprite::create("TrackOne/WayPoints/Directional/2by4.png");
	else if (type == "3by1")
		sprite = Sprite::create("TrackOne/WayPoints/Directional/3by1.png");
	else if (type == "3by2")
		sprite = Sprite::create("TrackOne/WayPoints/Directional/3by2.png");
	else if (type == "3by3")
		sprite = Sprite::create("TrackOne/WayPoints/Directional/3by3.png");
	else if (type == "4by1")
		sprite = Sprite::create("TrackOne/WayPoints/Directional/4by1.png");
	else if (type == "5by2")
	{
		sprite = Sprite::create("TrackOne/WayPoints/Directional/5by2.png");
		animate();
	}
	else if (type == "6by2")
		sprite = Sprite::create("TrackOne/WayPoints/Directional/6by2.png");
	else
		sprite = Sprite::create("TrackOne/WayPoints/Directional/2by2.png");

	active = false;
}
int DirectionWayPoint::getID()
{
	return m_id;
}
bool DirectionWayPoint::getActive()
{
	return m_active;
}
void DirectionWayPoint::setActive(bool active)
{
	m_active = active;
}

//GET SPRITE OBJECT POINTER
cocos2d::Sprite* DirectionWayPoint::getSprite()
{
	return sprite;
}

//TRACK WAY POINT ANIMATION START
void DirectionWayPoint::animate()
{
	for (int i = 0; i < 8; i++)
	{
		auto frame = SpriteFrame::create("TrackOne/WayPoints/Directional/5by2Sprite.png", Rect(500 * i / TIscale, 0 / TIscale, 500 / TIscale, 200 / TIscale));
		animationFrames.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(animationFrames, mDelay);
	auto animate = Animate::create(animation);
	sprite->runAction(RepeatForever::create(animate));
}

//SET BLINKING SPEED OF TRACK WAY POINTS
void DirectionWayPoint::setAnimateSpeed(float delay)
{
	mDelay = delay;
	animate();//RESET TRACK WAY POINT ANIMATION
}
