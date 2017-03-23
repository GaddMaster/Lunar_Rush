//SAMANTHA MARAH
//K00200782

//SAMUEL MACSWEENEY
//K00200955

#include "SecondWorld.h"

#include "FinishLine.h"

#include "Triangle.h"
#include "Circle.h"
#include "Square.h"

#include "TurretBody.h"
#include "TurretHead.h"

#include "Bullet.h"
#include "Rocket.h"
#include "LandMine.h"

#include "EndingCredits.h"

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

//LAYERS
//Track Background = Layer 0 Done - SAMANTHA
//Finish Line = Layer 0 Done - SAMANTHA
//Track Walls = Layer 1 Done - SAMANTHA
//Player Vehicle = Layer 2 Done - DANIEL
//Health Pickup = Layer 2 Done - SAMANTHA
//Thruster Pickup = Layer 2 Done - SAMANTHA
//Weapon/Shield Pickup = Layer 2 Done - SAMANTHA
//Circle = Layer2 Done - SAMUEL
//Square = Layer 2 Done SAMUEL
//Triangle = Layer 2 Done - SAMUEL
//Turret Body = Layer 2 Done - SAMUEL
//Turret Head = Layer 3 Done - SAMUEL


//BITMASKS
//Track Walls = Bitmask 1 Done - SAMANTHA
//Finish Line Detector = Bitmask 2 Done - SAMANTHA
//Finish Line Pre-Detector One = Bitmask 3 Done - SAMANTHA
//Finish Line Pre-Detector Two = Bitmask 4 Done - SAMANTHA
//Player Vehicle = Bitmask 5 Done - DANIEL
//Thruster Pickup = Bitmask 6 Done - SAMANTHA
//Health Pickup = Bitmask 7 Done - SAMANTHA
//Weapon/Shield Pickup = Bitmask 8 Done - SAMANTHA
//Circle = Bitmask 9 Done - SAMUEL
//Square = Bitmask 9 Done - SAMUEL 
//Triangle = Bitmask 9 Done - SAMUEL
//Turret Body = Bitmask 10 Done - SAMUEL
//Turret Bullet = Bitmask 11 - SAMUEL


bool SecondWorld::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//LISTENERS FUNCTION
	listeners();

	//TRACK FUNCTION - SAMANTHA
	track();

	//PLAYER SHIP FUNCTION - DANIEL
	vehicleObjects();

	//AI WAYPOINTS FOR AI TO FOLLOW - SAMUEL
	AIWayPoints();

	//FINISH LINE FUNCTION - SAMANTHA
	finishLine();

	//THRUSTER PICKUP FUNCTION - SAMANTHA
	thrusterPickup();

	//HEALTH PICKUP FUNCTION - SAMANTHA
	healthPickup();

	//WEAPON/SHIELD PICKUP FUNCTION - SAMANTHA
	weaponShieldPickup();

	//CIRCLE CIRCUIT FUNCTION - SAMUEL
	circleCircuit();

	//SQUARE CIRCUIT FUNCTION - SAMUEL
	squareCircuit();

	//TURRET BODY FUNCTION - SAMUEL
	turretBody();

	//TURRET HEAD FUNCTION - SAMUEL
	turretHead();

	//TURRET FIRE FUNCTION - SAMUEL
	turretFire();

	//HUD LAYER FUNCTION - SAMANTHA & SAMUEL
	hudLayer();

	//SCHEDULE UPDATE FUNCTION
	scheduleUpdate();

	return true;
};

