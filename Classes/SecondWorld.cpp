//SAMANTHA MARAH
//K00200782

//SAMUEL MACSWEENEY
//K00200955

#include "SecondWorld.h"

#include "FinishLine.h"

#include "CircleCircuit.h"
#include "SquareCircuit.h"

#include "TurretBody.h"
#include "TurretHead.h"
#include "TurretBullet.h"

#include "Bullet.h"
#include "Rocket.h"
#include "LandMine.h"

USING_NS_CC;

cocos2d::Scene* SecondWorld::createScene()
{
	auto SecondWorldScene = Scene::createWithPhysics();

	auto layer = SecondWorld::create();
	layer->SetPhysicsWorld(SecondWorldScene->getPhysicsWorld());

	//SecondWorldScene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	SecondWorldScene->getPhysicsWorld()->setGravity(Vec2(0, 0));

	SecondWorldScene->addChild(layer);

	return SecondWorldScene;
};

SecondWorld::SecondWorld()
{};

SecondWorld::~SecondWorld()
{};

//Z Ordering Global
//LAYER - Game	: 0
//Track ZIndex	: 1
//Finish Line	: 2
//Vehicles		: 3
//Weapons		: 4
//Particles		: 5
//WayPoints		: 2
//Turret Head	: 4
//Turret Body	: 3
//PickUps		: 3
//Obstacles		: 3
//
//
//
//LAYER - HUD	: 1
//
//
//
//
//
//
//

//Track Background = Layer 0 Done
//Finish Line = Layer 0 Done

//Track Walls = Layer 1 Done
//Finish Line Detector = Layer 1 Done
//Finish Line Pre-Detector = Layer 1 Done

//Player Ship = Layer 2 Done
//Circle Circuit = Layer 2 Done
//Square Circuit = Layer 2 Done
//Thruster Pickup = Layer 2 Done
//Health Pickup = Layer 2 Done
//Weapon/Shield Pickup = Layer 2 Done

//BITMASK
//Track Walls = Bitmask 1 Done
//Finish Line Detector = Bitmask 2 Done
//Finish Line Pre-Detector = Bitmask 3 Done
//Player Ship = Bitmask 4 Done
//Circle Circuit = Bitmask 5 Done
//Square Circuit = Bitmask 5 Done
//Thruster Pickup = Bitmask 6 Done
//Health Pickup = Bitmask 7 Done
//Weapon/Shield Pickup = Bitmask 8 Done

bool SecondWorld::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//LISTENERS FUNCTION
	listeners();

	//TRACK FUNCTION
	track();

	//AI WAYPOINTS FOR AI TO FOLLOW
	AIWayPoints();

	//FINISH LINE FUNCTION
	finish_line();

	//PLAYER SHIP FUNCTION
	//this->player_ship();
	vehicleObjects();

	//THRUSTER PICKUP FUNCTION
	thruster_pickup();

	//HEALTH PICKUP FUNCTION
	health_pickup();

	//WEAPON/SHIELD PICKUP FUNCTION
	weapon_shield_pickup();

	//CIRCLE CIRCUIT FUNCTION
	circle_circuit();

	//SQUARE CIRCUIT FUNCTION
	square_circuit();

	//TURRET BODY FUNCTION
	turret_body();

	//TURRET HEAD FUNCTION
	turret_head();

	//TURRET FIRE FUNCTION
	turret_fire();

	//HUD LAYER FUNCTION
	hud_layer();

	//SCHEDULE UPDATE FUNCTION
	scheduleUpdate();

	return true;
};

