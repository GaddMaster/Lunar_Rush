#ifndef DIRECTIONWAYPOINT_H
#define DIRECTIONWAYPOINT_H

#include "cocos2d.h"

class DirectionWayPoint
{
public:

	DirectionWayPoint();
	~DirectionWayPoint();

	void setID(bool active, int id, std::string type);
	int getID();
	bool getActive();
	void setActive(bool active);
	cocos2d::Sprite* getSprite();
	void animate();
	void setAnimateSpeed(float delay);

private:
	int m_id;
	bool m_active;
	float TIscale;
	cocos2d::Vector<cocos2d::SpriteFrame*> animationFrames;
	cocos2d::Sprite* sprite;
	float mDelay;
};

#endif