//LISTENERS - DANIEL GADD
void SecondWorld::listeners()
{
	//ACTION LISTENERS FOR TOUCH SCREEN
	touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(SecondWorld::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);


	//OBJECTS COLLISION DETECTION AND ACTION
	contactListenerBegin = EventListenerPhysicsContact::create();
	contactListenerBegin->onContactBegin = CC_CALLBACK_1(SecondWorld::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListenerBegin, this);

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
		case EventKeyboard::KeyCode::KEY_SPACE://FIRES WEAPON IF AVAILABLE
		{
			//CHECK IF ANY WEAPONS ARE AVAILABLE
			if (playerVehicleObject->availableWeapon())
			{
				//CHECK WHICH WEAPON IS AVAILABLE AND USE
				if (playerVehicleObject->getRocketStatus())
				{
					bool fire = false;
					cocos2d::Sprite* target;

					//GET NEARBY ENEMY VEHICLE FOR TARGETING
					for (auto vehicle : this->vehicles)
					{
						if (vehicle->getType() != "player")
						{
							float distance = std::sqrt(std::pow((vehicle->getSprite()->getPosition().x - playerVehicleObject->getSprite()->getPosition().x), 2) + std::pow((vehicle->getSprite()->getPosition().y - playerVehicleObject->getSprite()->getPosition().y), 2));
							CCLOG("DISTANCE ROCKET : %f", distance);
							if (distance < 300)
							{
								target = vehicle->getSprite();
								fire = true;
								break;
							}
						}
					}


					if (fire)
					{
						GameObject* rocket = playerVehicleObject->fireRocket(target, false);
						this->addChild(rocket->getSprite());//ROCKET CAN BE LOCK ON OR NOT
						projectiles.push_back(rocket);
					}
				}
				else if (playerVehicleObject->getMineStatus())
				{
					GameObject* mine = playerVehicleObject->layMine();
					this->addChild(mine->getSprite());//ROCKET CAN BE LOCK ON OR NOT
					projectiles.push_back(mine);
				}
				else if (playerVehicleObject->getMachineGunStatus())
				{
					GameObject* bullet = playerVehicleObject->fireMachineGun();
					if (bullet != NULL)
					{
						this->addChild(bullet->getSprite());//ROCKET CAN BE LOCK ON OR NOT
						projectiles.push_back(bullet);
					}
				}
				else if (playerVehicleObject->getShieldStatus())
				{
					CCLOG("SHIELD ACTIVATED - WORKING ON THIS");
					weaponTimer = 0;
					activeWeaponTimer = true;
					playerVehicleObject->deployShield();
				}
				else if (playerVehicleObject->getTrusterStatus())
				{
					CCLOG("TRUSTER ACTIVATED");
					weaponTimer = 7;
					playerVehicleObject->truster();
				}
			}
		}
		break;
		case EventKeyboard::KeyCode::KEY_1://TESTING TRUSTER ACTIVATE
		{
			playerVehicleObject->endWeapon();
			playerVehicleObject->setTrusterStatus(true);
		}
		break;
		case EventKeyboard::KeyCode::KEY_2://TESTING ROCKET ACTIVATE
		{
			playerVehicleObject->endWeapon();
			playerVehicleObject->setRocketStatus(true);
		}
		break;
		case EventKeyboard::KeyCode::KEY_3://TESTING MINE ACTIVATE
		{
			playerVehicleObject->endWeapon();
			playerVehicleObject->setMineStatus(true);
		}
		break;
		case EventKeyboard::KeyCode::KEY_4://TESTING SHIELD ACTIVATE
		{
			playerVehicleObject->endWeapon();
			playerVehicleObject->setShieldStatus(true);
		}
		break;
		case EventKeyboard::KeyCode::KEY_5://TESTING MACHINE GUN ACTIVATE
		{
			playerVehicleObject->endWeapon();
			playerVehicleObject->setMachineGunStatus(true);
		}
		break;
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

//MENU CLOSE FUNCTION - SAMUEL MACSWEENEY
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

//ON TOUCH BEGIN FUNCTION - DANIEL GADD
bool SecondWorld::onTouchBegan(Touch* touch, Event* event)
{
	//TRIGONOMETRY CALCULATIONS - ROTATION - VELOCITY - DANILE
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

	//auto sprite = Sprite::create("TrackOne/WayPoint.png");
	//sprite->setPosition(cocos2d::Vec2(x, y));
	//this->addChild(sprite);
	//CCLOG("X %f Y %f", x*TIscale, y*TIscale);

	return true;
};

//ON TOUCH ENDED FUNCTION - DANIEL GADD
void SecondWorld::onTouchEnded(Touch* touch, Event* event)
{
	CCLOG("Touch Ended");
};

//ON TOUCH MOVED FUNCTION - DANIEL GADD
void SecondWorld::onTouchMoved(Touch* touch, Event* event)
{};

//ON TOUCH CANCELLED FUNCTION - DANIEL GADD
void SecondWorld::onTouchCancelled(Touch* touch, Event* event)
{};

//ON CONTACT BEGIN - SAMANTHA MARAH & SAMUEL MACSWEENEY
bool SecondWorld::onContactBegin(cocos2d::PhysicsContact& contact)
{
	contactA = contact.getShapeA()->getBody();
	contactB = contact.getShapeB()->getBody();

	//PLAYER SHIP COMES IN CONTACT WITH WALL - SAMANTHA
	if ((contactA->getCollisionBitmask() == 1) && (contactB->getCollisionBitmask() == 5) || (contactA->getCollisionBitmask() == 5) && (contactB->getCollisionBitmask() == 1))
	{
		CCLOG("There Is Contact Between The Wall And Player Ship");

		return true;
	}

	//PLAYER SHIP COMES IN CONTACT WITH FINISH LINE PRE-DETECTOR2 - SAMANTHA
	if ((contactA->getCollisionBitmask() == 4) && (contactB->getCollisionBitmask() == 5) || (contactA->getCollisionBitmask() == 5) && (contactB->getCollisionBitmask() == 4))
	{
		//SETS BOOL TO TRUE
		lapDetector2 = true;

		return true;
	}

	//PLAYER SHIP COMES IN CONTACT WITH FINISH LINE PRE-DETECTOR1 - SAMANTHA
	if ((contactA->getCollisionBitmask() == 3) && (contactB->getCollisionBitmask() == 5) || (contactA->getCollisionBitmask() == 5) && (contactB->getCollisionBitmask() == 3))
	{
		//SETS BOOL TO TRU
		lapDetector1 = true;

		return true;
	}

	//PLAYER SHIP COMES IN CONTACT WITH FINISH LINE - SAMANTHA
	if ((contactA->getCollisionBitmask() == 2) && (contactB->getCollisionBitmask() == 5) && (lapDetector2 == true) && (lapDetector1 == true) || (contactA->getCollisionBitmask() == 5) && (contactB->getCollisionBitmask() == 2) && (lapDetector2 == true) && (lapDetector1 == true))
	{
		CCLOG("There Is Contact Between The Finish Line And Player Ship");

		//INCREMENTS THE LAP COUNTER
		lapCounter++;

		//SETS BOOL TO FALSE
		lapDetector2 = false;
		lapDetector1 = false;

		return true;
	}

	//PLAYER SHIP COMES IN CONTACT WITH THRUSTER PICKUP - SAMANTHA
	if ((contactA->getCollisionBitmask() == 5) && (contactB->getCollisionBitmask() == 6))
	{
		CCLOG("There Is Contact Between The Thruster Pickup And The Player Ship");

		//INCREMENT THRUSTERFUEL BY 20
		playerThrusterfuel = playerThrusterfuel + 20;

		//REMOVE THE SPRITE FROM SCENE
		contactB->getNode()->removeFromParent();

		return true;
	}

	if ((contactA->getCollisionBitmask() == 6) && (contactB->getCollisionBitmask() == 5))
	{
		CCLOG("There Is Contact Between The Thruster Pickup And The Player Ship");

		//INCREMENT THRUSTERFUEL BY 20
		playerThrusterfuel = playerThrusterfuel + 20;

		//REMOVE THE SPRITE FROM SCENE
		contactA->getNode()->removeFromParent();

		return true;
	}

	//PLAYER SHIP COMES IN CONTACT WITH HEALTH PICKUP - SAMANTHA
	if ((contactA->getCollisionBitmask() == 5) && (contactB->getCollisionBitmask() == 7))
	{
		CCLOG("There Is Contact Between The Health Pickup And The Player Ship");

		//INCREMENT PLAYERHEALTH BY 20
		playerHealth = playerHealth + 20;

		//REMOVE THE SPRITE FROM SCENE
		contactB->getNode()->removeFromParent();

		return true;
	}

	if ((contactA->getCollisionBitmask() == 7) && (contactB->getCollisionBitmask() == 5))
	{
		CCLOG("There Is Contact Between The Health Pickup And The Player Ship");

		//INCREMENT PLAYERHEALTH BY 20
		playerHealth = playerHealth + 20;

		//REMOVE THE SPRITE FROM SCENE
		contactA->getNode()->removeFromParent();

		return true;
	}

	//PLAYER SHIP COMES IN CONTACT WITH WEAPON-SHIELD PICKUP - SAMANTHA
	//ITERATES THROUGH LIST
	for (it = weaponPickups.begin(); it != weaponPickups.end(); it++)
	{
		if ((contactA->getCollisionBitmask() == 5) && (contactB->getCollisionBitmask() == 8) && (*it)->getID() == 1)
		{
			//RE-ITERATES THROUGH THE LIST
			for (it = weaponPickups.begin(); it != weaponPickups.end(); it++)
			{
				//SETS BULLETS BOOL TO TRUE WHILE
				//OTHER WEAPONS ARE SET TO FALS
				playerVehicleObject->setMachineGunStatus(true);
				playerVehicleObject->setRocketStatus(false);
				playerVehicleObject->setMineStatus(false);
				playerVehicleObject->setShieldStatus(false);

				CCLOG("Gun Is Activated");

				//REMOVES SPRITE
				contactB->getNode()->removeFromParent();

				return true;
			}
		}

		else if ((contactA->getCollisionBitmask() == 5) && (contactB->getCollisionBitmask() == 8) && (*it)->getID() == 2)
		{
			for (it = weaponPickups.begin(); it != weaponPickups.end(); it++)
			{
				//SETS ROCKET BOOL TO TRUE WHILE
				//OTHER WEAPONS ARE SET TO FALS
				playerVehicleObject->setMachineGunStatus(false);
				playerVehicleObject->setRocketStatus(true);
				playerVehicleObject->setMineStatus(false);
				playerVehicleObject->setShieldStatus(false);

				CCLOG("Rocket Is Activated");

				//REMOVES SPRITE
				contactB->getNode()->removeFromParent();

				return true;

			}
		}

		else if ((contactA->getCollisionBitmask() == 5) && (contactB->getCollisionBitmask() == 8) && (*it)->getID() == 3)
		{
			for (it = weaponPickups.begin(); it != weaponPickups.end(); it++)
			{
				//SETS MINE BOOL TO TRUE WHILE
				//OTHER WEAPONS ARE SET TO FALS
				playerVehicleObject->setMachineGunStatus(false);
				playerVehicleObject->setRocketStatus(false);
				playerVehicleObject->setMineStatus(true);
				playerVehicleObject->setShieldStatus(false);

				CCLOG("LandMine Is Activated");

				//REMOVE SPRITE FROM SCENE
				contactB->getNode()->removeFromParent();

				return true;

			}
		}

		else if ((contactA->getCollisionBitmask() == 5) && (contactB->getCollisionBitmask() == 8) && (*it)->getID() == 4)
		{
			for (it = weaponPickups.begin(); it != weaponPickups.end(); it++)
			{
				//SETS SHIELD BOOL TO TRUE WHILE
				//OTHER WEAPONS ARE SET TO FALS
				playerVehicleObject->setMachineGunStatus(false);
				playerVehicleObject->setRocketStatus(false);
				playerVehicleObject->setMineStatus(false);
				playerVehicleObject->setShieldStatus(true);

				CCLOG("Shield Is Activated");

				//REMOVES SRITE FROM SCENE
				contactB->getNode()->removeFromParent();

				return true;
			}
		}
	}

	for (it = weaponPickups.begin(); it != weaponPickups.end(); it++)
	{
		if ((contactA->getCollisionBitmask() == 8) && (contactB->getCollisionBitmask() == 5) && (*it)->getID() == 1)
		{
			for (it = weaponPickups.begin(); it != weaponPickups.end(); it++)
			{
				//SETS BULLETS BOOL TO TRUE WHILE
				//OTHER WEAPONS ARE SET TO FALS
				playerVehicleObject->setMachineGunStatus(true);
				playerVehicleObject->setRocketStatus(false);
				playerVehicleObject->setMineStatus(false);
				playerVehicleObject->setShieldStatus(false);

				CCLOG("Gun Is Activated");

				//REMOVE THE SPRITE FROM SCENE
				contactA->getNode()->removeFromParent();

				return true;
			}
		}

		else if ((contactA->getCollisionBitmask() == 8) && (contactB->getCollisionBitmask() == 5) && (*it)->getID() == 2)
		{
			for (it = weaponPickups.begin(); it != weaponPickups.end(); it++)
			{
				//SETS ROCKET BOOL TO TRUE WHILE
				//OTHER WEAPONS ARE SET TO FALS
				playerVehicleObject->setMachineGunStatus(false);
				playerVehicleObject->setRocketStatus(true);
				playerVehicleObject->setMineStatus(false);
				playerVehicleObject->setShieldStatus(false);

				CCLOG("Rocket Is Activated");

				//REMOVE THE SPRITE FROM SCENE
				contactA->getNode()->removeFromParent();

				return true;
			}
		}

		else if ((contactA->getCollisionBitmask() == 8) && (contactB->getCollisionBitmask() == 5) && (*it)->getID() == 3)
		{
			for (it = weaponPickups.begin(); it != weaponPickups.end(); it++)
			{
				//SETS MINE BOOL TO TRUE WHILE
				//OTHER WEAPONS ARE SET TO FALS
				playerVehicleObject->setMachineGunStatus(false);
				playerVehicleObject->setRocketStatus(false);
				playerVehicleObject->setMineStatus(true);
				playerVehicleObject->setShieldStatus(false);

				CCLOG("LandMine Is Activated");

				//REMOVE THE SPRITE FROM SCENE
				contactA->getNode()->removeFromParent();

				return true;
			}
		}

		else if ((contactA->getCollisionBitmask() == 8) && (contactB->getCollisionBitmask() == 5) && (*it)->getID() == 4)
		{
			for (it = weaponPickups.begin(); it != weaponPickups.end(); it++)
			{
				//SETS SHIELD BOOL TO TRUE WHILE
				//OTHER WEAPONS ARE SET TO FALS
				playerVehicleObject->setMachineGunStatus(false);
				playerVehicleObject->setRocketStatus(false);
				playerVehicleObject->setMineStatus(false);
				playerVehicleObject->setShieldStatus(true);

				CCLOG("Shield Is Activated");

				//REMOVE THE SPRITE FROM SCENE
				contactA->getNode()->removeFromParent();

				return true;
			}
		}
	}

	//PLAYER SHIP COMES IN CONTACT WITH OBSTACLES - SAMUEL
	if ((contactA->getCollisionBitmask() == 9) && (contactB->getCollisionBitmask() == 5) || (contactA->getCollisionBitmask() == 5) && (contactB->getCollisionBitmask() == 9))
	{
		CCLOG("There Is Contact Between The Obstacle And Player Ship");

		return true;
	};

	//PLAYER SHIP COMES IN CONTACT WITH TURRET BODY - SAMUEL
	if ((contactA->getCollisionBitmask() == 10) && (contactB->getCollisionBitmask() == 5) || (contactA->getCollisionBitmask() == 5) && (contactB->getCollisionBitmask() == 10))
	{
		CCLOG("There Is Contact Between The Turret Body And Player Ship");

		return true;
	};

	//PLAYER SHIP COMES IN CONTACT WITH TURRET BULLET - SAMUEL
	if ((contactA->getCollisionBitmask() == 11) && (contactB->getCollisionBitmask() == 5) || (contactA->getCollisionBitmask() == 5) && (contactB->getCollisionBitmask() == 11))
	{
		CCLOG("There Is Contact Between The Turret Bullet And Player Ship");
		playerHealth = playerHealth - 20;

		contactA->getNode()->removeFromParent();
		return true;
	};

	if ((contactA->getCollisionBitmask() == 5) && (contactB->getCollisionBitmask() == 11) || (contactA->getCollisionBitmask() == 11) && (contactB->getCollisionBitmask() == 5))
	{
		CCLOG("There Is Contact Between The Turret Bullet And Player Ship");
		playerHealth = playerHealth - 20;

		contactB->getNode()->removeFromParent();
		return true;
	};

	//TURRET BULLET COMES IN CONTACT WALL - SAMUEL
	if ((contactA->getCollisionBitmask() == 11) && (contactB->getCollisionBitmask() == 1) || (contactA->getCollisionBitmask() == 1) && (contactB->getCollisionBitmask() == 11))
	{
		CCLOG("There Is Contact Between The Turret Bullet And Wall");

		contactA->getNode()->removeFromParent();
		return true;
	};

	if ((contactA->getCollisionBitmask() == 1) && (contactB->getCollisionBitmask() == 11) || (contactA->getCollisionBitmask() == 11) && (contactB->getCollisionBitmask() == 1))
	{
		CCLOG("There Is Contact Between The Wall And Turret Bullet");

		contactB->getNode()->removeFromParent();
		return true;
	};


	return true;
};

//IS KEY PRESSED FUNCTION - DANIEL GADD
bool SecondWorld::isKeyPressed(EventKeyboard::KeyCode code)
{
	if (keys.find(code) != keys.end())
	{
		return true;
	}

	return false;
};

//KEY PRESSED DURATION FUNCTION - DANIEL GADD
double SecondWorld::keyPressedDuration(EventKeyboard::KeyCode code)
{
	if (!isKeyPressed(EventKeyboard::KeyCode::KEY_CTRL))
	{
		return 0;
	}

	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - keys[code]).count();
};