//EVENT LISTENERS SAMANTHA & SAMUEL
void SecondWorld::listeners()
{
	//ACTION LISTENERS FOR TOUCH SCREEN
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(SecondWorld::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	//OBJECTS COLLISION DETECTION AND ACTION
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(SecondWorld::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	//EVENT LISTENER FOR DRIVING VEHICLE
	eventListener = EventListenerKeyboard::create();
	eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		//IF A KEY ALREADY EXISTS, DO NOTHING AS IT ALREADY WILL HAVE A TIMESTAMP. OTHERWISE, SET THE TIMESTAMP TO NOW
		if (keys.find(keyCode) == keys.end())
		{
			keys[keyCode] = std::chrono::high_resolution_clock::now();
		}

		switch (keyCode) 
		{
			case EventKeyboard::KeyCode::KEY_SPACE:
			{

				CCLOG("Weapon Fired");
				//cocos2d::Sprite* sprite = playerVehicleObject->fireWeapon();
				//if (sprite != NULL)
				//{
					//this->addChild(sprite);
				//}
				//else
				//{
					//CCLOG("Weapon NULL");
					//break;
				//}
			}
		}
	};
	eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		//REMOVE KEY
		keys.erase(keyCode);
		playerVehicleObject->setSlowDownStatus(true);
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
};

void SecondWorld::menuCloseCallback(Ref* pSender)
{
	//MENU - SAMUEL
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
};

bool SecondWorld::onTouchBegan(Touch* touch, Event* event)
{
	//TRIGONOMETRY CALCULATIONS - ROTATION - VELOCITY
	playerRotationAngle = atan2(touch->getLocation().y - visibleSize.height / 2, touch->getLocation().x - visibleSize.width / 2)  * (180.0 / 3.14);
	setRotationAction = cocos2d::RotateTo::create(0.7, -(playerRotationAngle));
	playerVehicleObject->getSprite()->runAction(setRotationAction);
	float x = 0;
	float y = 0;
	if (playerVehicleObject->getPosition().x < 0)
	{
		x = playerVehicleObject->getPosition().x + (touch->getLocation().x - visibleSize.width / 2);
	}
	else if (playerVehicleObject->getPosition().x > 0)
	{
		x = playerVehicleObject->getPosition().x + (touch->getLocation().x - visibleSize.width / 2);
	}

	if (playerVehicleObject->getPosition().y < 0)
	{
		y = playerVehicleObject->getPosition().y + (touch->getLocation().y - visibleSize.height / 2);
	}
	else if (playerVehicleObject->getPosition().y > 0)
	{
		y = playerVehicleObject->getPosition().y + (touch->getLocation().y - visibleSize.height / 2);
	}

	auto sprite = Sprite::create("TrackOne/WayPoint.png");
	sprite->setPosition(cocos2d::Vec2(x, y));
	this->addChild(sprite);
	CCLOG("X %f Y %f", x*TIscale, y*TIscale);

	return true;
};

void SecondWorld::onTouchEnded(Touch* touch, Event* event)
{
	CCLOG("Touch Ended");
};

void SecondWorld::onTouchMoved(Touch* touch, Event* event)
{};

void SecondWorld::onTouchCancelled(Touch* touch, Event* event)
{};

bool SecondWorld::onContactBegin(cocos2d::PhysicsContact& contact)
{
	contact_a = contact.getShapeA()->getBody();
	contact_b = contact.getShapeB()->getBody();

	//PLAYER SHIP COMES IN CONTACT WITH WALL - SAMANTHA
	if ((contact_a->getCollisionBitmask() == 1) && (contact_b->getCollisionBitmask() == 4) || (contact_a->getCollisionBitmask() == 4) && (contact_b->getCollisionBitmask() == 1))
	{
		CCLOG("There Is Contact Between The Wall And Player Ship");

		return true;
	}

	//PLAYER SHIP COMES IN CONTACT WITH FINISH LINE PRE-DETECTOR - SAMANTHA
	if ((contact_a->getCollisionBitmask() == 3) && (contact_b->getCollisionBitmask() == 4) || (contact_a->getCollisionBitmask() == 4) && (contact_b->getCollisionBitmask() == 3))
	{
		lap_detector = true;

		return true;
	}

	//PLAYER SHIP COMES IN CONTACT WITH FINISH LINE - SAMANTHA
	if ((contact_a->getCollisionBitmask() == 2) && (contact_b->getCollisionBitmask() == 4) && (lap_detector == true) || (contact_a->getCollisionBitmask() == 4) && (contact_b->getCollisionBitmask() == 2) && (lap_detector == true))
	{
		CCLOG("There Is Contact Between The Finish Line And Player Ship");

		lap_counter++;

		lap_detector = false;

		return true;
	}

	//PLAYER SHIP COMES IN CONTACT WITH OBSTACLES - SAMANTHA
	if ((contact_a->getCollisionBitmask() == 4) && (contact_b->getCollisionBitmask() == 5) || (contact_a->getCollisionBitmask() == 5) && (contact_b->getCollisionBitmask() == 4))
	{
		CCLOG("There Is Contact Between The Obstacle And Player Ship");

		return true;
	};

	//PLAYER SHIP COMES IN CONTACT WITH THRUSTER PICKUP - SAMANTHA
	if ((contact_a->getCollisionBitmask() == 4) && (contact_b->getCollisionBitmask() == 6))
	{
		CCLOG("There Is Contact Between The Thruster Pickup And The Player Ship");

		player_ship_thruster_fuel = player_ship_thruster_fuel + 20;

		contact_b->getNode()->removeFromParent();

		return true;
	}

	if ((contact_a->getCollisionBitmask() == 6) && (contact_b->getCollisionBitmask() == 4))
	{
		CCLOG("There Is Contact Between The Thruster Pickup And The Player Ship");

		player_ship_thruster_fuel = player_ship_thruster_fuel + 20;

		contact_a->getNode()->removeFromParent();

		return true;
	}

	//PLAYER SHIP COMES IN CONTACT WITH HEALTH PICKUP - SAMANTHA
	if ((contact_a->getCollisionBitmask() == 4) && (contact_b->getCollisionBitmask() == 7))
	{
		CCLOG("There Is Contact Between The Health Pickup And The Player Ship");

		player_ship_health = player_ship_health + 20;

		contact_b->getNode()->removeFromParent();

		return true;
	}

	if ((contact_a->getCollisionBitmask() == 7) && (contact_b->getCollisionBitmask() == 4))
	{
		CCLOG("There Is Contact Between The Health Pickup And The Player Ship");

		player_ship_health = player_ship_health + 20;

		contact_a->getNode()->removeFromParent();

		return true;
	}

	//PLAYER SHIP COMES IN CONTACT WITH WEAPON-SHIELD PICKUP - SAMANTHA
	for (it = weaponPickups.begin(); it != weaponPickups.end(); it++)
	{
		if ((contact_a->getCollisionBitmask() == 4) && (contact_b->getCollisionBitmask() == 8) && (*it)->getID() == 1)
		{
			for (it = weaponPickups.begin(); it != weaponPickups.end(); it++)
			{
				playerVehicleObject->setMachineGunStatus(true);
				playerVehicleObject->setRocketStatus(false);
				playerVehicleObject->setMineStatus(false);
				playerVehicleObject->setShieldStatus(false);

				CCLOG("Gun Is Activated");

				contact_b->getNode()->removeFromParent();

				return true;
			}
		}

		else if ((contact_a->getCollisionBitmask() == 4) && (contact_b->getCollisionBitmask() == 8) && (*it)->getID() == 2)
		{
			for (it = weaponPickups.begin(); it != weaponPickups.end(); it++)
			{
				playerVehicleObject->setMachineGunStatus(false);
				playerVehicleObject->setRocketStatus(true);
				playerVehicleObject->setMineStatus(false);
				playerVehicleObject->setShieldStatus(false);

				CCLOG("Rocket Is Activated");

				contact_b->getNode()->removeFromParent();

				return true;

			}
		}

		else if ((contact_a->getCollisionBitmask() == 4) && (contact_b->getCollisionBitmask() == 8) && (*it)->getID() == 3)
		{
			for (it = weaponPickups.begin(); it != weaponPickups.end(); it++)
			{
				playerVehicleObject->setMachineGunStatus(false);
				playerVehicleObject->setRocketStatus(false);
				playerVehicleObject->setMineStatus(true);
				playerVehicleObject->setShieldStatus(false);

				CCLOG("LandMine Is Activated");

				contact_b->getNode()->removeFromParent();

				return true;

			}
		}

		else if ((contact_a->getCollisionBitmask() == 4) && (contact_b->getCollisionBitmask() == 8) && (*it)->getID() == 4)
		{
			for (it = weaponPickups.begin(); it != weaponPickups.end(); it++)
			{
				playerVehicleObject->setMachineGunStatus(false);
				playerVehicleObject->setRocketStatus(false);
				playerVehicleObject->setMineStatus(false);
				playerVehicleObject->setShieldStatus(true);

				CCLOG("Shield Is Activated");

				contact_b->getNode()->removeFromParent();

				return true;
			}
		}
	}

	for (it = weaponPickups.begin(); it != weaponPickups.end(); it++)
	{
		if ((contact_a->getCollisionBitmask() == 8) && (contact_b->getCollisionBitmask() == 4) && (*it)->getID() == 1)
		{
			for (it = weaponPickups.begin(); it != weaponPickups.end(); it++)
			{
				playerVehicleObject->setMachineGunStatus(true);
				playerVehicleObject->setRocketStatus(false);
				playerVehicleObject->setMineStatus(false);
				playerVehicleObject->setShieldStatus(false);

				CCLOG("Gun Is Activated");

				contact_a->getNode()->removeFromParent();

				return true;
			}
		}

		else if ((contact_a->getCollisionBitmask() == 8) && (contact_b->getCollisionBitmask() == 4) && (*it)->getID() == 2)
		{
			for (it = weaponPickups.begin(); it != weaponPickups.end(); it++)
			{
				playerVehicleObject->setMachineGunStatus(false);
				playerVehicleObject->setRocketStatus(true);
				playerVehicleObject->setMineStatus(false);
				playerVehicleObject->setShieldStatus(false);

				CCLOG("Rocket Is Activated");

				contact_a->getNode()->removeFromParent();

				return true;
			}
		}

		else if ((contact_a->getCollisionBitmask() == 8) && (contact_b->getCollisionBitmask() == 4) && (*it)->getID() == 3)
		{
			for (it = weaponPickups.begin(); it != weaponPickups.end(); it++)
			{
				playerVehicleObject->setMachineGunStatus(false);
				playerVehicleObject->setRocketStatus(false);
				playerVehicleObject->setMineStatus(true);
				playerVehicleObject->setShieldStatus(false);

				CCLOG("LandMine Is Activated");

				contact_a->getNode()->removeFromParent();

				return true;
			}
		}

		else if ((contact_a->getCollisionBitmask() == 8) && (contact_b->getCollisionBitmask() == 4) && (*it)->getID() == 4)
		{
			for (it = weaponPickups.begin(); it != weaponPickups.end(); it++)
			{
				playerVehicleObject->setMachineGunStatus(false);
				playerVehicleObject->setRocketStatus(false);
				playerVehicleObject->setMineStatus(false);
				playerVehicleObject->setShieldStatus(true);

				CCLOG("Shield Is Activated");

				contact_a->getNode()->removeFromParent();

				return true;
			}
		}
	}
};

bool SecondWorld::isKeyPressed(EventKeyboard::KeyCode code)
{
	if (keys.find(code) != keys.end())
	{
		return true;
	}

	return false;
};

double SecondWorld::keyPressedDuration(EventKeyboard::KeyCode code)
{
	if (!isKeyPressed(EventKeyboard::KeyCode::KEY_CTRL))
	{
		return 0;
	}

	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - keys[code]).count();
};

