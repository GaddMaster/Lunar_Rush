//SAMUEL
#ifndef SQUARECIRCUIT_H
#define SQUARECIRCUIT_H

#include "cocos2d.h"
#include "SecondWorld.h"

class SquareCircuit : public cocos2d::Sprite
{
public:

	SquareCircuit();
	~SquareCircuit();

	//PASS IN SECONDWORLD* SCENE4 TO GAIN ACCESS TO THE SECONDWORLD SCENE
	void init_SquareCircuit(SecondWorld* scene4SecondWorldScene);
	float set_SquareCircuit_position(float x, float y);

	cocos2d::Sprite* SquareCircuitSprite;
	cocos2d::PhysicsBody* SquareCircuitPhysicsBody;

	float m_position_x;
	float m_position_y;

	CREATE_FUNC(SquareCircuit);

};

#endif