//UPDATE FUNCTION - SAMANTHA, SAMUEL & DANIEL
void SecondWorld::update(float delta)
{
	//UPDATES THE HUD LAYER POSITION - SAMANTHA
	HUD->setPosition(playerVehicleObject->getSprite()->getPosition().x - visibleSize.width / 2, playerVehicleObject->getSprite()->getPosition().y - visibleSize.height / 2);

	//UPDATES THE LAP NUMBER - SAMANTHA
	lapNumber->setString("LAP NUMBER: " + std::to_string(lapCounter) + "/10");

	//UPDATES TIMER - SAMUEL
	time += delta;
	__String *timeToDisplay = __String::createWithFormat("%.2f", time);
	timer->setString(timeToDisplay->getCString());

	//----------------------------------------------------------------
	//PROJECTILES COLLISION - EXPLOSION ON COLLISION -  REDUCE HEALTH OF VEHICLES - DESTROY VEHICLE/OBJECTS - DANIEL
	if (!projectiles.empty())
	{
		for (auto vehicle : this->vehicles)
		{

			//CHECKING PROJECTILES AGAINST VEHICLES - INTERSECTION
			for (auto projectile : this->projectiles)
			{
				cocos2d::Rect rect1 = vehicle->getSprite()->getBoundingBox();
				cocos2d::Rect rect2 = projectile->getSprite()->getBoundingBox();

				//CHECK FOR INTERSECTIONS AND SPAWN EXPLOSIONS
				if (rect1.intersectsRect(rect2) && vehicle->getType() != "player")
				{
					vehicle->setDamage(projectile->returnType());
					cocos2d::Vec2 location = projectile->getSprite()->getPosition();//SAVE INTERSECTION POINT TO SPAWN EXPLOSION
					auto it = find(projectiles.begin(), projectiles.end(), projectile);//FIND CURRENT PROJECTILE
					if (it != projectiles.end())projectiles.erase(it);//ERASE CURRENT PROJECTILE
					this->removeChild(projectile->getSprite());
					projectile->DisposeObject();
					Explosion* explosion = new Explosion();
					explosion->getSprite()->setPosition(location);
					this->addChild(explosion->getSprite());
					explosion->explode();
					break;
				}
			}
		}

	}
	for (auto vehicle : this->vehicles)
	{
		//CHECK FOR VEHICLE HEALTH & EXPLODE IF DEAD
		if (vehicle->isDead())
		{
			cocos2d::Vec2 position = vehicle->getSprite()->getPosition();
			this->removeChild(vehicle->getSprite());
			auto it = find(vehicles.begin(), vehicles.end(), vehicle);//FIND CURRENT PROJECTILE
			if (it != vehicles.end())vehicles.erase(it);//ERASE CURRENT PROJECTILE
			vehicle->destroyVehicle();
			ExplosionLarge* explosionLarge = new ExplosionLarge();
			explosionLarge->getSprite()->setPosition(position);
			this->addChild(explosionLarge->getSprite());
			explosionLarge->explode();
			break;
		}
	}
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	//WEAPON TIMER 10 SECONDS DURATION OF SHIELD ACVTIVE - SAMUAL
	if (activeWeaponTimer)
	{
		if (weaponTimer < 10)
		{
			//TIMER - SAMUEL
			weaponTimer += delta;
		}
		else if (weaponTimer >= 10)
		{
			playerVehicleObject->endWeapon();
			activeWeaponTimer = false;
		}
	}
	weaponLabel->setString(playerVehicleObject->getWeapon());
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	//FINISH LINE - SAMANTHA
	if (!finishLines.empty())//CHECK FOR VEHICLE INTERSECTING WAY POINTS - MARK WAY POINT CROSSED - ADD WAY POINT NUMBER TO VECTOR FOR ORDER CHECKING IN NEXT SECTION 
	{
		for (auto finishLine : this->finishLines)
		{
			Rect rect1 = playerVehicleObject->getSprite()->getBoundingBox();
			Rect rect2 = finishLine->getSprite()->getBoundingBox();
			if (rect1.intersectsRect(rect2))
			{
				if (!finishLine->getActive())
				{
					finishLine->setActive(true);
					finishLineTriggers.push_back(finishLine->getID());
					CCLOG("FINISH LINE INTERSECTION");

					if (finishLineTriggers.size() > 2)//WE MAKE SURE OUR VECTOR ONLY HAS THREE ITEMS - MAKE SURE ITEMS ARE IN CORRECT ORDER FROM LOW TO HIGH, ELSE WE ARE GOING BACKWARDS
					{
						if (finishLineTriggers.size() > 3) { finishLineTriggers.erase(finishLineTriggers.begin()); }//KEEP IT AT THREE MAX

						int lowest = 0;
						int inc = 0;//CHECK IF WE ARE GOING RIGHT WAY ACROSS LINES
						int dec = 2;//CHECK IF WE ARE GOING WRONG WAY ACROSS LINES

						for (auto finishLineTrigger : this->finishLineTriggers)
						{
							if (lowest == 0) { lowest = finishLineTrigger; }

							if (lowest == 3 && finishLineTrigger == 1)//RESTART
							{
								lowest = finishLineTrigger;//MAKE IT ONE AGAIN
								CCLOG("FL BLANK");
							}
							else
							{
								if (lowest < finishLineTrigger)//CHECK IF WE ARE GOING RIGHT WAY ACROSS LINES
								{
									inc++;
									if (inc == 2)
									{
										lapCounter++;
										lapNumber->setString(std::to_string(lapCounter) + "/10");
									}
									lowest = finishLineTrigger;
								}
								else if (lowest > finishLineTrigger)//CHECK IF WE ARE GOING WRONG WAY ACROSS LINES
								{
									dec--;
									if (dec == 0)
									{
										lapCounter--;
										lapNumber->setString(std::to_string(lapCounter) + "/10");
									}
									lowest = finishLineTrigger;
								}
							}

						}

					}
				}


			}
			else
			{
				finishLine->setActive(false);
			}
		}
	}
	//----------------------------------------------------------------

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

	//----------------------------------------------------------------
	//ENEMY ONE VEHICLE CALCULATION - - VELOCITY - DRIVE - DANIEL - SAMUEL
	for (auto vehicle : this->vehicles)
	{
		if (vehicle->getType() == "enemy")
		{
			vehicle->moveWayPointSprite(vehicle->getCurrentWayPoint());

			vehicle->autoControlAI(vehicle->getCurrentWayPoint());
			if (vehicle->getActiveStatus())
			{
				vehicle->setVelocityPoint();
				vehicle->setVelocity();
				if (vehicle->wayPointCollision(vehicle->returnWayPointSprite()))
				{
					WayPoint[vehicle->getWayPointCounter()] = false;

					if (vehicle->getWayPointCounter() == 61)//CHECK IF AT END OF WAY POINTS AND RESET BACK TO ONE SO WE CAN DO MORE LAPS
					{
						vehicle->setWayPointCounter(0);
						WayPoint[vehicle->getWayPointCounter()] = true;
					}
					else
					{
						vehicle->setWayPointCounter(vehicle->getWayPointCounter() + 1);
						WayPoint[vehicle->getWayPointCounter()] = true;
					}
					vehicle->setCurrentWayPoint(WayPoints[vehicle->getWayPointCounter()][vehicle->getCornering()]);
					vehicle->moveWayPointSprite(vehicle->getCurrentWayPoint());
				}
			}
			//CHECK IF ENEMY ONE IS COLLIDING WITH CURRENT WAY POINT
		}

	}
	//ENEMY ONE VEHICLE CALCULATION - DANIEL
	//----------------------------------------------------------------

	//THRUSTER FUEL PERCENTAGE - SAMANTHA
	if (playerThrusterfuel == 100)
	{
		this->thrusterTimer->setPercentage(100);
	}
	if (playerThrusterfuel == 90)
	{
		this->thrusterTimer->setPercentage(90);
	}
	if (playerThrusterfuel == 80)
	{
		this->thrusterTimer->setPercentage(80);
	}
	if (playerThrusterfuel == 70)
	{
		this->thrusterTimer->setPercentage(70);
	}
	if (playerThrusterfuel == 60)
	{
		this->thrusterTimer->setPercentage(60);
	}
	if (playerThrusterfuel == 50)
	{
		this->thrusterTimer->setPercentage(50);
	}
	if (playerThrusterfuel == 40)
	{
		this->thrusterTimer->setPercentage(40);
	}
	if (playerThrusterfuel == 30)
	{
		this->thrusterTimer->setPercentage(30);
	}
	if (playerThrusterfuel == 20)
	{
		this->thrusterTimer->setPercentage(20);
	}
	if (playerThrusterfuel == 10)
	{
		this->thrusterTimer->setPercentage(10);
	}
	if (playerThrusterfuel == 0)
	{
		this->thrusterTimer->setPercentage(0);
	}
	if (playerThrusterfuel > 100)
	{
		playerThrusterfuel = 100;
		this->thrusterTimer->setPercentage(100);
	}

	//HEALTH PERCENTAGE - SAMANTHA
	if (playerHealth == 100)
	{
		this->healthTimer->setPercentage(100);
	}
	if (playerHealth == 90)
	{
		this->healthTimer->setPercentage(90);
	}
	if (playerHealth == 80)
	{
		this->healthTimer->setPercentage(80);
	}
	if (playerHealth == 70)
	{
		this->healthTimer->setPercentage(70);
	}
	if (playerHealth == 60)
	{
		this->healthTimer->setPercentage(60);
	}
	if (playerHealth == 50)
	{
		this->healthTimer->setPercentage(50);
	}
	if (playerHealth == 40)
	{
		this->healthTimer->setPercentage(40);
	}
	if (playerHealth == 30)
	{
		this->healthTimer->setPercentage(30);
	}
	if (playerHealth == 20)
	{
		this->healthTimer->setPercentage(20);
	}
	if (playerHealth == 10)
	{
		this->healthTimer->setPercentage(10);
	}
	if (playerHealth == 0)
	{
		this->healthTimer->setPercentage(0);
	}
	if (playerHealth > 100)
	{
		playerHealth = 100;
		this->healthTimer->setPercentage(100);
	}

	//SPEED INDICATOR - SAMANTHA
	if (playerVehicleObject->getSpeed() == 100)
	{
		this->speedTimer->setPercentage(100);
	}
	if (playerVehicleObject->getSpeed() >= 50 && playerVehicleObject->getSpeed() <= 100)
	{
		this->speedTimer->setPercentage(82);
	}
	if (playerVehicleObject->getSpeed() >= 40 && playerVehicleObject->getSpeed() <= 50)
	{
		this->speedTimer->setPercentage(66);
	}
	if (playerVehicleObject->getSpeed() >= 30 && playerVehicleObject->getSpeed() <= 40)
	{
		this->speedTimer->setPercentage(49);
	}
	if (playerVehicleObject->getSpeed() >= 20 && playerVehicleObject->getSpeed() <= 20)
	{
		this->speedTimer->setPercentage(33);
	}
	if (playerVehicleObject->getSpeed() >= 10 && playerVehicleObject->getSpeed() <= 20)
	{
		this->speedTimer->setPercentage(17);
	}
	if (playerVehicleObject->getSpeed() == 0)
	{
		this->speedTimer->setPercentage(0);
	}
	if (playerVehicleObject->getSpeed() > 100)
	{
		this->speedTimer->setPercentage(100);
	}

	//END RACE - SAMANTHA
	this->endRace();
};