void SecondWorld::update(float delta)
{
	//UPDATES THE HUD LAYER POSITION - SAMANTHA
	HUD->setPosition(playerVehicleObject->getSprite()->getPosition().x - visibleSize.width / 2, playerVehicleObject->getSprite()->getPosition().y - visibleSize.height / 2);

	//UPDATES THE LAP NUMBER - SAMANTHA
	lap_number->setString("LAP NUMBER: " + std::to_string(lap_counter) + "/10");

	//TIMER - SAMUEL
	time += delta;
	__String *timeToDisplay = __String::createWithFormat("%.2f", time);
	timer->setString(timeToDisplay->getCString());


	//----------------------------------------------------------------
	//PLAYER VEHICLE CALCULATION - DANIEL
	//HLDING DOWN ARROW KEYS FOR CONTROLS
	//Node::update(delta);
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW))
	{
		playerVehicleObject->turnLeft();
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW))
	{
		playerVehicleObject->turnRight();
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW))
	{
		playerVehicleObject->accelerate();
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW))
	{
		playerVehicleObject->brake();
	}
	if (playerVehicleObject->getActiveStatus() && playerVehicleObject->getSpeed() > 0)
	{
		playerVehicleObject->setVelocityPoint();
		playerVehicleObject->setVelocity();
	}
	if (playerVehicleObject->getSlowDownStatus() && playerVehicleObject->getSpeed() > 0)
	{
		playerVehicleObject->VelocityDamping();
	}
	//angle->setString(std::to_string(playerVehicleObject->getAngle()));
	//PLAYER VEHICLE CALCULATION - DANIEL
	//----------------------------------------------------------------


	//THRUSTER FUEL PERCENTAGE - SAMANTHA
	if (player_ship_thruster_fuel == 100)
	{
		this->thruster_bar_timer->setPercentage(100);
	}
	if (player_ship_thruster_fuel == 90)
	{
		this->thruster_bar_timer->setPercentage(90);
	}
	if (player_ship_thruster_fuel == 80)
	{
		this->thruster_bar_timer->setPercentage(80);
	}
	if (player_ship_thruster_fuel == 70)
	{
		this->thruster_bar_timer->setPercentage(70);
	}
	if (player_ship_thruster_fuel == 60)
	{
		this->thruster_bar_timer->setPercentage(60);
	}
	if (player_ship_thruster_fuel == 50)
	{
		this->thruster_bar_timer->setPercentage(50);
	}
	if (player_ship_thruster_fuel == 40)
	{
		this->thruster_bar_timer->setPercentage(40);
	}
	if (player_ship_thruster_fuel == 30)
	{
		this->thruster_bar_timer->setPercentage(30);
	}
	if (player_ship_thruster_fuel == 20)
	{
		this->thruster_bar_timer->setPercentage(20);
	}
	if (player_ship_thruster_fuel == 10)
	{
		this->thruster_bar_timer->setPercentage(10);
	}
	if (player_ship_thruster_fuel == 0)
	{
		this->thruster_bar_timer->setPercentage(0);
	}
	if (player_ship_thruster_fuel > 100)
	{
		player_ship_thruster_fuel = 100;
		this->thruster_bar_timer->setPercentage(100);
	}

	//HEALTH PERCENTAGE - SAMANTHA
	if (player_ship_health == 100)
	{
		this->health_bar_timer->setPercentage(100);
	}
	if (player_ship_health == 90)
	{
		this->health_bar_timer->setPercentage(90);
	}
	if (player_ship_health == 80)
	{
		this->health_bar_timer->setPercentage(80);
	}
	if (player_ship_health == 70)
	{
		this->health_bar_timer->setPercentage(70);
	}
	if (player_ship_health == 60)
	{
		this->health_bar_timer->setPercentage(60);
	}
	if (player_ship_health == 50)
	{
		this->health_bar_timer->setPercentage(50);
	}
	if (player_ship_health == 40)
	{
		this->health_bar_timer->setPercentage(40);
	}
	if (player_ship_health == 30)
	{
		this->health_bar_timer->setPercentage(30);
	}
	if (player_ship_health == 20)
	{
		this->health_bar_timer->setPercentage(20);
	}
	if (player_ship_health == 10)
	{
		this->health_bar_timer->setPercentage(10);
	}
	if (player_ship_health == 0)
	{
		this->health_bar_timer->setPercentage(0);
	}
	if (player_ship_health > 100)
	{
		player_ship_health = 100;
		this->health_bar_timer->setPercentage(100);
	}

	//SPEED INDICATOR - SAMANTHA
	if (player_ship_speed == 100)
	{
		this->speed_indicator_timer->setPercentage(100);
	}

	if (player_ship_speed == 50)
	{
		this->speed_indicator_timer->setPercentage(82);
	}
	if (player_ship_speed == 40)
	{
		this->speed_indicator_timer->setPercentage(66);
	}
	if (player_ship_speed == 30)
	{
		this->speed_indicator_timer->setPercentage(49);
	}
	if (player_ship_speed == 20)
	{
		this->speed_indicator_timer->setPercentage(33);
	}
	if (player_ship_speed == 10)
	{
		this->speed_indicator_timer->setPercentage(17);
	}
	if (player_ship_speed == 0)
	{
		this->speed_indicator_timer->setPercentage(0);
	}
	if (player_ship_speed > 100)
	{
		player_ship_speed = 100;
		this->speed_indicator_timer->setPercentage(100);
	}

	//END RACE - SAMANTHA
	this->end_race();

	//ENEMY ONE VEHICLE CALCULATION - SAMUEL
	enemyOneVehicleObject->autoControlAI(enemyOneCurrentWayPoint);

	if (enemyOneVehicleObject->getActiveStatus())
	{
		enemyOneVehicleObject->setVelocityPoint();
		enemyOneVehicleObject->setVelocity();
	}

	//CHECK IF ENEMY ONE IS COLLIDING WITH CURRENT WAY POINT - SAMUEL
	if (enemyOneVehicleObject->wayPointCollision(wayPointSprite))
	{
		WayPoint[wayPointCounter] = false;

		//CHECK IF AI IS AT THE END OF WAYPOINTS IF TRUE RESET TO ONE TO LOOP LAPS
		if (wayPointCounter == 37)
		{
			wayPointCounter = 0;
			WayPoint[wayPointCounter] = true;
		}

		else
		{
			wayPointCounter++;
			WayPoint[wayPointCounter] = true;
		}

		enemyOneCurrentWayPoint = WayPoints[wayPointCounter][enemyOneWayPointSkill];
		wayPointSprite->setPosition(enemyOneCurrentWayPoint);
	}
};

std::map<cocos2d::EventKeyboard::KeyCode, std::chrono::high_resolution_clock::time_point> SecondWorld::keys;

