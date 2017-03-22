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
		static std::map<cocos2d::EventKeyboard::KeyCode,std::chrono::high_resolution_clock::time_point> keys;

		//ADD TRACT TO SCENE
		void addTrack();

		//AI TRACK WAY POINTS FUNCTION
		void AIWayPoints();

		//TRACK WAY POINTS 
		void trackWayPoints();

		//ADD VEHICLE OBJECTS
		void vehicleObjects();

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
		cocos2d::PhysicsBody* trackInPhysics;
		cocos2d::PhysicsBody* trackOutPhysics;
		cocos2d::PhysicsBody* trackInLetPhyscis;
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
		int lapN = -1;

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

		//DIRECTIONAL VECTORS, INT & WAY POINT OBJECTS
		std::vector<DirectionWayPoint*> directionalWayPoints;
		int directionalTriggerPoint[44];
		std::vector<int> directionalTriggers;

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
		cocos2d::Label* lapCount;
		
		//CAMERA - WORKING ON IT
		cocos2d::Sprite* sprite;
		cocos2d::Camera* camera;
		cocos2d::Vec3 spritePos;

		//TIMER
		float time;
		cocos2d::Label* timer;
		cocos2d::DelayTime* delay;
		Explosion* explosion;
};
#endif