std::map<cocos2d::EventKeyboard::KeyCode, std::chrono::high_resolution_clock::time_point> SecondWorld::keys;

//TRACK FUNCTION - SAMANTHA
void SecondWorld::track()
{
	//TRACK BACKGROUD - SAMANTHA
	//Sets The Image For The trackBackground Sprite
	trackBackground = Sprite::create("TrackTwo/tracktwobackground.png");

	//Sets The trackBackground Sprite To The Scene On Layer 0
	this->addChild(trackBackground, 0);

	//TRACK INNER RIM - SAMANTHA
	//Sets The Image For The trackInsprite
	trackInsprite = Sprite::create("TrackTwo/tracktwoinnerrim.png");

	//An Array For All The Points Along The Inner Track
	trackInarray[0] = Point(-3500 / TIscale, 800 / TIscale);
	trackInarray[1] = Point(-2900 / TIscale, 800 / TIscale);
	trackInarray[2] = Point(-2800 / TIscale, 700 / TIscale);
	trackInarray[3] = Point(-2800 / TIscale, -400 / TIscale);
	trackInarray[4] = Point(-2700 / TIscale, -500 / TIscale);
	trackInarray[5] = Point(-1100 / TIscale, -500 / TIscale);
	trackInarray[6] = Point(-1000 / TIscale, -400 / TIscale);
	trackInarray[7] = Point(-1000 / TIscale, 0 / TIscale);
	trackInarray[8] = Point(-900 / TIscale, 100 / TIscale);
	trackInarray[9] = Point(-700 / TIscale, 100 / TIscale);
	trackInarray[10] = Point(-300 / TIscale, -300 / TIscale);
	trackInarray[11] = Point(3100 / TIscale, -300 / TIscale);
	trackInarray[12] = Point(3500 / TIscale, 100 / TIscale);
	trackInarray[13] = Point(3500 / TIscale, 900 / TIscale);
	trackInarray[14] = Point(3600 / TIscale, 1000 / TIscale);
	trackInarray[15] = Point(3700 / TIscale, 900 / TIscale);
	trackInarray[16] = Point(3700 / TIscale, -1000 / TIscale);
	trackInarray[17] = Point(3600 / TIscale, -1100 / TIscale);
	trackInarray[18] = Point(1200 / TIscale, -1100 / TIscale);
	trackInarray[19] = Point(1000 / TIscale, -900 / TIscale);
	trackInarray[20] = Point(-100 / TIscale, -900 / TIscale);
	trackInarray[21] = Point(-300 / TIscale, -700 / TIscale);
	trackInarray[22] = Point(-3000 / TIscale, -700 / TIscale);
	trackInarray[23] = Point(-3300 / TIscale, -1000 / TIscale);
	trackInarray[24] = Point(-3500 / TIscale, -1000 / TIscale);
	trackInarray[25] = Point(-3500 / TIscale, -600 / TIscale);
	trackInarray[26] = Point(-3200 / TIscale, -300 / TIscale);
	trackInarray[27] = Point(-3200 / TIscale, 500 / TIscale);
	trackInarray[28] = Point(-3500 / TIscale, 800 / TIscale);

	//Creates The Type Of Physics Body -> Edge Polygon Physics Body Is Being Created Here
	trackInphysics = PhysicsBody::createEdgePolygon(trackInarray, 28, PhysicsMaterial(0, 0, 0), 30);

	//Sets The Physics Body's Collision Bitmask Which Will Be Used When The Sprite
	//Is Collided With. Collision Bitmask Gives Me More Control Over What Happens When
	//The Sprite Is In Contact With Another Sprite. It Also Allows The Program To
	//Know What Sprite Has Collided With Another.
	trackInphysics->setCollisionBitmask(1);

	//Sets The Physics Body Contact To True. This Makes The Sprite Collidable
	trackInphysics->setContactTestBitmask(true);

	//Sets The Physics Body Onto The Sprite Itself
	trackInsprite->setPhysicsBody(trackInphysics);

	//Sets The trackInsprite Sprite To The Scene On Layer 1
	this->addChild(trackInsprite, 1);

	//TRACK ISLAND - SAMANTHA
	//Sets The Image For The trackIslandsprite
	trackIslandsprite = Sprite::create("TrackTwo/tracktwoisland.png");

	//An Array For All The Points Along The Track Island
	trackIslandarray[0] = Point(-3500 / TIscale, 500 / TIscale);
	trackIslandarray[1] = Point(-3500 / TIscale, -300 / TIscale);
	trackIslandarray[2] = Point(-3600 / TIscale, -300 / TIscale);
	trackIslandarray[3] = Point(-3600 / TIscale, 400 / TIscale);
	trackIslandarray[4] = Point(-3500 / TIscale, 500 / TIscale);

	//Creates The Type Of Physics Body -> Edge Polygon Physics Body Is Being Created Here
	trackIslandphysics = PhysicsBody::createEdgePolygon(trackIslandarray, 4, PhysicsMaterial(0, 0, 0), 30);

	//Sets The Physics Body's Collision Bitmask Which Will Be Used When The Sprite
	//Is Collided With. Collision Bitmask Gives Me More Control Over What Happens When
	//The Sprite Is In Contact With Another Sprite. It Also Allows The Program To
	//Know What Sprite Has Collided With Another.
	trackIslandphysics->setCollisionBitmask(1);

	//Sets The Physics Body Contact To True. This Makes The Sprite Collidable
	trackIslandphysics->setContactTestBitmask(true);

	//Sets The Physics Body Onto The Sprite Itself
	trackIslandsprite->setPhysicsBody(trackIslandphysics);

	//Sets The trackIslandsprite Sprite To The Scene On Layer 1
	this->addChild(trackIslandsprite, 1);

	//TRACK OUTER RIM - SAMANTHA
	//Sets The Image For The trackOutsprite
	trackOutsprite = Sprite::create("TrackTwo/tracktwoouterrim.png");

	//An Array For All The Points Along The Outer Track
	trackOutarray[0] = Point(-4000 / TIscale, 1400 / TIscale);
	trackOutarray[1] = Point(-3500 / TIscale, 1400 / TIscale);
	trackOutarray[2] = Point(-3400 / TIscale, 1500 / TIscale);
	trackOutarray[3] = Point(-2900 / TIscale, 1500 / TIscale);
	trackOutarray[4] = Point(-2800 / TIscale, 1400 / TIscale);
	trackOutarray[5] = Point(-2500 / TIscale, 1400 / TIscale);
	trackOutarray[6] = Point(-2300 / TIscale, 1200 / TIscale);
	trackOutarray[7] = Point(-2300 / TIscale, 200 / TIscale);
	trackOutarray[8] = Point(-2100 / TIscale, 0 / TIscale);
	trackOutarray[9] = Point(-1600 / TIscale, 0 / TIscale);
	trackOutarray[10] = Point(-1400 / TIscale, 200 / TIscale);
	trackOutarray[11] = Point(-1400 / TIscale, 700 / TIscale);
	trackOutarray[12] = Point(-1300 / TIscale, 800 / TIscale);
	trackOutarray[13] = Point(-600 / TIscale, 800 / TIscale);
	trackOutarray[14] = Point(-100 / TIscale, 300 / TIscale);
	trackOutarray[15] = Point(1200 / TIscale, 300 / TIscale);
	trackOutarray[16] = Point(1300 / TIscale, 400 / TIscale);
	trackOutarray[17] = Point(2000 / TIscale, 400 / TIscale);
	trackOutarray[18] = Point(2100 / TIscale, 300 / TIscale);
	trackOutarray[19] = Point(2700 / TIscale, 300 / TIscale);
	trackOutarray[20] = Point(2900 / TIscale, 500 / TIscale);
	trackOutarray[21] = Point(2900 / TIscale, 1500 / TIscale);
	trackOutarray[22] = Point(3100 / TIscale, 1700 / TIscale);
	trackOutarray[23] = Point(4200 / TIscale, 1700 / TIscale);
	trackOutarray[24] = Point(4400 / TIscale, 1500 / TIscale);
	trackOutarray[25] = Point(4400 / TIscale, -1800 / TIscale);
	trackOutarray[26] = Point(2700 / TIscale, -1800 / TIscale);
	trackOutarray[27] = Point(2600 / TIscale, -1900 / TIscale);
	trackOutarray[28] = Point(1900 / TIscale, -1900 / TIscale);
	trackOutarray[29] = Point(1800 / TIscale, -1800 / TIscale);
	trackOutarray[30] = Point(800 / TIscale, -1800 / TIscale);
	trackOutarray[31] = Point(500 / TIscale, -1600 / TIscale);
	trackOutarray[32] = Point(-600 / TIscale, -1600 / TIscale);
	trackOutarray[33] = Point(-1000 / TIscale, -1200 / TIscale);
	trackOutarray[34] = Point(-2500 / TIscale, -1200 / TIscale);
	trackOutarray[35] = Point(-3100 / TIscale, -1800 / TIscale);
	trackOutarray[36] = Point(-4100 / TIscale, -1800 / TIscale);
	trackOutarray[37] = Point(-4100 / TIscale, 1300 / TIscale);
	trackOutarray[38] = Point(-4000 / TIscale, 1400 / TIscale);

	//Creates The Type Of Physics Body -> Edge Polygon Physics Body Is Being Created Here
	trackOutphysics = PhysicsBody::createEdgePolygon(trackOutarray, 38, PhysicsMaterial(0, 0, 0), 30);

	//Sets The Physics Body's Collision Bitmask Which Will Be Used When The Sprite
	//Is Collided With. Collision Bitmask Gives Me More Control Over What Happens When
	//The Sprite Is In Contact With Another Sprite. It Also Allows The Program To
	//Know What Sprite Has Collided With Another.
	trackOutphysics->setCollisionBitmask(1);

	//Sets The Physics Body Contact To True. This Makes The Sprite Collidable
	trackOutphysics->setContactTestBitmask(true);

	//Sets The Physics Body Onto The Sprite Itself
	trackOutsprite->setPhysicsBody(trackOutphysics);

	//Sets The trackOutsprite Sprite To The Scene On Layer 1
	this->addChild(trackOutsprite, 1);
};