void SecondWorld::track()
{
	//TRACK BACKGROUD - SAMANTHA
	track_background = Sprite::create("TrackTwo/tracktwobackground.png");
	this->addChild(track_background, 0);

	//TRACK INNER RIM - SAMANTHA
	track_in_sprite = Sprite::create("TrackTwo/tracktwoinnerrim.png");

	track_in_array[0] = Point(-3500 / TIscale, 800 / TIscale);
	track_in_array[1] = Point(-2900 / TIscale, 800 / TIscale);
	track_in_array[2] = Point(-2800 / TIscale, 700 / TIscale);
	track_in_array[3] = Point(-2800 / TIscale, -400 / TIscale);
	track_in_array[4] = Point(-2700 / TIscale, -500 / TIscale);
	track_in_array[5] = Point(-1100 / TIscale, -500 / TIscale);
	track_in_array[6] = Point(-1000 / TIscale, -400 / TIscale);
	track_in_array[7] = Point(-1000 / TIscale, 0 / TIscale);
	track_in_array[8] = Point(-900 / TIscale, 100 / TIscale);
	track_in_array[9] = Point(-700 / TIscale, 100 / TIscale);
	track_in_array[10] = Point(-300 / TIscale, -300 / TIscale);
	track_in_array[11] = Point(3100 / TIscale, -300 / TIscale);
	track_in_array[12] = Point(3500 / TIscale, 100 / TIscale);
	track_in_array[13] = Point(3500 / TIscale, 900 / TIscale);
	track_in_array[14] = Point(3600 / TIscale, 1000 / TIscale);
	track_in_array[15] = Point(3700 / TIscale, 900 / TIscale);
	track_in_array[16] = Point(3700 / TIscale, -1000 / TIscale);
	track_in_array[17] = Point(3600 / TIscale, -1100 / TIscale);
	track_in_array[18] = Point(1200 / TIscale, -1100 / TIscale);
	track_in_array[19] = Point(1000 / TIscale, -900 / TIscale);
	track_in_array[20] = Point(-100 / TIscale, -900 / TIscale);
	track_in_array[21] = Point(-300 / TIscale, -700 / TIscale);
	track_in_array[22] = Point(-3000 / TIscale, -700 / TIscale);
	track_in_array[23] = Point(-3300 / TIscale, -1000 / TIscale);
	track_in_array[24] = Point(-3500 / TIscale, -1000 / TIscale);
	track_in_array[25] = Point(-3500 / TIscale, -600 / TIscale);
	track_in_array[26] = Point(-3200 / TIscale, -300 / TIscale);
	track_in_array[27] = Point(-3200 / TIscale, 500 / TIscale);
	track_in_array[28] = Point(-3500 / TIscale, 800 / TIscale);

	track_in_physics = PhysicsBody::createEdgePolygon(track_in_array, 28, PhysicsMaterial(0, 0, 0), 30);

	track_in_physics->setCollisionBitmask(1);
	track_in_physics->setContactTestBitmask(true);

	track_in_sprite->setPhysicsBody(track_in_physics);

	this->addChild(track_in_sprite, 1);

	//TRACK ISLAND - SAMANTHA
	track_island_sprite = Sprite::create("TrackTwo/tracktwoisland.png");

	track_island_array[0] = Point(-3500 / TIscale, 500 / TIscale);
	track_island_array[1] = Point(-3500 / TIscale, -300 / TIscale);
	track_island_array[2] = Point(-3600 / TIscale, -300 / TIscale);
	track_island_array[3] = Point(-3600 / TIscale, 400 / TIscale);
	track_island_array[4] = Point(-3500 / TIscale, 500 / TIscale);

	track_island_physics = PhysicsBody::createEdgePolygon(track_island_array, 4, PhysicsMaterial(0, 0, 0), 30);

	track_island_physics->setCollisionBitmask(1);
	track_island_physics->setContactTestBitmask(true);

	track_island_sprite->setPhysicsBody(track_island_physics);

	this->addChild(track_island_sprite, 1);

	//TRACK OUTER RIM - SAMANTHA
	track_out_sprite = Sprite::create("TrackTwo/tracktwoouterrim.png");

	track_out_array[0] = Point(-4000 / TIscale, 1400 / TIscale);
	track_out_array[1] = Point(-3500 / TIscale, 1400 / TIscale);
	track_out_array[2] = Point(-3400 / TIscale, 1500 / TIscale);
	track_out_array[3] = Point(-2900 / TIscale, 1500 / TIscale);
	track_out_array[4] = Point(-2800 / TIscale, 1400 / TIscale);
	track_out_array[5] = Point(-2500 / TIscale, 1400 / TIscale);
	track_out_array[6] = Point(-2300 / TIscale, 1200 / TIscale);
	track_out_array[7] = Point(-2300 / TIscale, 200 / TIscale);
	track_out_array[8] = Point(-2100 / TIscale, 0 / TIscale);
	track_out_array[9] = Point(-1600 / TIscale, 0 / TIscale);
	track_out_array[10] = Point(-1400 / TIscale, 200 / TIscale);
	track_out_array[11] = Point(-1400 / TIscale, 700 / TIscale);
	track_out_array[12] = Point(-1300 / TIscale, 800 / TIscale);
	track_out_array[13] = Point(-600 / TIscale, 800 / TIscale);
	track_out_array[14] = Point(-100 / TIscale, 300 / TIscale);
	track_out_array[15] = Point(1200 / TIscale, 300 / TIscale);
	track_out_array[16] = Point(1300 / TIscale, 400 / TIscale);
	track_out_array[17] = Point(2000 / TIscale, 400 / TIscale);
	track_out_array[18] = Point(2100 / TIscale, 300 / TIscale);
	track_out_array[19] = Point(2700 / TIscale, 300 / TIscale);
	track_out_array[20] = Point(2900 / TIscale, 500 / TIscale);
	track_out_array[21] = Point(2900 / TIscale, 1500 / TIscale);
	track_out_array[22] = Point(3100 / TIscale, 1700 / TIscale);
	track_out_array[23] = Point(4200 / TIscale, 1700 / TIscale);
	track_out_array[24] = Point(4400 / TIscale, 1500 / TIscale);
	track_out_array[25] = Point(4400 / TIscale, -1800 / TIscale);
	track_out_array[26] = Point(2700 / TIscale, -1800 / TIscale);
	track_out_array[27] = Point(2600 / TIscale, -1900 / TIscale);
	track_out_array[28] = Point(1900 / TIscale, -1900 / TIscale);
	track_out_array[29] = Point(1800 / TIscale, -1800 / TIscale);
	track_out_array[30] = Point(800 / TIscale, -1800 / TIscale);
	track_out_array[31] = Point(500 / TIscale, -1600 / TIscale);
	track_out_array[32] = Point(-600 / TIscale, -1600 / TIscale);
	track_out_array[33] = Point(-1000 / TIscale, -1200 / TIscale);
	track_out_array[34] = Point(-2500 / TIscale, -1200 / TIscale);
	track_out_array[35] = Point(-3100 / TIscale, -1800 / TIscale);
	track_out_array[36] = Point(-4100 / TIscale, -1800 / TIscale);
	track_out_array[37] = Point(-4100 / TIscale, 1300 / TIscale);
	track_out_array[38] = Point(-4000 / TIscale, 1400 / TIscale);

	track_out_physics = PhysicsBody::createEdgePolygon(track_out_array, 38, PhysicsMaterial(0, 0, 0), 30);

	track_out_physics->setCollisionBitmask(1);
	track_out_physics->setContactTestBitmask(true);

	track_out_sprite->setPhysicsBody(track_out_physics);

	this->addChild(track_out_sprite, 1);
};

