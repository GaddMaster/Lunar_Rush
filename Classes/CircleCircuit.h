//SAMUEL
#ifndef CIRCLECIRCUIT_H
#define CIRCLECIRCUIT_H

#include "cocos2d.h"
#include "FirstWorld.h"
#include "SecondWorld.h"

class CircleCircuit : public cocos2d::Sprite
{
	public:

		CircleCircuit();
		~CircleCircuit();

		//PASS IN SECONDWORLD* SCENE4 TO GAIN ACCESS TO THE SECONDWORLD SCENE
		void init_CircleCircuit(SecondWorld* SecondWorldScene);
		float set_CircleCircuit_position(float x, float y);

		cocos2d::Sprite* CircleCircuitSprite;
		cocos2d::PhysicsBody* CircleCircuitPhysicsBody;

		float m_position_x;
		float m_position_y;

		CREATE_FUNC(CircleCircuit);

};

#endif