//FINISH LINE FUNCTION - SAMANTHA MARAH
void SecondWorld::finishLine()
{
	FinishLine* lineOne = new FinishLine();
	FinishLine* lineTwo = new FinishLine();
	FinishLine* lineThree = new FinishLine();

	//WE HAVE THREE LINES WITH 3 ID's. VEHICLE MUST ADD THEM TO VECTOR IN CORRECT ORDER FOR LAP TO INCREMENT - BY INTERSECTING THEM IN UPDATE
	lineOne->getSprite()->setPosition(cocos2d::Vec2(-2500 / TIscale, 250 / TIscale));
	lineOne->setID(3);
	this->addChild(lineOne->getSprite());
	finishLines.push_back(lineOne);

	lineTwo->getSprite()->setPosition(cocos2d::Vec2(-2500 / TIscale, -0 / TIscale));
	lineTwo->setID(2);
	this->addChild(lineTwo->getSprite());
	finishLines.push_back(lineTwo);

	lineThree->getSprite()->setPosition(cocos2d::Vec2(-2500 / TIscale, -250 / TIscale));
	lineThree->setID(1);
	this->addChild(lineThree->getSprite());
	finishLines.push_back(lineThree);
};

//AI WAYPOINTS FUNCTION - SAMUEL MACSWEENEY
void SecondWorld::AIWayPoints()
{
	//WE HAVE THIS EXTRA ARRAY HANDY FOR DIFFERENT USES - WE INITIALIZE THEM ALL FALSE
	for (int i = 0; i < 37; i++)
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

	for (auto vehicle : this->vehicles)
	{
		vehicle->setCurrentWayPoint(WayPoints[vehicle->getWayPointCounter()][vehicle->getCornering()]);
		this->addChild(vehicle->returnWayPointSprite());
		vehicle->moveWayPointSprite(vehicle->getCurrentWayPoint());
	}
};