//SAMUEL
void SecondWorld::AIWayPoints()
{
	//WE HAVE THIS EXTRA ARRAY HANDY FOR DIFFERENT USES - WE INITIALIZE THEM ALL FALSE
	for (int i = 0; i < 62; i++)
	{ 
		WayPoint[i] = false;
	}
	
	WayPoint[0] = true;//WE START AT FIRST WAY POINT - WHICH WILL HAVE 3 LANES 

	WayPoints[0][0] = cocos2d::Vec2(-3700 / TIscale, -300 / TIscale);
	WayPoints[0][1] = cocos2d::Vec2(-3800 / TIscale, -300 / TIscale);//WAY POINT 1
	WayPoints[0][2] = cocos2d::Vec2(-3900 / TIscale, -300 / TIscale);

	WayPoints[1][0] = cocos2d::Vec2(-3700 / TIscale, 500 / TIscale);
	WayPoints[1][1] = cocos2d::Vec2(-3800 / TIscale, 500 / TIscale);//WAY POINT 2
	WayPoints[1][2] = cocos2d::Vec2(-3900 / TIscale, 500 / TIscale);

	WayPoints[2][0] = cocos2d::Vec2(-3700 / TIscale, 900 / TIscale);
	WayPoints[2][1] = cocos2d::Vec2(-3800 / TIscale, 1000 / TIscale);//WAY POINT 3
	WayPoints[2][2] = cocos2d::Vec2(-3900 / TIscale, 1100 / TIscale);

	WayPoints[3][0] = cocos2d::Vec2(-3000 / TIscale, 900 / TIscale);
	WayPoints[3][1] = cocos2d::Vec2(-3000 / TIscale, 1000 / TIscale);//WAY POINT 4
	WayPoints[3][2] = cocos2d::Vec2(-3000 / TIscale, 1100 / TIscale);

	WayPoints[4][0] = cocos2d::Vec2(-2700 / TIscale, 900 / TIscale);
	WayPoints[4][1] = cocos2d::Vec2(-2600 / TIscale, 1000 / TIscale);//WAY POINT 5
	WayPoints[4][2] = cocos2d::Vec2(-2500 / TIscale, 1100 / TIscale);

	WayPoints[5][0] = cocos2d::Vec2(-2700 / TIscale, 0 / TIscale);
	WayPoints[5][1] = cocos2d::Vec2(-2600 / TIscale, 0 / TIscale);//WAY POINT 6
	WayPoints[5][2] = cocos2d::Vec2(-2500 / TIscale, 0 / TIscale);

	WayPoints[6][0] = cocos2d::Vec2(-2700 / TIscale, -300 / TIscale);
	WayPoints[6][1] = cocos2d::Vec2(-2600 / TIscale, -200 / TIscale);//WAY POINT 7
	WayPoints[6][2] = cocos2d::Vec2(-2500 / TIscale, -100 / TIscale);

	WayPoints[7][0] = cocos2d::Vec2(-1100 / TIscale, -300 / TIscale);
	WayPoints[7][1] = cocos2d::Vec2(-1200 / TIscale, -200 / TIscale);//WAY POINT 8
	WayPoints[7][2] = cocos2d::Vec2(-1300 / TIscale, -100 / TIscale);

	WayPoints[8][0] = cocos2d::Vec2(-1100 / TIscale, 200 / TIscale);
	WayPoints[8][1] = cocos2d::Vec2(-1200 / TIscale, 300 / TIscale);//WAY POINT 9
	WayPoints[8][2] = cocos2d::Vec2(-1300 / TIscale, 400 / TIscale);

	WayPoints[9][0] = cocos2d::Vec2(-600 / TIscale, 200 / TIscale);
	WayPoints[9][1] = cocos2d::Vec2(-500 / TIscale, 300 / TIscale);//WAY POINT 10
	WayPoints[9][2] = cocos2d::Vec2(-400 / TIscale, 400 / TIscale);

	WayPoints[10][0] = cocos2d::Vec2(-200 / TIscale, -200 / TIscale);
	WayPoints[10][1] = cocos2d::Vec2(-100 / TIscale, -100 / TIscale);//WAY POINT 11
	WayPoints[10][2] = cocos2d::Vec2(0 / TIscale, 0 / TIscale);

	WayPoints[11][0] = cocos2d::Vec2(1000 / TIscale, -200 / TIscale);
	WayPoints[11][1] = cocos2d::Vec2(1000 / TIscale, -100 / TIscale);//WAY POINT 12
	WayPoints[11][2] = cocos2d::Vec2(1000 / TIscale, 0 / TIscale);

	WayPoints[12][0] = cocos2d::Vec2(2000 / TIscale, -200 / TIscale);
	WayPoints[12][1] = cocos2d::Vec2(2000 / TIscale, -100 / TIscale);//WAY POINT 13
	WayPoints[12][2] = cocos2d::Vec2(2000 / TIscale, 0 / TIscale);

	WayPoints[13][0] = cocos2d::Vec2(3000 / TIscale, -200 / TIscale);
	WayPoints[13][1] = cocos2d::Vec2(2900 / TIscale, -100 / TIscale);//WAY POINT 14
	WayPoints[13][2] = cocos2d::Vec2(2800 / TIscale, 0 / TIscale);

	WayPoints[14][0] = cocos2d::Vec2(3400 / TIscale, 200 / TIscale);
	WayPoints[14][1] = cocos2d::Vec2(3300 / TIscale, 300 / TIscale);//WAY POINT 15
	WayPoints[14][2] = cocos2d::Vec2(3200 / TIscale, 400 / TIscale);

	WayPoints[15][0] = cocos2d::Vec2(3400 / TIscale, 1000 / TIscale);
	WayPoints[15][1] = cocos2d::Vec2(3300 / TIscale, 1100 / TIscale);//WAY POINT 16
	WayPoints[15][2] = cocos2d::Vec2(3200 / TIscale, 1200 / TIscale);

	WayPoints[16][0] = cocos2d::Vec2(3500 / TIscale, 1100 / TIscale);
	WayPoints[16][1] = cocos2d::Vec2(3400 / TIscale, 1200 / TIscale);//WAY POINT 17
	WayPoints[16][2] = cocos2d::Vec2(3300 / TIscale, 1300 / TIscale);

	WayPoints[17][0] = cocos2d::Vec2(3800 / TIscale, 1100 / TIscale);
	WayPoints[17][1] = cocos2d::Vec2(3900 / TIscale, 1200 / TIscale);//WAY POINT 18
	WayPoints[17][2] = cocos2d::Vec2(4000 / TIscale, 1300 / TIscale);

	WayPoints[18][0] = cocos2d::Vec2(3800 / TIscale, 1000 / TIscale);
	WayPoints[18][1] = cocos2d::Vec2(3900 / TIscale, 1000 / TIscale);//WAY POINT 19
	WayPoints[18][2] = cocos2d::Vec2(4000 / TIscale, 1000 / TIscale);

	WayPoints[19][0] = cocos2d::Vec2(3800 / TIscale, 0 / TIscale);
	WayPoints[19][1] = cocos2d::Vec2(3900 / TIscale, 0 / TIscale);//WAY POINT 20
	WayPoints[19][2] = cocos2d::Vec2(4000 / TIscale, 0 / TIscale);

	WayPoints[20][0] = cocos2d::Vec2(3800 / TIscale, -1000 / TIscale);
	WayPoints[20][1] = cocos2d::Vec2(3900 / TIscale, -1000 / TIscale);//WAY POINT 21
	WayPoints[20][2] = cocos2d::Vec2(4000 / TIscale, -1000 / TIscale);

	WayPoints[21][0] = cocos2d::Vec2(3800 / TIscale, -1100 / TIscale);
	WayPoints[21][1] = cocos2d::Vec2(3900 / TIscale, -1200 / TIscale);//WAY POINT 22
	WayPoints[21][2] = cocos2d::Vec2(4000 / TIscale, -1300 / TIscale);

	WayPoints[22][0] = cocos2d::Vec2(3700 / TIscale, -1200 / TIscale);
	WayPoints[22][1] = cocos2d::Vec2(3800 / TIscale, -1300 / TIscale);//WAY POINT 23
	WayPoints[22][2] = cocos2d::Vec2(3900 / TIscale, -1400 / TIscale);

	WayPoints[23][0] = cocos2d::Vec2(3000 / TIscale, -1200 / TIscale);
	WayPoints[23][1] = cocos2d::Vec2(3000 / TIscale, -1300 / TIscale);//WAY POINT 24
	WayPoints[23][2] = cocos2d::Vec2(3000 / TIscale, -1400 / TIscale);

	WayPoints[24][0] = cocos2d::Vec2(2000 / TIscale, -1200 / TIscale);
	WayPoints[24][1] = cocos2d::Vec2(2000 / TIscale, -1300 / TIscale);//WAY POINT 25
	WayPoints[24][2] = cocos2d::Vec2(2000 / TIscale, -1400 / TIscale);

	WayPoints[25][0] = cocos2d::Vec2(1000 / TIscale, -1200 / TIscale);
	WayPoints[25][1] = cocos2d::Vec2(1000 / TIscale, -1300 / TIscale);//WAY POINT 26
	WayPoints[25][2] = cocos2d::Vec2(1000 / TIscale, -1400 / TIscale);

	WayPoints[26][0] = cocos2d::Vec2(800 / TIscale, -1000 / TIscale);
	WayPoints[26][1] = cocos2d::Vec2(800 / TIscale, -1100 / TIscale);//WAY POINT 27
	WayPoints[26][2] = cocos2d::Vec2(800 / TIscale, -1200 / TIscale);

	WayPoints[27][0] = cocos2d::Vec2(0 / TIscale, -1000 / TIscale);
	WayPoints[27][1] = cocos2d::Vec2(0 / TIscale, -1100 / TIscale);//WAY POINT 28
	WayPoints[27][2] = cocos2d::Vec2(0 / TIscale, -1200 / TIscale);

	WayPoints[28][0] = cocos2d::Vec2(-200 / TIscale, -1000 / TIscale);
	WayPoints[28][1] = cocos2d::Vec2(-300 / TIscale, -1100 / TIscale);//WAY POINT 29
	WayPoints[28][2] = cocos2d::Vec2(-400 / TIscale, -1200 / TIscale);

	WayPoints[29][0] = cocos2d::Vec2(-400 / TIscale, -800 / TIscale);
	WayPoints[29][1] = cocos2d::Vec2(-500 / TIscale, -900 / TIscale);//WAY POINT 30
	WayPoints[29][2] = cocos2d::Vec2(-600 / TIscale, -1000 / TIscale);

	WayPoints[30][0] = cocos2d::Vec2(-1000 / TIscale, -800 / TIscale);
	WayPoints[30][1] = cocos2d::Vec2(-1000 / TIscale, -900 / TIscale);//WAY POINT 31
	WayPoints[30][2] = cocos2d::Vec2(-1000 / TIscale, -1000 / TIscale);

	WayPoints[31][0] = cocos2d::Vec2(-2000 / TIscale, -800 / TIscale);
	WayPoints[31][1] = cocos2d::Vec2(-2000 / TIscale, -900 / TIscale);//WAY POINT 32
	WayPoints[31][2] = cocos2d::Vec2(-2000 / TIscale, -1000 / TIscale);

	WayPoints[32][0] = cocos2d::Vec2(-2900 / TIscale, -800 / TIscale);
	WayPoints[32][1] = cocos2d::Vec2(-2800 / TIscale, -900 / TIscale);//WAY POINT 33
	WayPoints[32][2] = cocos2d::Vec2(-2700 / TIscale, -1000 / TIscale);

	WayPoints[33][0] = cocos2d::Vec2(-3200 / TIscale, -1100 / TIscale);
	WayPoints[33][1] = cocos2d::Vec2(-3100 / TIscale, -1200 / TIscale);//WAY POINT 34
	WayPoints[33][2] = cocos2d::Vec2(-3000 / TIscale, -1300 / TIscale);

	WayPoints[34][0] = cocos2d::Vec2(-3700 / TIscale, -1100 / TIscale);
	WayPoints[34][1] = cocos2d::Vec2(-3800 / TIscale, -1200 / TIscale);//WAY POINT 35
	WayPoints[34][2] = cocos2d::Vec2(-3900 / TIscale, -1300 / TIscale);

	WayPoints[35][0] = cocos2d::Vec2(-3700 / TIscale, -1000 / TIscale);
	WayPoints[35][1] = cocos2d::Vec2(-3800 / TIscale, -1000 / TIscale);//WAY POINT 36
	WayPoints[35][2] = cocos2d::Vec2(-3900 / TIscale, -1000 / TIscale);

	WayPoints[36][0] = cocos2d::Vec2(-3700 / TIscale, -600 / TIscale);
	WayPoints[36][1] = cocos2d::Vec2(-3800 / TIscale, -700 / TIscale);//WAY POINT 37 /*USE HERE AS START FOR TURN IN FOR REFULE*/
	WayPoints[36][2] = cocos2d::Vec2(-3900 / TIscale, -800 / TIscale);

	for (int i = 0; i < 37; i++)
	{
		for (int j = 0; j<3; j++)
		{
			auto sprite = Sprite::create("TrackOne/WayPoint.png");
			sprite->setPosition(WayPoints[i][j]);
			this->addChild(sprite);
		}
	}

	wayPointCounter = 0;
	enemyOneCurrentWayPoint = WayPoints[wayPointCounter][enemyOneWayPointSkill];
	wayPointSprite = Sprite::create("TrackOne/WayPoint.png");
	wayPointSprite->setPosition(enemyOneCurrentWayPoint);
	this->addChild(wayPointSprite, 2);

};

