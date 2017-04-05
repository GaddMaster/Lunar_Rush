//SAMANTHA MARAH
//K00200782

//SAMUEL MACSWEENEY
//K00200955

//DANIEL GADD
//K00202350

#ifndef SECOND_WORLD_H
#define SECOND_WORLD_H

#define COCOS2D_DEBUG 1

#include "cocos2d.h"

#include <string>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include <vector>

//ALL PICKUP OBJECT HEADER FILES INCLUDED - SAMANTHA MARAH
#include "PickUps.h"
#include "ThrusterPickup.h"
#include "HealthPickup.h"
#include "WeaponShieldPickup.h"
#include "FinishLine.h"

//INCLUDE VEHICLE OBJECTS, WAY POINTS, GAME BASE OBJECTS AND EXPLOSION OBJECTS - DANIEL
#include "Vehicle.h"
#include "DirectionWayPoint.h"
#include "GameObjectPhysics.h"
#include "GameObject.h"
#include "Explosion.h"
#include "ExplosionLarge.h"

class SecondWorld : public cocos2d::Layer
{
public:
	SecondWorld();
	~SecondWorld();

	static cocos2d::Scene* createScene();

	CREATE_FUNC(SecondWorld);

	virtual bool init();

	//LISTENERS FUNCTION
	void listeners();

	//SELECTOR CALL BACK
	void menuCloseCallback(cocos2d::Ref* pSender);