//VEHICLES OBJECTS FOR OUR FIRST SCENE - DANIEL
void SecondWorld::vehicleObjects()
{
	//PLAYER VEHICLE OBJECT - DANIEL
	playerVehicleObject = new Vehicle();
	playerVehicleObject->setAngle(-90);
	playerVehicleObject->setPosition(Vec2(-3700 / TIscale, -500 / TIscale));
	playerVehicleObject->setSteeringPower(1);
	playerVehicleObject->setCornering(1);
	playerVehicleObject->setType("player");
	this->addChild(playerVehicleObject->getSprite(), 9);
	vehicles.push_back(playerVehicleObject);

	//AI CAR I VEHICLE OBJECT - DANIEL
	enemyOneVehicleObject = new Vehicle();
	enemyOneVehicleObject->setAngle(-90);
	enemyOneVehicleObject->setPosition(Vec2(-3700 / TIscale, -700 / TIscale));
	enemyOneVehicleObject->setAutoControl(true);
	enemyOneVehicleObject->setSpeed(95);
	enemyOneVehicleObject->setCornering(1);
	enemyOneVehicleObject->setSteeringPower(2);
	enemyOneVehicleObject->setType("enemy");
	this->addChild(enemyOneVehicleObject->getSprite(), 9);
	vehicles.push_back(enemyOneVehicleObject);

	//AI CAR II VEHICLE OBJECT - DANIEL
	enemyTwoVehicleObject = new Vehicle();
	enemyTwoVehicleObject->setAngle(-90);
	enemyTwoVehicleObject->setPosition(Vec2(-3900 / TIscale, -500 / TIscale));
	enemyTwoVehicleObject->setAutoControl(true);
	enemyTwoVehicleObject->setSpeed(105);
	enemyTwoVehicleObject->setCornering(2);
	enemyTwoVehicleObject->setSteeringPower(2);
	enemyTwoVehicleObject->setType("enemy");
	this->addChild(enemyTwoVehicleObject->getSprite(), 9);
	vehicles.push_back(enemyTwoVehicleObject);

	//AI CAR III VEHICLE OBJECT - DANIEL
	enemyThreeVehicleObject = new Vehicle();
	enemyThreeVehicleObject->setAngle(-90);
	enemyThreeVehicleObject->setPosition(Vec2(-3900 / TIscale, -700 / TIscale));
	enemyThreeVehicleObject->setAutoControl(true);
	enemyThreeVehicleObject->setSpeed(120);
	enemyThreeVehicleObject->setCornering(3);
	enemyThreeVehicleObject->setSteeringPower(2);
	enemyThreeVehicleObject->setType("enemy");
	this->addChild(enemyThreeVehicleObject->getSprite(), 9);
	vehicles.push_back(enemyThreeVehicleObject);

	this->runAction(cocos2d::Follow::create(playerVehicleObject->getSprite()));
}

//THRUSTER PICKUP FUNCTION - SAMANTHA MARAH
void SecondWorld::thrusterPickup()
{
	//ALL THE THRUSTER PICKUP OBJECTS IN THIS TRACK
	PickUps* t1 = new ThrusterPickup(); //CREATES THRUSTERPICKUP OBJECT AND ASSIGNS IT TO t1
	t1->getSprite()->setPosition(3800 / TIscale, -500 / TIscale); //SETS THE POSITION OF t1
	t1->rotate(); //CALLS THE ROTATE FUNCTION FOR t1
	this->addChild(t1->getSprite(), 2); //ADDS T1 TO THE SCENE LAYER 2

	PickUps* t2 = new ThrusterPickup(); //CREATES THRUSTERPICKUP OBJECT AND ASSIGNS IT TO t2
	t2->getSprite()->setPosition(4300 / TIscale, -500 / TIscale); //SETS THE POSITION OF t2
	t2->rotate(); //CALLS THE ROTATE FUNCTION FOR t2
	this->addChild(t2->getSprite(), 2); //ADDS T2 TO THE SCENE LAYER 2

	PickUps* t3 = new ThrusterPickup(); //CREATES THRUSTERPICKUP OBJECT AND ASSIGNS IT TO t3
	t3->getSprite()->setPosition(-800 / TIscale, 400 / TIscale); //SETS THE POSITION OF t3
	t3->rotate(); //CALLS THE ROTATE FUNCTION FOR t3
	this->addChild(t3->getSprite(), 2); //ADDS T3 TO THE SCENE LAYER 2
};

//HEALTH PICKUP FUNCTION - SAMANTHA MARAH
void SecondWorld::healthPickup()
{
	//ALL HEALTH PICKUP OBJECTS IN THIS TRACK
	PickUps* h1 = new HealthPickup(); //CREATES HEALTHPICKUP OBJECT AND ASSIGNS IT TO h1
	h1->getSprite()->setPosition(4050 / TIscale, -500 / TIscale); //SETS THE POSITION OF h1
	h1->rotate(); //CALLS THE ROTATE FUNCTION FOR h1
	this->addChild(h1->getSprite(), 2); //ADDS h1 TO THE SCENE LAYER 2

	PickUps* h2 = new HealthPickup(); //CREATES HEALTHPICKUP OBJECT AND ASSIGNS IT TO h2
	h2->getSprite()->setPosition(-800 / TIscale, 200 / TIscale); //SETS THE POSITION OF h2
	h2->rotate(); //CALLS THE ROTATE FUNCTION FOR h2
	this->addChild(h2->getSprite(), 2); //ADDS h2 TO THE SCENE LAYER 2

	PickUps* h3 = new HealthPickup(); //CREATES HEALTHPICKUP OBJECT AND ASSIGNS IT TO h3
	h3->getSprite()->setPosition(-800 / TIscale, 600 / TIscale); //SETS THE POSITION OF h3
	h3->rotate(); //CALLS THE ROTATE FUNCTION FOR h3
	this->addChild(h3->getSprite(), 2); //ADDS h3 TO THE SCENE LAYER 2
};