void SecondWorld::finish_line()
{
	//FINISH LINE - SAMANTHA & SAMUEL
	FinishLine* f1 = new FinishLine();
	f1->set_finish_line_position(-4115 / TIscale, -900 / TIscale);
	f1->set_finish_line_detector_position(-4100 / TIscale, -700 / TIscale, -3500 / TIscale, -700 / TIscale);
	f1->set_finish_line_pre_detector_position(-4100 / TIscale, -900 / TIscale, -3500 / TIscale, -900 / TIscale);
	f1->init_finish_line(this);
};

void SecondWorld::vehicleObjects()//VEHICLES OBJECTS FOR OUR FIRST SCENE - DANIEL
{
	//PLAYER VEHICLE OBJECT - DANIEL
	playerVehicleObject = new Vehicle();
	playerVehicleObject->setAngle(-90);
	playerVehicleObject->setPosition(Vec2(-3800 / TIscale, -300 / TIscale));
	playerVehicleObject->setSteeringPower(2);
	this->addChild(playerVehicleObject->getSprite(), 2);

	//AI CAR I VEHICLE OBJECT - DANIEL & SAMUEL
	enemyOneVehicleObject = new Vehicle();
	enemyOneVehicleObject->setAngle(-90);
	enemyOneVehicleObject->setPosition(Vec2(-3700 / TIscale, -300 / TIscale));
	enemyOneVehicleObject->setAutoControl(true);
	enemyOneVehicleObject->setSpeed(220);
	enemyOneVehicleObject->setSteeringPower(2);
	this->addChild(enemyOneVehicleObject->getSprite(), 9);

	this->runAction(cocos2d::Follow::create(playerVehicleObject->getSprite()));
}

//THRUSTER PICKUP FUNCTION - SAMANTHA MARAH
void SecondWorld::thruster_pickup()
{
	//ALL THE THRUSTER PICKUP OBJECTS IN THIS TRACK
	PickUps* t1 = new ThrusterPickup(); //CREATES THRUSTERPICKUP OBJECT AND ASSIGNS IT TO t1
	t1->getSprite()->setPosition(3800 / TIscale, -500 / TIscale); //SETS THE POSITION OF t1
	t1->rotate(); //CALLS THE ROTATE FUNCTION FOR t1
	this->addChild(t1->getSprite(), 2); //ADDS T1 TO THE SCENE

	PickUps* t2 = new ThrusterPickup(); //CREATES THRUSTERPICKUP OBJECT AND ASSIGNS IT TO t2
	t2->getSprite()->setPosition(4300 / TIscale, -500 / TIscale); //SETS THE POSITION OF t2
	t2->rotate(); //CALLS THE ROTATE FUNCTION FOR t2
	this->addChild(t2->getSprite(), 2); //ADDS T2 TO THE SCENE

	PickUps* t3 = new ThrusterPickup(); //CREATES THRUSTERPICKUP OBJECT AND ASSIGNS IT TO t3
	t3->getSprite()->setPosition(-800 / TIscale, 400 / TIscale); //SETS THE POSITION OF t3
	t3->rotate(); //CALLS THE ROTATE FUNCTION FOR t3
	this->addChild(t3->getSprite(), 2); //ADDS T3 TO THE SCENE
};