	//TOUCH FUCNTIONS
	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);

	//OBJECT COLLISIONS
	bool onContactBegin(cocos2d::PhysicsContact& contact);

	//KEYBOARD FUCNTIONS
	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
	double keyPressedDuration(cocos2d::EventKeyboard::KeyCode);
	static std::map<cocos2d::EventKeyboard::KeyCode, std::chrono::high_resolution_clock::time_point> keys;

	//UPDATE FUCNTION
	void update(float) override;

	//TRACK FUNCTION
	void track();

	//AI WAYPOINTS
	void AIWayPoints();

	//FINISH LINE FUNCTION
	void finishLine();

	//PLAYER SHIP FUNCTION
	void vehicleObjects();

	//THRUSTER PICKUP FUNCTION
	void thrusterPickup();

	//HEALTH PICKUP FUNCTION
	void healthPickup();

	//WEAPON/SHIELD PICKUP FUNCTION
	void weaponShieldPickup();

	//CIRCLE CIRCUIT FUNCTION
	void circleCircuit();

	//SQUARE CIRCUIT FUNCTION 
	void squareCircuit();

	//TRIANGLE CIRCUIT FUNCTION
	void triangleCircuit();

	//TURRET BODY FUNCTION
	void turretBody();

	//TURRET HEAD FUNCTION
	void turretHead();

	//TURRET FIRE FUNCTION
	void turretFire();

	//TURRET SHOOT FUNCTION
	void turretShoot(float delta);

	//HUD LAYER FUNCTION
	void hudLayer();

	//END RACE FUNCTION
	void endRace();

	//DIRECTOR AND WINDOW ORIGIN
	void director();

	//PHYSICSWORLD
	cocos2d::PhysicsWorld *sceneWorld;

	void SetPhysicsWorld(cocos2d::PhysicsWorld *world)
	{
		sceneWorld = world;
	};

	//SPRITES
	cocos2d::Sprite* trackBackground;
	cocos2d::Sprite* trackInsprite;
	cocos2d::Sprite* trackIslandsprite;
	cocos2d::Sprite* trackOutsprite;
	cocos2d::Sprite* hudTemplatesprite;
	cocos2d::Sprite* backgroundBarSprite1;
	cocos2d::Sprite* backgroundBarSprite2;
	cocos2d::Sprite* healthBarSprite;
	cocos2d::Sprite* thrusterBarSprite;
	cocos2d::Sprite* damageBarSprite1;
	cocos2d::Sprite* damageBarSprite2;
	cocos2d::Sprite* speedIndicator;
	cocos2d::Sprite* detectorSprite;
	cocos2d::Sprite* preDetector1Sprite;
	cocos2d::Sprite* preDetector2Sprite;

	Vehicle* playerVehicleObject;
	Vehicle* enemyOneVehicleObject;
	Vehicle* enemyTwoVehicleObject;
	Vehicle* enemyThreeVehicleObject;

	//PHYSICS BODIES
	cocos2d::PhysicsBody* trackInphysics;
	cocos2d::PhysicsBody* trackIslandphysics;
	cocos2d::PhysicsBody* trackOutphysics;
	cocos2d::PhysicsBody* contactA;
	cocos2d::PhysicsBody* contactB;
	cocos2d::PhysicsBody* detectorPhysics;
	cocos2d::PhysicsBody* preDetector1Physics;
	cocos2d::PhysicsBody* preDetector2Physics;

	//ARRAYS
	cocos2d::Vec2 trackInarray[29];
	cocos2d::Vec2 trackIslandarray[5];
	cocos2d::Vec2 trackOutarray[39];

	std::vector<cocos2d::Vec2> wayPointVectors;
	std::vector<cocos2d::Vec2*>::const_iterator iterator;
	cocos2d::Vector<Node*> pausedNodes;
	std::vector<std::tuple< std::vector<cocos2d::Vec2*>, std::vector<cocos2d::Vec2*>, std::vector<cocos2d::Vec2*>>> wayPointVectorsTuple;
	std::vector<std::tuple< std::vector<cocos2d::Vec2*>, std::vector<cocos2d::Vec2*>, std::vector<cocos2d::Vec2*> > >::iterator iteratorTuple;
	std::vector<GameObject*> projectiles;

	//AI POINTS
	cocos2d::Vec2 WayPoints[37][3];//VECTOR TO CAPTURE ALL OUR WAY POOINTS FOR AI
	bool WayPoint[37];//BOOLEAN FOR TRACKING WHICH WAY POINT WE ARE ON
	int wayPointCounter;//DECIDES WHICH WAY POINT IS CURRENTLY ON
	int enemyOneWayPointSkill;//DECIDES HOW TIGHT THE AI CUTS AROUND CORNER. 0=HARD - 1=MEDIUM, 2=EASY
	cocos2d::Sprite* wayPointSprite;//SPRITE FOR VISUAL BEBUGGING
	cocos2d::Rect wayPointRect_I;//RECTANGLE I INTERSECTION CHECKING
	cocos2d::Rect wayPointRect_II;//RECTANGLE II INTERSECTION CHECKING

	//DIRECTIONAL VECTORS, INT & WAY POINT OBJECTS
	std::vector<DirectionWayPoint*> directionalWayPoints;
	int directionalTriggerPoint[44];
	std::vector<int> directionalTriggers;

	//FINISH LINE VECTORS - SAMANTHA
	std::vector<int> finishLineTriggers;
	std::vector<FinishLine*> finishLines;

	//LISTENERS
	cocos2d::EventListenerKeyboard* keyboardEvent;
	cocos2d::EventListenerKeyboard* eventListener;
	cocos2d::EventListenerTouchOneByOne* touchListener;
	cocos2d::EventListenerPhysicsContact* contactListenerBegin;

	//VARIABLES
	float playerRotationAngle;
	float enemyOneRotationAngle;
	float time = 0;
	float velocity = 0;
	float TIscale = 1.705;
	bool lapDetector1 = false;
	bool lapDetector2 = false;
	int lapCounter = 0;
	int playerHealth = 100;
	int playerThrusterfuel = 100;
	int pickupID;
	float fireRate = 5;
	float weaponTimer;
	bool activeWeaponTimer;


	//ACTIONS
	cocos2d::RepeatForever* repeat;
	cocos2d::RotateBy* rotate;
	cocos2d::RotateTo* setRotationAction;

	//POINTS
	cocos2d::Vec2 origin;
	cocos2d::Vec2 enemyOneCurrentWayPoint;

	//SIZE
	cocos2d::Size visibleSize;

	//HUD
	cocos2d::LayerGradient* HUD;

	//LABEL
	cocos2d::Label* lapNumber;
	cocos2d::Label* timer;
	cocos2d::Label* backwardsLabel;
	cocos2d::Label* speed;
	cocos2d::Label* slowDownStatus;
	cocos2d::Label* angle;
	cocos2d::Label* weaponLabel;

	//PROGRESS TIMERS
	cocos2d::ProgressTimer* healthTimer;
	cocos2d::ProgressTimer* damageTimer1;
	cocos2d::ProgressTimer* thrusterTimer;
	cocos2d::ProgressTimer* damageTimer2;
	cocos2d::ProgressTimer* speedTimer;

	//DELAY TIME
	cocos2d::DelayTime* delay;

	std::vector<PickUps*> weaponPickups;
	std::vector<PickUps*>::iterator it;
	std::vector<Vehicle*> vehicles;
};
#endif