//WEAPON-SHIELD PICKUP FUNCTION - SAMANTHA MARAH
void SecondWorld::weaponShieldPickup()
{
	//ALL THE WEAPON-SHIELD PICKUP OBJECTS IN THIS TRACK
	PickUps* ws1 = new WeaponShieldPickup(); //CREATES WEAPONSHIELDPICKUP OBJECT AND ASSIGNS IT TO ws1
	ws1->getSprite()->setPosition(2000 / TIscale, -200 / TIscale); //SETS THE POSITION OF ws1
	ws1->rotate(); //CALLS THE ROTATE FUNCTION FOR ws1
	this->addChild(ws1->getSprite(), 2); //ADDS ws1 TO THE SCENE LAYER 2

	PickUps* ws2 = new WeaponShieldPickup(); //CREATES WEAPONSHIELDPICKUP OBJECT AND ASSIGNS IT TO ws2
	ws2->getSprite()->setPosition(2000 / TIscale, 0 / TIscale); //SETS THE POSITION OF ws2
	ws2->rotate(); //CALLS THE ROTATE FUNCTION FOR ws2
	this->addChild(ws2->getSprite(), 2); //ADDS ws2 TO THE SCENE LAYER 2

	PickUps* ws3 = new WeaponShieldPickup(); //CREATES WEAPONSHIELDPICKUP OBJECT AND ASSIGNS IT TO ws3
	ws3->getSprite()->setPosition(2000 / TIscale, 200 / TIscale); //SETS THE POSITION OF ws3
	ws3->rotate(); //CALLS THE ROTATE FUNCTION FOR ws3
	this->addChild(ws3->getSprite(), 2); //ADDS ws3 TO THE SCENE LAYER 2

	PickUps* ws4 = new WeaponShieldPickup(); //CREATES WEAPONSHIELDPICKUP OBJECT AND ASSIGNS IT TO ws4
	ws4->getSprite()->setPosition(1000 / TIscale, -1100 / TIscale); //SETS THE POSITION OF ws4
	ws4->rotate(); //CALLS THE ROTATE FUNCTION FOR ws4
	this->addChild(ws4->getSprite(), 2); //ADDS ws4 TO THE SCENE LAYER 2

	PickUps* ws5 = new WeaponShieldPickup(); //CREATES WEAPONSHIELDPICKUP OBJECT AND ASSIGNS IT TO ws5
	ws5->getSprite()->setPosition(800 / TIscale, -1300 / TIscale); //SETS THE POSITION OF ws5
	ws5->rotate(); //CALLS THE ROTATE FUNCTION FOR ws5
	this->addChild(ws5->getSprite(), 2); //ADDS ws5 TO THE SCENE LAYER 2

	PickUps* ws6 = new WeaponShieldPickup(); //CREATES WEAPONSHIELDPICKUP OBJECT AND ASSIGNS IT TO ws6
	ws6->getSprite()->setPosition(600 / TIscale, -1500 / TIscale); //SETS THE POSITION OF ws6
	ws6->rotate(); //CALLS THE ROTATE FUNCTION FOR ws6
	this->addChild(ws6->getSprite(), 2); //ADDS ws6 TO THE SCENE LAYER 2

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

	//SHOWS THE ID FOR EACH WEAPONSHIELDPICKUP IN THE DEBUG LOG
	//USED FOR DEBUGGING
	for (it = weaponPickups.begin(); it != weaponPickups.end(); it++)
	{
		(*it)->seeID();
	}
};

//CIRCLE FUNCTION - SAMUEL MACSWEENEY
void SecondWorld::circleCircuit()
{
	//CIRCLE CIRCUIT OBSTACLE - SAMUEL
	GameObjectPhysics* circle1 = new Circle();
	circle1->getSprite()->setPosition(3800 / TIscale, -300 / TIscale);
	this->addChild(circle1->getSprite(), 4);

	GameObjectPhysics* circle2 = new Circle();
	circle2->getSprite()->setPosition(-3700 / TIscale, -300 / TIscale);
	this->addChild(circle2->getSprite(), 4);

	GameObjectPhysics* circle3 = new Circle();
	circle3->getSprite()->setPosition(-3900 / TIscale, 1200 / TIscale);
	this->addChild(circle3->getSprite(), 4);

	GameObjectPhysics* circle4 = new Circle();
	circle4->getSprite()->setPosition(-900 / TIscale, 200 / TIscale);
	this->addChild(circle4->getSprite(), 4);
};

//SQUARE FUNCTION - SAMUEL MACSWEENEY
void  SecondWorld::squareCircuit()
{
	//SQUARE CIRCUIT OBSTACLE - SAMUEL
	GameObjectPhysics* square1 = new Square();
	square1->getSprite()->setPosition(3800 / TIscale, -400 / TIscale);
	this->addChild(square1->getSprite(), 4);

	GameObjectPhysics* square2 = new Square();
	square2->getSprite()->setPosition(-3800 / TIscale, -350 / TIscale);
	this->addChild(square2->getSprite(), 4);

	GameObjectPhysics* square3 = new Square();
	square3->getSprite()->setPosition(-3900 / TIscale, 1250 / TIscale);
	this->addChild(square3->getSprite(), 4);

	GameObjectPhysics* square4 = new Square();
	square4->getSprite()->setPosition(-900 / TIscale, 250 / TIscale);
	this->addChild(square4->getSprite(), 4);
};

//TRIANGLE FUNCTION - SAMUEL MACSWEENEY
void SecondWorld::triangleCircuit()
{
	//TRIANGLE CIRCUIT OBSTACLE - SAMUEL
	GameObjectPhysics* triangle1 = new Triangle();
	triangle1->getSprite()->setPosition(3805 / TIscale, -300 / TIscale);
	this->addChild(triangle1->getSprite(), 4);

	GameObjectPhysics* triangle2 = new Triangle();
	triangle2->getSprite()->setPosition(-3705 / TIscale, -300 / TIscale);
	this->addChild(triangle2->getSprite(), 4);

	GameObjectPhysics* triangle3 = new Triangle();
	triangle3->getSprite()->setPosition(-3905 / TIscale, 1200 / TIscale);
	this->addChild(triangle3->getSprite(), 4);

	GameObjectPhysics* triangle4 = new Triangle();
	triangle4->getSprite()->setPosition(-905 / TIscale, 200 / TIscale);
	this->addChild(triangle4->getSprite(), 4);
};

//TURRET BODY FUNCTION - SAMUEL MACSWEENEY
void SecondWorld::turretBody()
{
	//TURRET BODY - SAMUEL
	TurretBody* tb1 = new TurretBody();
	tb1->getSprite()->setPosition(-3200 / TIscale, 1400 / TIscale);
	this->addChild(tb1->getSprite(), 2);

	TurretBody* tb2 = new TurretBody();
	tb2->getSprite()->setPosition(1600 / TIscale, 300 / TIscale);
	this->addChild(tb2->getSprite(), 2);

	TurretBody* tb3 = new TurretBody();
	tb3->getSprite()->setPosition(2200 / TIscale, -1800 / TIscale);
	this->addChild(tb3->getSprite(), 2);
};

//TURRET HEAD FUNCTION - SAMUEL MACSWEENEY
void SecondWorld::turretHead()
{
	//TURRET HEAD - SAMUEL

	//TURRET HEAD OBJECTS
	TurretHead* th1 = new TurretHead();
	th1->getSprite()->setPosition(-3150 / TIscale, 1400 / TIscale);
	th1->turretmove();
	this->addChild(th1->getSprite(), 3);

	TurretHead* th2 = new TurretHead();
	th2->getSprite()->setPosition(1650 / TIscale, 300 / TIscale);
	th2->turretmove();
	this->addChild(th2->getSprite(), 3);


	TurretHead* th3 = new TurretHead();
	th3->getSprite()->setPosition(2250 / TIscale, -1800 / TIscale);
	th3->turretmove();
	this->addChild(th3->getSprite(), 3);

};

//TURRET FIRE FUNCTION - SAMUEL MACSWEENEY
void SecondWorld::turretFire()
{
	//CREATING A SCHEDULE THAT WILL CALL THE SHOOT FUNCTION AND MAKE THE TURRETS FIRE
	//FIRERATE IS HOW MANY BULLETS PER SECOND
	this->schedule(schedule_selector(SecondWorld::turretShoot), fireRate);
};