//HEALTH PICKUP FUNCTION - SAMANTHA MARAH
void SecondWorld::health_pickup()
{
	//ALL HEALTH PICKUP OBJECTS IN THIS TRACK
	PickUps* h1 = new HealthPickup(); //CREATES HEALTHPICKUP OBJECT AND ASSIGNS IT TO h1
	h1->getSprite()->setPosition(4050 / TIscale, -500 / TIscale); //SETS THE POSITION OF h1
	h1->rotate(); //CALLS THE ROTATE FUNCTION FOR h1
	this->addChild(h1->getSprite(), 2); //ADDS h1 TO THE SCENE

	PickUps* h2 = new HealthPickup(); //CREATES HEALTHPICKUP OBJECT AND ASSIGNS IT TO h2
	h2->getSprite()->setPosition(-800 / TIscale, 200 / TIscale); //SETS THE POSITION OF h2
	h2->rotate(); //CALLS THE ROTATE FUNCTION FOR h2
	this->addChild(h2->getSprite(), 2); //ADDS h2 TO THE SCENE

	PickUps* h3 = new HealthPickup(); //CREATES HEALTHPICKUP OBJECT AND ASSIGNS IT TO h3
	h3->getSprite()->setPosition(-800 / TIscale, 600 / TIscale); //SETS THE POSITION OF h3
	h3->rotate(); //CALLS THE ROTATE FUNCTION FOR h3
	this->addChild(h3->getSprite(), 2); //ADDS h3 TO THE SCENE
};

//WEAPON-SHIELD PICKUP FUNCTION - SAMANTHA MARAH
void SecondWorld::weapon_shield_pickup()
{
	//ALL THE WEAPON-SHIELD PICKUP OBJECTS IN THIS TRACK
	PickUps* ws1 = new WeaponShieldPickup(); //CREATES WEAPONSHIELDPICKUP OBJECT AND ASSIGNS IT TO ws1
	ws1->getSprite()->setPosition(2000 / TIscale, -200 / TIscale); //SETS THE POSITION OF ws1
	ws1->rotate(); //CALLS THE ROTATE FUNCTION FOR ws1
	this->addChild(ws1->getSprite(), 2); //ADDS ws1 TO THE SCENE

	PickUps* ws2 = new WeaponShieldPickup(); //CREATES WEAPONSHIELDPICKUP OBJECT AND ASSIGNS IT TO ws2
	ws2->getSprite()->setPosition(2000 / TIscale, 0 / TIscale); //SETS THE POSITION OF ws2
	ws2->rotate(); //CALLS THE ROTATE FUNCTION FOR ws2
	this->addChild(ws2->getSprite(), 2); //ADDS ws2 TO THE SCENE

	PickUps* ws3 = new WeaponShieldPickup(); //CREATES WEAPONSHIELDPICKUP OBJECT AND ASSIGNS IT TO ws3
	ws3->getSprite()->setPosition(2000 / TIscale, 200 / TIscale); //SETS THE POSITION OF ws3
	ws3->rotate(); //CALLS THE ROTATE FUNCTION FOR ws3
	this->addChild(ws3->getSprite(), 2); //ADDS ws3 TO THE SCENE

	PickUps* ws4 = new WeaponShieldPickup(); //CREATES WEAPONSHIELDPICKUP OBJECT AND ASSIGNS IT TO ws4
	ws4->getSprite()->setPosition(1000 / TIscale, -1100 / TIscale); //SETS THE POSITION OF ws4
	ws4->rotate(); //CALLS THE ROTATE FUNCTION FOR ws4
	this->addChild(ws4->getSprite(), 2); //ADDS ws4 TO THE SCENE

	PickUps* ws5 = new WeaponShieldPickup(); //CREATES WEAPONSHIELDPICKUP OBJECT AND ASSIGNS IT TO ws5
	ws5->getSprite()->setPosition(800 / TIscale, -1300 / TIscale); //SETS THE POSITION OF ws5
	ws5->rotate(); //CALLS THE ROTATE FUNCTION FOR ws5
	this->addChild(ws5->getSprite(), 2); //ADDS ws5 TO THE SCENE

	PickUps* ws6 = new WeaponShieldPickup(); //CREATES WEAPONSHIELDPICKUP OBJECT AND ASSIGNS IT TO ws6
	ws6->getSprite()->setPosition(600 / TIscale, -1500 / TIscale); //SETS THE POSITION OF ws6
	ws6->rotate(); //CALLS THE ROTATE FUNCTION FOR ws6
	this->addChild(ws6->getSprite(), 2); //ADDS ws6 TO THE SCENE

	//PUSHING EACH INSTANCE OF THE WEAPONSHIELDPICKUP
	//OBJECT INTO A VECTOR
	weaponPickups.push_back(ws1);
	weaponPickups.push_back(ws2);
	weaponPickups.push_back(ws3);
	weaponPickups.push_back(ws4);
	weaponPickups.push_back(ws5);
	weaponPickups.push_back(ws6);

	//CYCLES THROUGH THE VECTOR AND GIVES EACH WEAPONSHIELDPICKUP OBJECT
	//A RANDOM ID BETWEEN 1-4;
	for (it = weaponPickups.begin(); it != weaponPickups.end(); it++)
	{
		pickupID = cocos2d::RandomHelper::random_int(1, 4);

		(*it)->setID(pickupID);
	}

	for (it = weaponPickups.begin(); it != weaponPickups.end(); it++)
	{
		(*it)->seeID();
	}
};

void SecondWorld::circle_circuit()
{
	//CIRCLE CIRCUIT OBSTACLE - SAMUEL
	CircleCircuit* circle = new CircleCircuit();
	circle->set_CircleCircuit_position(3800 / TIscale, -300 / TIscale);
	circle->init_CircleCircuit(this);

	CircleCircuit* circle1 = new CircleCircuit();
	circle1->set_CircleCircuit_position(-3700 / TIscale, -300 / TIscale);
	circle1->init_CircleCircuit(this);

	CircleCircuit* circle2 = new CircleCircuit();
	circle2->set_CircleCircuit_position(-3900 / TIscale, 1200 / TIscale);
	circle2->init_CircleCircuit(this);

	CircleCircuit* circle3 = new CircleCircuit();
	circle3->set_CircleCircuit_position(-900 / TIscale, 200 / TIscale);
	circle3->init_CircleCircuit(this);
};

void  SecondWorld::square_circuit()
{
	//SQUARE CIRCUIT OBSTACLE - SAMUEL
	SquareCircuit* square = new SquareCircuit();
	square->set_SquareCircuit_position(3800 / TIscale, -400 / TIscale);
	square->init_SquareCircuit(this);

	SquareCircuit* square1 = new SquareCircuit();
	square1->set_SquareCircuit_position(-3800 / TIscale, -350 / TIscale);
	square1->init_SquareCircuit(this);

	SquareCircuit* square2 = new SquareCircuit();
	square2->set_SquareCircuit_position(-3900 / TIscale, 1250 / TIscale);
	square2->init_SquareCircuit(this);

	SquareCircuit* square3 = new SquareCircuit();
	square3->set_SquareCircuit_position(-900 / TIscale, 250 / TIscale);
	square3->init_SquareCircuit(this);
};

void SecondWorld::turret_body()
{
	//TURRET BODY - SAMANTHA
	TurretBody* tb1 = new TurretBody();
	tb1->set_turret_body_position(-3200 / TIscale, 1400 / TIscale);
	tb1->init_turret_body(this);

	TurretBody* tb2 = new TurretBody();
	tb2->set_turret_body_position(1600 / TIscale, 300 / TIscale);
	tb2->init_turret_body(this);

	TurretBody* tb3 = new TurretBody();
	tb3->set_turret_body_position(2200 / TIscale, -1800 / TIscale);
	tb3->init_turret_body(this);
};

