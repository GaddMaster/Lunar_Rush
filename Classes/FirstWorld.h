//SAMANTHA MARAH
//K00200782

//SAMUEL MACSWEENEY
//K00200955

//DANIEL GADD
//K00202350

#ifndef _FIRST_WORLD_H_
#define _FIRST_WORLD_H_

#define COCOS2D_DEBUG 1

#include "cocos2d.h"
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include "Triangle.h"
#include "Circle.h"
#include "Square.h"
#include "Vehicle.h"
#include "DirectionWayPoint.h"
#include "GameObject.h"
#include "GameObjectPhysics.h"
#include "Rocket.h"
#include "Explosion.h"
#include "ExplosionLarge.h"
#include "FinishLine.h"

//ALL PICKUP OBJECT HEADER FILES INCLUDED - SAMANTHA MARAH
#include "PickUps.h"
#include "ThrusterPickup.h"
#include "HealthPickup.h"
#include "WeaponShieldPickup.h"

class FirstWorld : public cocos2d::Layer
{
public:////////////////////////////////////////////////////////////////////////////////////

	   //CONSTRUCTOR AND DE-CONSTRUCTOR
	FirstWorld();
	~FirstWorld();

	//THERE IS NO ID IN CPP. HENCH WE RETURN THE CLASS INSTANCE POINTER
	static cocos2d::Scene* createScene();

	//INITIAL FUNCTION
	virtual bool init();

	//TOUCH FUCNTIONS
	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);

	//UPDATE FUCNTION
	void update(float) override;

	//SELECTOR CALL BACK
	void menuCloseCallback(cocos2d::Ref* pSender);

	//IMPLEMENT THE STATIC CREATE METHOD MANUALLY
	CREATE_FUNC(FirstWorld);

	//KEYBOARD FUCNTIONS
	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
	double keyPressedDuration(cocos2d::EventKeyboard::KeyCode);
	static std::map<cocos2d::EventKeyboard::KeyCode, std::chrono::high_resolution_clock::time_point> keys;

	//ADD TRACT TO SCENE
	void addTrack();

	//AI TRACK WAY POINTS FUNCTION
	void AIWayPoints();

	//FINISH LINE FUNCTION
	void finishLine();

	//TRACK WAY POINTS 
	void trackWayPoints();

	//ADD VEHICLE OBJECTS
	void vehicleObjects();

	//THRUSTER PICKUP FUNCTION
	void thrusterPickup();

	//HEALTH PICKUP FUNCTION
	void healthPickup();

	//WEAPON/SHIELD PICKUP FUNCTION
	void weaponShieldPickup();

	//TRACK OBSTACLES
	void obstacles();

	//EVENT LISTENERS
	void eventListeners();

	//HUD DISPLAY
	void hud();

	//DIRECTOR AND WINDOW ORIGIN
	void director();

	//LABELS - BACKWARDS NOTIFICATION
	void labels();

	//END RACE FUNCTION
	void endRace();

	//CAMERA
	void moveWorld();