//TURRET SHOOT FUNCTION - SAMUEL MACSWEENEY
void SecondWorld::turretShoot(float delta)
{

	//CREATING BULLET OBJECTS ADDING PHYSICS BODIES AND ACTIONS

	//ADDING SPRITE
	Sprite* turret_bullet = Sprite::create("Turret/turretammo.png");
	turret_bullet->setPosition(-3150 / TIscale, 1400 / TIscale);
	turret_bullet->setScale(0.1);
	this->addChild(turret_bullet);

	//ADDING PHYSICS
	PhysicsBody* turret_bullet_physics = PhysicsBody::createCircle(turret_bullet->getContentSize().width / 2, PhysicsMaterial(0, 0, 0));
	turret_bullet_physics->setContactTestBitmask(true);
	turret_bullet_physics->setDynamic(false);
	turret_bullet_physics->setCollisionBitmask(11);
	turret_bullet->setPhysicsBody(turret_bullet_physics);

	//ADDING ACTIONS
	auto moveTo = MoveTo::create(10, Vec2(-3250 / TIscale, 800 / TIscale));
	auto seq1 = cocos2d::Sequence::create(moveTo, NULL);

	//CREATES AN ACTION THAT WILL RUN FOREVER
	turret_bullet->runAction(RepeatForever::create(cocos2d::Sequence::create(seq1, NULL)));

	//DUPLICATE BULLET OBJECTS TO ADD BULLETS TO OTHER CANNONS

	/*
	DUPLICATES MUST BE USED IN ORDER TO PREVENT ERRORS AND BROKEN CODE AND SEQUECEING PROBLEMS AND
	CODE NOT RUNNING FOR UNKNOWN REASONS
	*/

	Sprite* turret_bullet2 = Sprite::create("Turret/turretammo.png");
	turret_bullet2->setPosition(1650 / TIscale, 300 / TIscale);
	turret_bullet2->setScale(0.1);
	this->addChild(turret_bullet2);

	PhysicsBody* turret_bullet_physics2 = PhysicsBody::createCircle(turret_bullet2->getContentSize().width / 2, PhysicsMaterial(0, 0, 0));
	turret_bullet_physics2->setContactTestBitmask(true);
	turret_bullet_physics2->setDynamic(false);
	turret_bullet_physics2->setCollisionBitmask(11);
	turret_bullet2->setPhysicsBody(turret_bullet_physics2);

	auto moveTo2 = MoveTo::create(10, Vec2(1500 / TIscale, -300 / TIscale));
	auto seq3 = cocos2d::Sequence::create(moveTo2, NULL);
	turret_bullet2->runAction(RepeatForever::create(cocos2d::Sequence::create(seq3, NULL)));

	Sprite* turret_bullet3 = Sprite::create("Turret/turretammo.png");
	turret_bullet3->setPosition(2250 / TIscale, -1800 / TIscale);
	turret_bullet3->setScale(0.1);
	this->addChild(turret_bullet3);

	PhysicsBody* turret_bullet_physics3 = PhysicsBody::createCircle(turret_bullet3->getContentSize().width / 2, PhysicsMaterial(0, 0, 0));
	turret_bullet_physics3->setContactTestBitmask(true);
	turret_bullet_physics3->setDynamic(false);
	turret_bullet_physics3->setCollisionBitmask(11);
	turret_bullet3->setPhysicsBody(turret_bullet_physics3);

	auto moveTo3 = MoveTo::create(10, Vec2(2200 / TIscale, -1100 / TIscale));
	auto seq4 = cocos2d::Sequence::create(moveTo3, NULL);
	turret_bullet3->runAction(RepeatForever::create(cocos2d::Sequence::create(seq4, NULL)));
};

//HUD LAYER FUNCTION - SAMUEL & SAMANTHA
void SecondWorld::hudLayer()
{

	//HUD LAYER - SAMUEL & SAMANTHA
	HUD = LayerGradient::create(Color4B(0, 0, 0, 0), Color4B(0, 0, 0, 0));
	HUD->setContentSize(visibleSize);

	this->addChild(HUD, 4);

	//WEAPON AVAILABLE - DANIEL
	weaponLabel = Label::createWithTTF("", "fonts/Marker Felt.ttf", 20);
	HUD->addChild(weaponLabel);
	weaponLabel->setPosition(Vec2(30, visibleSize.height - 250));
	weaponLabel->setAnchorPoint(cocos2d::Vec2(0, 0));

	//HUD LAYER TEMPLATE - SAMUEL & SAMANTHA
	hudTemplatesprite = Sprite::create("HUD/hudtemplate.png");
	hudTemplatesprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	hudTemplatesprite->setScale(1.27);

	HUD->addChild(hudTemplatesprite, 5);

	//LAP NUMBER SAMUEL & SAMANTHA
	lapNumber = Label::createWithTTF("LAP NUMBER: ", "fonts/Marker Felt.ttf", 20);
	lapNumber->setPosition(Vec2(-300, visibleSize.height + 350));
	lapNumber->setAnchorPoint(Vec2(0, 0));
	lapNumber->setString("LAP NUMBER: " + std::to_string(lapCounter) + "/10");

	HUD->addChild(lapNumber, 6);

	//TIMER - SAMUEL
	timer = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 30);
	timer->setPosition(Vec2(-50, visibleSize.height + 350));
	timer->setAnchorPoint(Vec2(0, 0));

	HUD->addChild(timer, 6);

	//HEALTH BAR - SAMANTHA
	backgroundBarSprite1 = Sprite::create("Bars/backgroundbar.png");
	backgroundBarSprite1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 305));

	HUD->addChild(backgroundBarSprite1, 6);

	this->damageTimer1 = cocos2d::ProgressTimer::create(damageBarSprite1 = Sprite::create("Bars/damagebar.png"));
	this->damageTimer1->setGlobalZOrder(1);
	this->damageTimer1->setType(ProgressTimerType::BAR);
	this->damageTimer1->setBarChangeRate(Vec2(1, 0));
	this->damageTimer1->setAnchorPoint(Vec2(0, 0));
	this->damageTimer1->setPosition(Vec2(visibleSize.width / 2 - 145, visibleSize.height - 315));
	this->damageTimer1->setVisible(true);
	this->damageTimer1->setPercentage(100);
	this->damageTimer1->setMidpoint(Vec2(0, 0));
	HUD->addChild(this->damageTimer1, 7);

	this->healthTimer = cocos2d::ProgressTimer::create(healthBarSprite = Sprite::create("Bars/healthbar.png"));
	this->healthTimer->setGlobalZOrder(2);
	this->healthTimer->setType(ProgressTimerType::BAR);
	this->healthTimer->setBarChangeRate(Vec2(1, 0));
	this->healthTimer->setAnchorPoint(Vec2(0, 0));
	this->healthTimer->setPosition(Vec2(visibleSize.width / 2 - 145, visibleSize.height - 315));
	this->healthTimer->setVisible(true);
	this->healthTimer->setPercentage(100);
	this->healthTimer->setMidpoint(Vec2(0, 0));
	HUD->addChild(this->healthTimer, 8);

	//THRUSTER BAR - SAMANTHA
	backgroundBarSprite2 = Sprite::create("Bars/backgroundbar.png");
	backgroundBarSprite2->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 365));

	HUD->addChild(backgroundBarSprite2, 6);

	this->damageTimer2 = cocos2d::ProgressTimer::create(damageBarSprite2 = Sprite::create("Bars/damagebar.png"));
	this->damageTimer2->setGlobalZOrder(1);
	this->damageTimer2->setType(ProgressTimerType::BAR);
	this->damageTimer2->setBarChangeRate(Vec2(1, 0));
	this->damageTimer2->setAnchorPoint(Vec2(0, 0));
	this->damageTimer2->setPosition(Vec2(visibleSize.width / 2 - 145, visibleSize.height - 375));
	this->damageTimer2->setVisible(true);
	this->damageTimer2->setPercentage(100);
	this->damageTimer2->setMidpoint(Vec2(0, 0));
	HUD->addChild(this->damageTimer2, 7);

	this->thrusterTimer = cocos2d::ProgressTimer::create(thrusterBarSprite = Sprite::create("Bars/thrusterbar.png"));
	this->thrusterTimer->setGlobalZOrder(2);
	this->thrusterTimer->setType(ProgressTimerType::BAR);
	this->thrusterTimer->setBarChangeRate(Vec2(1, 0));
	this->thrusterTimer->setAnchorPoint(Vec2(0, 0));
	this->thrusterTimer->setPosition(Vec2(visibleSize.width / 2 - 145, visibleSize.height - 375));
	this->thrusterTimer->setVisible(true);
	this->thrusterTimer->setPercentage(100);
	this->thrusterTimer->setMidpoint(Vec2(0, 0));
	HUD->addChild(this->thrusterTimer, 8);

	this->speedTimer = cocos2d::ProgressTimer::create(speedIndicator = Sprite::create("SpeedIndicator/speedindicator.png"));
	this->speedTimer->setGlobalZOrder(1);
	this->speedTimer->setType(ProgressTimerType::BAR);
	this->speedTimer->setBarChangeRate(Vec2(1, 0));
	this->speedTimer->setAnchorPoint(Vec2(0, 0));
	this->speedTimer->setPosition(Vec2(visibleSize.width / 2 + 300, visibleSize.height - 375));
	this->speedTimer->setVisible(true);
	this->speedTimer->setPercentage(100);
	this->speedTimer->setMidpoint(Vec2(0, 0));

	HUD->addChild(speedTimer, 6);
};

//END RACE FUNCTION - SAMANTHA
void SecondWorld::endRace()
{
	if (lapCounter >= 11)
	{
		auto EndingCreditsScene = EndingCredits::createScene();
		Director::getInstance()->replaceScene(EndingCreditsScene);
	}
}

//DIRECTOR & SCREEN ORIGIN CENTER POINT
void SecondWorld::director()
{
	//DIRECTOR RESOLUTION - VISIBLSIZE CAN BE USED THROUGH OUT CLASS TO GET SCREEN WIDTH AND HEIGHT - DANIEL
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();//GETS CENTER OF DISPLAY
}