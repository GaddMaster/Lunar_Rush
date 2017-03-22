//SAMANTHA MARAH
//K00200782

//SAMUEL MACSWEENEY
//K00200955

#ifndef SECOND_WORLD_H
#define SECOND_WORLD_H

#define COCOS2D_DEBUG 1

#include "cocos2d.h"

#include <string>
#include <iostream>
#include <stdio.h>
#include <time.h>

//ALL PICKUP OBJECT HEADER FILES INCLUDED - SAMANTHA MARAH
#include "PickUps.h"
#include "ThrusterPickup.h"
#include "HealthPickup.h"
#include "WeaponShieldPickup.h"

#include "Vehicle.h"
#include "DirectionWayPoint.h"
#include "GameObjectPhysics.h"

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
		void finish_line();

		//PLAYER SHIP FUNCTION
		void vehicleObjects();

		//THRUSTER PICKUP FUNCTION
		void thruster_pickup();

		//HEALTH PICKUP FUNCTION
		void health_pickup();

		//WEAPON/SHIELD PICKUP FUNCTION
		void weapon_shield_pickup();

		//CIRCLE CIRCUIT FUNCTION
		void circle_circuit();

		//SQUARE CIRCUIT FUNCTION 
		void square_circuit();

		//TURRET BODY FUNCTION
		void turret_body();

		//TURRET HEAD FUNCTION
		void turret_head();

		//TURRET FIRE FUNCTION
		void turret_fire();

		//HUD LAYER FUNCTION
		void hud_layer();

		//END RACE FUNCTION
		void end_race();

		//DIRECTOR AND WINDOW ORIGIN
		void director();

		//PHYSICSWORLD
		cocos2d::PhysicsWorld *sceneWorld;

		void SetPhysicsWorld(cocos2d::PhysicsWorld *world)
		{
			sceneWorld = world;
		};

		//SPRITES
		cocos2d::Sprite* track_background;
		cocos2d::Sprite* track_in_sprite;
		cocos2d::Sprite* track_island_sprite;
		cocos2d::Sprite* track_out_sprite;
		cocos2d::Sprite* player_ship_sprite;
		cocos2d::Sprite* finish_line_detector_sprite;
		cocos2d::Sprite* hud_layer_template_sprite;
		cocos2d::Sprite* background_bar_sprite1;
		cocos2d::Sprite* background_bar_sprite2;
		cocos2d::Sprite* health_bar_sprite;
		cocos2d::Sprite* thruster_bar_sprite;
		cocos2d::Sprite* damage_bar_sprite1;
		cocos2d::Sprite* damage_bar_sprite2;
		cocos2d::Sprite* speed_indicator;
		Vehicle* playerVehicleObject;
		Vehicle* enemyOneVehicleObject;

		//PHYSICS BODIES
		cocos2d::PhysicsBody* track_in_physics;
		cocos2d::PhysicsBody* track_island_physics;
		cocos2d::PhysicsBody* track_out_physics;
		cocos2d::PhysicsBody* player_ship_physics;
		cocos2d::PhysicsBody* contact_a;
		cocos2d::PhysicsBody* contact_b;
		cocos2d::PhysicsBody* finish_line_detector_physics;

		//ARRAYS
		cocos2d::Vec2 track_in_array[28];
		cocos2d::Vec2 track_island_array[4];
		cocos2d::Vec2 track_out_array[38];

		std::vector<cocos2d::Vec2> wayPointVectors;
		std::vector<cocos2d::Vec2*>::const_iterator iterator;
		cocos2d::Vector<Node*> pausedNodes;
		std::vector<std::tuple< std::vector<cocos2d::Vec2*>, std::vector<cocos2d::Vec2*>, std::vector<cocos2d::Vec2*>>> wayPointVectorsTuple;
		std::vector<std::tuple< std::vector<cocos2d::Vec2*>, std::vector<cocos2d::Vec2*>, std::vector<cocos2d::Vec2*> > >::iterator iteratorTuple;

		//AI POINTS
		cocos2d::Vec2 WayPoints[62][3];//VECTOR TO CAPTURE ALL OUR WAY POOINTS FOR AI
		bool WayPoint[61];//BOOLEAN FOR TRACKING WHICH WAY POINT WE ARE ON
		int wayPointCounter;//DECIDES WHICH WAY POINT IS CURRENTLY ON
		int enemyOneWayPointSkill;//DECIDES HOW TIGHT THE AI CUTS AROUND CORNER. 0=HARD - 1=MEDIUM, 2=EASY
		cocos2d::Sprite* wayPointSprite;//SPRITE FOR VISUAL BEBUGGING
		cocos2d::Rect wayPointRect_I;//RECTANGLE I INTERSECTION CHECKING
		cocos2d::Rect wayPointRect_II;//RECTANGLE II INTERSECTION CHECKING

		//DIRECTIONAL VECTORS, INT & WAY POINT OBJECTS
		std::vector<DirectionWayPoint*> directionalWayPoints;
		int directionalTriggerPoint[44];
		std::vector<int> directionalTriggers;

		//LISTENERS
		cocos2d::EventListenerKeyboard* keyboardEvent;
		cocos2d::EventListenerKeyboard* eventListener;

		//VARIABLES
		float playerRotationAngle;
		float enemyOneRotationAngle;
		float time = 0;
		float velocity = 0;
		float TIscale = 1.705;
		float player_transformed_angle;
		bool player_drive = true;
		bool player_fire;
		bool slow_down = false;
		bool lap_detector = false;
		int collisions = 0;
		int lap_counter = 0;
		int player_ship_health = 100;
		int player_ship_thruster_fuel = 100;
		int player_ship_speed = 100;
		int pickupID;

		//ACTIONS
		cocos2d::RepeatForever* repeat;
		cocos2d::RotateBy* rotate;
		cocos2d::RotateTo* setRotationAction;

		//POINTS
		cocos2d::Vec2 origin;
		cocos2d::Vec2 player_velocity_point;
		cocos2d::Vec2 player_bullet_spawn_point;
		cocos2d::Vec2 player_bullet_fire_point;
		cocos2d::Vec2 enemyOneCurrentWayPoint;

		//SIZE
		cocos2d::Size visibleSize;

		//HUD
		cocos2d::LayerGradient* HUD;

		//LABEL
		cocos2d::Label* lap_number;
		cocos2d::Label* timer;

		//PROGRESS TIMERS
		cocos2d::ProgressTimer* health_bar_timer;
		cocos2d::ProgressTimer* damage_bar_timer1;
		cocos2d::ProgressTimer* thruster_bar_timer;
		cocos2d::ProgressTimer* damage_bar_timer2;
		cocos2d::ProgressTimer* speed_indicator_timer;

		//DELAY TIME
		cocos2d::DelayTime* delay;

		std::vector<PickUps*> weaponPickups;
		std::vector<PickUps*>::iterator it;
		std::vector<Vehicle*> vehicles;
};
#endif