void SecondWorld::turret_head()
{
	//TURRET HEAD - SAMUEL
	TurretHead* th1 = new TurretHead();
	th1->getSprite()->setPosition(-3150 / TIscale, 1400 / TIscale);
	th1->setRotateHead1(0.5f, 110.0f);
	th1->setRotateHead2(0.5f, 40.0f);
	this->addChild(th1->getSprite(), 50);
	th1->turretmove();

	TurretHead* th2 = new TurretHead();
	th2->getSprite()->setPosition(1650 / TIscale, 300 / TIscale);
	th2->setRotateHead1(0.5f, 110.0f);
	th2->setRotateHead2(0.5f, 40.0f);
	this->addChild(th2->getSprite(), 50);
	th2->turretmove();

	TurretHead* th3 = new TurretHead();
	th3->getSprite()->setPosition(2250 / TIscale, -1800 / TIscale);
	th3->setRotateHead1(0.5f, -110.0f);
	th3->setRotateHead2(0.5f, -40.0f);
	this->addChild(th3->getSprite(), 50);
	th3->turretmove();

	/*TurretBullet* tb1 = new TurretBullet();
	if (th1->getRotation1() == true)
	{
		tb1->set_turret_bullet_position(-3225 / TIscale, 1200 / TIscale);
	}
	tb1->setmove(0 / TIscale, 0 / TIscale);

	tb1->init_turret_bullet(this);*/

};

void SecondWorld::turret_fire()
{
	/*TurretBullet* tb1 = new TurretBullet();
	if (th1->getRotation1() == true)
	{
		tb1->set_turret_bullet_position(-3225 / TIscale, 1200 / TIscale);
	}
	tb1->setmove(0 / TIscale, 0 / TIscale);

	tb1->init_turret_bullet(this);*/
};

void SecondWorld::hud_layer()
{
	//HUD LAYER - SAMUEL & SAMANTHA
	HUD = LayerGradient::create(Color4B(0, 0, 0, 0), Color4B(0, 0, 0, 0));
	HUD->setContentSize(visibleSize);

	this->addChild(HUD, 4);

	//HUD LAYER TEMPLATE - SAMUEL & SAMANTHA
	hud_layer_template_sprite = Sprite::create("HUD/hudtemplate.png");
	hud_layer_template_sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	hud_layer_template_sprite->setScale(1.27);

	HUD->addChild(hud_layer_template_sprite, 5);

	//LAP NUMBER SAMUEL & SAMANTHA
	lap_number = Label::createWithTTF("LAP NUMBER: ", "fonts/Marker Felt.ttf", 20);
	lap_number->setPosition(Vec2(-300, visibleSize.height + 350));
	lap_number->setAnchorPoint(Vec2(0, 0));
	lap_number->setString("LAP NUMBER: " + std::to_string(lap_counter) + "/10");

	HUD->addChild(lap_number, 6);

	//TIMER - SAMUEL
	timer = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 30);
	timer->setPosition(Vec2(-50, visibleSize.height + 350));
	timer->setAnchorPoint(Vec2(0, 0));

	HUD->addChild(timer, 6);

	//HEALTH BAR - SAMANTHA
	background_bar_sprite1 = Sprite::create("Bars/backgroundbar.png");
	background_bar_sprite1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 305));

	HUD->addChild(background_bar_sprite1, 6);

	this->damage_bar_timer1 = cocos2d::ProgressTimer::create(damage_bar_sprite1 = Sprite::create("Bars/damagebar.png"));
	this->damage_bar_timer1->setGlobalZOrder(1);
	this->damage_bar_timer1->setType(ProgressTimerType::BAR);
	this->damage_bar_timer1->setBarChangeRate(Vec2(1, 0));
	this->damage_bar_timer1->setAnchorPoint(Vec2(0, 0));
	this->damage_bar_timer1->setPosition(Vec2(visibleSize.width / 2 - 145, visibleSize.height - 315));
	this->damage_bar_timer1->setVisible(true);
	this->damage_bar_timer1->setPercentage(100);
	this->damage_bar_timer1->setMidpoint(Vec2(0, 0));
	HUD->addChild(this->damage_bar_timer1, 7);

	this->health_bar_timer = cocos2d::ProgressTimer::create(health_bar_sprite = Sprite::create("Bars/healthbar.png"));
	this->health_bar_timer->setGlobalZOrder(2);
	this->health_bar_timer->setType(ProgressTimerType::BAR);
	this->health_bar_timer->setBarChangeRate(Vec2(1, 0));
	this->health_bar_timer->setAnchorPoint(Vec2(0, 0));
	this->health_bar_timer->setPosition(Vec2(visibleSize.width / 2 - 145, visibleSize.height - 315));
	this->health_bar_timer->setVisible(true);
	this->health_bar_timer->setPercentage(100);
	this->health_bar_timer->setMidpoint(Vec2(0, 0));
	HUD->addChild(this->health_bar_timer, 8);

	//THRUSTER BAR - SAMANTHA
	background_bar_sprite2 = Sprite::create("Bars/backgroundbar.png");
	background_bar_sprite2->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 365));

	HUD->addChild(background_bar_sprite2, 6);

	this->damage_bar_timer2 = cocos2d::ProgressTimer::create(damage_bar_sprite2 = Sprite::create("Bars/damagebar.png"));
	this->damage_bar_timer2->setGlobalZOrder(1);
	this->damage_bar_timer2->setType(ProgressTimerType::BAR);
	this->damage_bar_timer2->setBarChangeRate(Vec2(1, 0));
	this->damage_bar_timer2->setAnchorPoint(Vec2(0, 0));
	this->damage_bar_timer2->setPosition(Vec2(visibleSize.width / 2 - 145, visibleSize.height - 375));
	this->damage_bar_timer2->setVisible(true);
	this->damage_bar_timer2->setPercentage(100);
	this->damage_bar_timer2->setMidpoint(Vec2(0, 0));
	HUD->addChild(this->damage_bar_timer2, 7);

	this->thruster_bar_timer = cocos2d::ProgressTimer::create(thruster_bar_sprite = Sprite::create("Bars/thrusterbar.png"));
	this->thruster_bar_timer->setGlobalZOrder(2);
	this->thruster_bar_timer->setType(ProgressTimerType::BAR);
	this->thruster_bar_timer->setBarChangeRate(Vec2(1, 0));
	this->thruster_bar_timer->setAnchorPoint(Vec2(0, 0));
	this->thruster_bar_timer->setPosition(Vec2(visibleSize.width / 2 - 145, visibleSize.height - 375));
	this->thruster_bar_timer->setVisible(true);
	this->thruster_bar_timer->setPercentage(100);
	this->thruster_bar_timer->setMidpoint(Vec2(0, 0));
	HUD->addChild(this->thruster_bar_timer, 8);

	this->speed_indicator_timer = cocos2d::ProgressTimer::create(speed_indicator = Sprite::create("SpeedIndicator/speedindicator.png"));
	this->speed_indicator_timer->setGlobalZOrder(1);
	this->speed_indicator_timer->setType(ProgressTimerType::BAR);
	this->speed_indicator_timer->setBarChangeRate(Vec2(1, 0));
	this->speed_indicator_timer->setAnchorPoint(Vec2(0, 0));
	this->speed_indicator_timer->setPosition(Vec2(visibleSize.width / 2 + 300, visibleSize.height - 375));
	this->speed_indicator_timer->setVisible(true);
	this->speed_indicator_timer->setPercentage(100);
	this->speed_indicator_timer->setMidpoint(Vec2(0, 0));

	HUD->addChild(speed_indicator_timer, 6);
};

void SecondWorld::end_race()
{
	if (lap_counter >= 11)
	{
		Director::getInstance()->end();
	}
}

//DIRECTOR & SCREEN ORIGIN CENTER POINT
void SecondWorld::director()
{
	//DIRECTOR RESOLUTION - VISIBLSIZE CAN BE USED THROUGH OUT CLASS TO GET SCREEN WIDTH AND HEIGHT - DANIEL
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();//GETS CENTER OF DISPLAY
}