private:////////////////////////////////////////////////////////////////////////////////////

		//SCENE & LAYERS
	cocos2d::PhysicsWorld *sceneWorld;
	void SetPhysicsWorld(cocos2d::PhysicsWorld *world) { sceneWorld = world; };

	//OBJECT COLLISIONS
	bool onContactBegin(cocos2d::PhysicsContact &contact);

	//VEHICLE OBJECTS, SPRITES, BODIES & ANIMATIONS
	cocos2d::Sprite* trackInSprite;
	cocos2d::Sprite* trackOutSprite;
	cocos2d::Sprite* trackInLetSprite;
	cocos2d::Sprite* detectorSprite;
	cocos2d::Sprite* preDetector1Sprite;
	cocos2d::Sprite* preDetector2Sprite;
	cocos2d::Sprite* hudTemplatesprite;
	cocos2d::Sprite* backgroundBarSprite1;
	cocos2d::Sprite* backgroundBarSprite2;
	cocos2d::Sprite* healthBarSprite;
	cocos2d::Sprite* thrusterBarSprite;
	cocos2d::Sprite* damageBarSprite1;
	cocos2d::Sprite* damageBarSprite2;
	cocos2d::Sprite* speedIndicator;
	cocos2d::PhysicsBody* trackInPhysics;
	cocos2d::PhysicsBody* trackOutPhysics;
	cocos2d::PhysicsBody* trackInLetPhyscis;
	cocos2d::PhysicsBody* contactA;
	cocos2d::PhysicsBody* contactB;
	cocos2d::PhysicsBody* detectorPhysics;
	cocos2d::PhysicsBody* preDetector1Physics;
	cocos2d::PhysicsBody* preDetector2Physics;
	Vehicle* playerVehicleObject;
	Vehicle* enemyOneVehicleObject;
	Vehicle* enemyTwoVehicleObject;
	Vehicle* enemyThreeVehicleObject;

	//LISTENERS
	cocos2d::EventListenerKeyboard* keyboardEvent;
	cocos2d::EventListenerKeyboard* eventListener;
	cocos2d::EventListenerTouchOneByOne* touchListener;
	cocos2d::EventListenerPhysicsContact* contactListenerBegin;

	//VARIABLES
	cocos2d::Size visibleSize;
	float playerRotationAngle;
	float enemyOneRotationAngle;
	float TIscale;//SEEMS IMAGE ACTUAL PIXEL SIZE AND PHYSICS BODY POINTS ARE OFF BY 1.7%
	cocos2d::Vec2 enemyOneCurrentWayPoint;
	bool backwards = false;
	float weaponTimer;
	bool activeWeaponTimer;
	bool lapDetector1 = false;
	bool lapDetector2 = false;
	int lapCounter = 0;
	int playerHealth = 100;
	int playerThrusterfuel = 100;
	int pickupID;

	//ARRAYS, VECTOR AND LISTS
	cocos2d::Vec2 trackInArray[63];
	cocos2d::Vec2 trackOutArray[59];
	cocos2d::Vec2 trackInLetArray[5];
	std::vector<cocos2d::Vec2> wayPointVectors;

	//AI POINTS
	cocos2d::Vec2 WayPoints[62][3];//VECTOR TO CAPTURE ALL OUR WAY POOINTS FOR AI
	bool WayPoint[61];//BOOLEAN FOR TRACKING WHICH WAY POINT WE ARE ON
	int wayPointCounter;//DECIDES WHICH WAY POINT IS CURRENTLY ON
	int enemyOneWayPointSkill;//DECIDES HOW TIGHT THE AI CUTS AROUND CORNER. 0=HARD - 1=MEDIUM, 2=EASY
	cocos2d::Sprite* wayPointSprite;//SPRITE FOR VISUAL BEBUGGING
	cocos2d::Rect wayPointRect_I;//RECTANGLE I INTERSECTION CHECKING
	cocos2d::Rect wayPointRect_II;//RECTANGLE II INTERSECTION CHECKING

	//CUSTOM VELOCITY DAMPING FOR ALL GAME OBJECT (OBSTACLES)
	std::vector<GameObjectPhysics*> objects;
	std::vector<Vehicle*> vehicles;
	std::vector<GameObject*> projectiles;
	std::vector<PickUps*> weaponPickups;
	std::vector<PickUps*>::iterator it;

	//DIRECTIONAL VECTORS, INT & WAY POINT OBJECTS
	std::vector<DirectionWayPoint*> directionalWayPoints;
	int directionalTriggerPoint[44];
	std::vector<int> directionalTriggers;

	//FINISH LINE VECTORS - SAMANTHA
	std::vector<int> finishLineTriggers;
	std::vector<FinishLine*> finishLines;

	//HUD
	cocos2d::LayerGradient* HUD;

	//ACTIONS
	cocos2d::RepeatForever* repeat;
	cocos2d::RotateBy* rotate;
	cocos2d::RotateTo* setRotationAction;

	//POINTS - ORIGIN OF DISPLAY
	cocos2d::Vec2 origin;

	//LABELS
	cocos2d::Label* backwardsLabel;
	cocos2d::Label* speed;
	cocos2d::Label* slowDownStatus;
	cocos2d::Label* angle;
	cocos2d::Label* weaponLabel;
	cocos2d::Label* lapNumber;

	//CAMERA - WORKING ON IT
	cocos2d::Sprite* sprite;
	cocos2d::Camera* camera;
	cocos2d::Vec3 spritePos;

	//TIMER
	float time;
	cocos2d::Label* timer;
	cocos2d::DelayTime* delay;
	Explosion* explosion;

	cocos2d::ProgressTimer* healthTimer;
	cocos2d::ProgressTimer* damageTimer1;
	cocos2d::ProgressTimer* thrusterTimer;
	cocos2d::ProgressTimer* damageTimer2;
	cocos2d::ProgressTimer* speedTimer;
};
#endif
