#include "FirstWorld.h"


USING_NS_CC;

//BITMASK///////////////////////////
//Track Walls = Bitmask 1 Done
//Finish Line Detector = Bitmask 2 Done
//Finish Line Pre-Detector = Bitmask 3 Done
//Player Ship = Bitmask 4 Done
//Circle Circuit = Bitmask 5 Done
//Square Circuit = Bitmask 5 Done
//Thruster Pickup = Bitmask 6 Done
//Health Pickup = Bitmask 7 Done
//Weapon/Shield Pickup = Bitmask 8 Done
//Z Ordering Global/////////////////
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
//LAYER - HUD	: 1

//CREATE SCENES AND LAYERS SAMUEL - PHYSCIS DEBUG OPTIONS- DANIEL
cocos2d::Scene* FirstWorld::createScene()
{
	auto FirstWorldScene = Scene::createWithPhysics();
	//FirstWorldScene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	FirstWorldScene->getPhysicsWorld()->setGravity(Vec2(0, 0));

	auto layer = FirstWorld::create();
	layer->SetPhysicsWorld(FirstWorldScene->getPhysicsWorld());
	FirstWorldScene->addChild(layer, 0);

	return FirstWorldScene;
};

//CONSTRUCTOR & DE-CONSTRUCTOR
FirstWorld::FirstWorld() :
TIscale(1.7068),//1.7068;//PHYSCIS SCALE ISSUE VARIABLE - DIVIDE ALL PHYSICS POINTS BY THIS VALUE TO FIX ISSUE - DANIEL
time(0),
weaponTimer(11),
activeWeaponTimer(false),
enemyOneWayPointSkill(2)//DEFAULT MEDIUM SKILL CORNER TAKING
{
};
FirstWorld::~FirstWorld()
{
};

//INITILIZING FUCNTION FOR OUR GAME - DANIEL
bool FirstWorld::init()
{
	//IF LAYER INIT FAILED WE EXIT GAME - RUNTIME ERROR CHECK - DANIEL
	if (!Layer::init())return false;

	//COCOS2D-X DIRECTOR SET UP - WINDOW ORIGIN
	director();

	//HUD SET UP
	hud();

	//RACING TRACK ONE PHYSICS AND BOUNDARIES _ DANIEL
	addTrack();

	//POINTS ON THE TRACK FOR THE AI TO FOLLOW - BASIC LEVEL EXAMPLE - SAMUEL
	AIWayPoints();

	//TRACK DIRECTIONAL CONTROL - DANIEL
	trackWayPoints();

	//VEHICLE OBEJCTS CONSTRUCTION - DANIEL
	vehicleObjects();

	//OBSTACLES AND TRACK OBJECTS - SAMUEL
	obstacles();

	//ACTIVATE LISTENERS
	eventListeners();

	//LABELS SET UP
	labels();
	
	//SCHEDULE UPDATE FUNCTIONALITY - UPDATES EVERY DELTA (RESEARCH DELTA - EFFICENT UPDATING) - DANIEL
	this->scheduleUpdate();

	//RETURN TRUE AND FINISH INIT CALL - ACTION LISTENER AND EVENT LISTENER WILL CONTIUE TO RUN
	return true;
};

//CALL BACK FOR WHEN ITEM IS CLOSED - DANIEL
void FirstWorld::menuCloseCallback(Ref* pSender)
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
		MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
		return;
	#endif

		Director::getInstance()->end();

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
	#endif
};

//ON TOUCH SCREEN BEGIN - DANIEL
bool FirstWorld::onTouchBegan(Touch* touch, Event* event)
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

	auto sprite = Sprite::create("TrackOne/WayPoint.png");
	sprite->setPosition(cocos2d::Vec2(x, y));
	this->addChild(sprite);
	CCLOG("X %f Y %f", x*TIscale, y*TIscale);

	return true;
};

//ON TOUCH SCREEN ENDED - DANIEL
void FirstWorld::onTouchEnded(Touch* touch, Event* event)
{
	CCLOG("Touch Ended");
};

//HOLD AND TOUCH - NOT BEEN USED YET - DANIEL
void FirstWorld::onTouchMoved(Touch* touch, Event* event)
{

};

//WHEN TOUCH IS CANCELED - NOT BEEN USED YET - DANIEL
void FirstWorld::onTouchCancelled(Touch* touch, Event* event)
{
	
	
};

//WHEN TWO PHYSICS OBJECTS COLLIDE FUCNTION - DANIEL
bool FirstWorld::onContactBegin(cocos2d::PhysicsContact &contact)
{
	PhysicsBody *contactA = contact.getShapeA()->getBody();
	PhysicsBody *contactB = contact.getShapeB()->getBody();

	//CHECK WALL AND VEHICLE COLLISION
	if (contactA->getCollisionBitmask() == 1 && contactB->getCollisionBitmask() == 2)
	{
		if (contactA == playerVehicleObject->getPhysicsBody()) { playerVehicleObject->setSpeed(120); }
		return true;
	}
	else if (contactA->getCollisionBitmask() == 2 && contactB->getCollisionBitmask() == 1)
	{
		if (contactB == playerVehicleObject->getPhysicsBody()) { playerVehicleObject->setSpeed(120); }
		return true;
	}

	if (contactA->getCollisionBitmask() == 2 && contactB->getCollisionBitmask() == 3)
	{
		this->removeChild(contactB->getNode(), true);
		return true;
	}
	else if (contactA->getCollisionBitmask() == 3 && contactB->getCollisionBitmask() == 2)
	{
		this->removeChild(contactA->getNode(), true);
		return true;
	}

	return true;
};

//IS THE KEY STILL BEEN PRESSED - TIMER - HOLD DOWN - DANIEL
bool FirstWorld::isKeyPressed(EventKeyboard::KeyCode code)
{
	if (keys.find(code) != keys.end())
	{
		return true;
	}

	return false;
};

//DURATION KEY IS BEEN PRESSED - TIMER - DANIEL
double FirstWorld::keyPressedDuration(EventKeyboard::KeyCode code)
{
	if (!isKeyPressed(EventKeyboard::KeyCode::KEY_CTRL))
	{
		return 0;
	}

	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - keys[code]).count();
};

//UPDATE FUCNTION - CALLED EVERY DELTA - DANIEL
void FirstWorld::update(float delta)
{
	//----------------------------------------------------------------
	//PROJECTILES COLLISION - EXPLOSION ON COLLISION -  REDUCE HEALTH OF VEHICLES - DESTROY VEHICLE/OBJECTS
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
				if (rect1.intersectsRect(rect2))
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
			__String *timeToDisplay = __String::createWithFormat("%.2f", time);
			timer->setString(std::to_string(weaponTimer));
			CCLOG("WEAPON TIMER : %f.0f", weaponTimer);
		}
		else if (weaponTimer >= 10)
		{
			playerVehicleObject->endWeapon();
			timer->setString("NO WEAPON");
			activeWeaponTimer = false;
		}
	}
	weaponLabel->setString(playerVehicleObject->getWeapon());
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	//HUD UPDATING - SPEED - BACKWARDS NOTIFICATION
	HUD->setPosition(playerVehicleObject->getSprite()->getPosition().x - visibleSize.width / 2, playerVehicleObject->getSprite()->getPosition().y - visibleSize.height / 2);
	speed->setString(std::to_string(int(playerVehicleObject->getSpeed())));
	if (playerVehicleObject->getSlowDownStatus())
	{
		slowDownStatus->setString("SLOW DOWN : TRUE");
	}
	else
	{
		slowDownStatus->setString("SLOW DOWN : FALSE");
	}
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	//SLOW ALL OBSTACLES DOWN - VELOCITY DAMPING - DANIEL
	for (auto object : this->objects)
	{
		if ((object->getPhysicsBody()->getVelocity().x < 1 || object->getPhysicsBody()->getVelocity().x > -1) && (object->getPhysicsBody()->getVelocity().y < 1 || object->getPhysicsBody()->getVelocity().y > -1))
			object->getPhysicsBody()->setVelocity(cocos2d::Vec2(object->getPhysicsBody()->getVelocity().x / 2, object->getPhysicsBody()->getVelocity().y / 2));
	}
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	//BACKWARDS CHECKING - NOTIFY PLAYER THEY ARE GOING BACKWARDS - DANIEL
	if (!directionalWayPoints.empty())//CHECK FOR VEHICLE INTERSECTING WAY POINTS - MARK WAY POINT CROSSED - ADD WAY POINT NUMBER TO VECTOR FOR ORDER CHECKING IN NEXT SECTION 
	{
		for (auto directionalWayPoint : this->directionalWayPoints)
		{
			Rect rect1 = playerVehicleObject->getSprite()->getBoundingBox();
			Rect rect2 = directionalWayPoint->getSprite()->getBoundingBox();
			if (rect1.intersectsRect(rect2))
			{
				if (!directionalWayPoint->getActive())
				{
					directionalWayPoint->setActive(true);
					directionalTriggers.push_back(directionalWayPoint->getID());
					CCLOG("Intersection IN");
				}
			}
			else
			{
				directionalWayPoint->setActive(false);
			}
		}
	}
	if (directionalTriggers.size() > 1)//WE MAKE SURE OUR VECTOR ONLY HAS THREE ITEMS - MAKE SURE ITEMS ARE IN CORRECT ORDER FROM LOW TO HIGH, ELSE WE ARE GOING BACKWARDS
	{
		if (directionalTriggers.size() > 3) { directionalTriggers.erase(directionalTriggers.begin());}//KEEP IT AT THREE MAX

		int low = 0;

		for (auto directionalTrigger : this->directionalTriggers)
		{
			if (low == 0) { low = directionalTrigger; }
			
			if (low == 44 && directionalTrigger == 1)
			{
					low = directionalTrigger;
					backwardsLabel->setString("");
			}
			else
			{
				if (low > directionalTrigger)
				{
					backwards = true;
					backwardsLabel->setString("Wrong Way !");
				}
				else
				{
					low = directionalTrigger;
					backwardsLabel->setString(" ");
				}
			}

		}
	}
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	//BACKWARDS CHECKING - NOTIFY PLAYER THEY ARE GOING BACKWARDS - SAMANTHA
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
	angle->setString(std::to_string(playerVehicleObject->getAngle()));
	//PLAYER VEHICLE CALCULATION - DANIEL
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	//ENEMY ONE VEHICLE CALCULATION - - VELOCITY - DRIVE - DANIEL
	for (auto vehicle : this->vehicles)
	{
		if (vehicle->getType() == "enemy" )
		{
			enemyOneVehicleObject->autoControlAI(enemyOneCurrentWayPoint);
			if (enemyOneVehicleObject->getActiveStatus())
			{
				enemyOneVehicleObject->setVelocityPoint();
				enemyOneVehicleObject->setVelocity();
				if (enemyOneVehicleObject->wayPointCollision(wayPointSprite))
				{
					WayPoint[wayPointCounter] = false;

					if (wayPointCounter == 61)//CHECK IF AT END OF WAY POINTS AND RESET BACK TO ONE SO WE CAN DO MORE LAPS
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
			}
			//CHECK IF ENEMY ONE IS COLLIDING WITH CURRENT WAY POINT
		}

	}
	//ENEMY ONE VEHICLE CALCULATION - DANIEL
	//----------------------------------------------------------------
};

//TRACK POINTS FOR TRACK SPRITE AND PHYSICS BOUNDARIES - DANIEL
void FirstWorld::addTrack()
{
	//INSIDE TRACK BOUNDARY
	trackInSprite = Sprite::create("TrackOne/trackoneinnerrim.png");
	trackInArray[0] = Point(-2400 / TIscale, 1000 / TIscale);
	trackInArray[1] = Point(-2300 / TIscale, 1100 / TIscale);
	trackInArray[2] = Point(-1200 / TIscale, 1100 / TIscale);
	trackInArray[3] = Point(-1100 / TIscale, 1000 / TIscale);
	trackInArray[4] = Point(-1100 / TIscale, 800 / TIscale);
	trackInArray[5] = Point(-1200 / TIscale, 700 / TIscale);
	trackInArray[6] = Point(-1300 / TIscale, 700 / TIscale);
	trackInArray[7] = Point(-1500 / TIscale, 900 / TIscale);
	trackInArray[8] = Point(-1800 / TIscale, 900 / TIscale);
	trackInArray[9] = Point(-2000 / TIscale, 700 / TIscale);
	trackInArray[10] = Point(-2000 / TIscale, -400 / TIscale);
	trackInArray[11] = Point(-2300 / TIscale, -700 / TIscale);
	trackInArray[12] = Point(-2300 / TIscale, -900 / TIscale);
	trackInArray[13] = Point(-2100 / TIscale, -1100 / TIscale);
	trackInArray[14] = Point(-200 / TIscale, -1100 / TIscale);
	trackInArray[15] = Point(100 / TIscale, -800 / TIscale);
	trackInArray[16] = Point(100 / TIscale, -600 / TIscale);
	trackInArray[17] = Point(-300 / TIscale, -200 / TIscale);
	trackInArray[18] = Point(-900 / TIscale, -200 / TIscale);
	trackInArray[19] = Point(-1100 / TIscale, -400 / TIscale);
	trackInArray[20] = Point(-1100 / TIscale, -500 / TIscale);
	trackInArray[21] = Point(-1200 / TIscale, -600 / TIscale);
	trackInArray[22] = Point(-1300 / TIscale, -600 / TIscale);
	trackInArray[23] = Point(-1500 / TIscale, -400 / TIscale);
	trackInArray[24] = Point(-1500 / TIscale, -100 / TIscale);
	trackInArray[25] = Point(-1400 / TIscale, 0 / TIscale);
	trackInArray[26] = Point(-400 / TIscale, 0 / TIscale);
	trackInArray[27] = Point(0 / TIscale, 400 / TIscale);
	trackInArray[28] = Point(0 / TIscale, 1100 / TIscale);
	trackInArray[29] = Point(100 / TIscale, 1200 / TIscale);
	trackInArray[30] = Point(700 / TIscale, 1200 / TIscale);
	trackInArray[31] = Point(800 / TIscale, 1100 / TIscale);
	trackInArray[32] = Point(800 / TIscale, 1000 / TIscale);
	trackInArray[33] = Point(700 / TIscale, 900 / TIscale);
	trackInArray[34] = Point(200 / TIscale, 900 / TIscale);
	trackInArray[35] = Point(100 / TIscale, 800 / TIscale);
	trackInArray[36] = Point(100 / TIscale, 200 / TIscale);
	trackInArray[37] = Point(-100 / TIscale, 0 / TIscale);
	trackInArray[38] = Point(-100 / TIscale, -100 / TIscale);
	trackInArray[39] = Point(200 / TIscale, -400 / TIscale);
	trackInArray[40] = Point(200 / TIscale, -900 / TIscale);
	trackInArray[41] = Point(500 / TIscale, -1200 / TIscale);
	trackInArray[42] = Point(1300 / TIscale, -1200 / TIscale);
	trackInArray[43] = Point(1900 / TIscale, -600 / TIscale);
	trackInArray[44] = Point(1900 / TIscale, 700 / TIscale);
	trackInArray[45] = Point(2100 / TIscale, 900 / TIscale);
	trackInArray[46] = Point(2300 / TIscale, 900 / TIscale);
	trackInArray[47] = Point(2500 / TIscale, 700 / TIscale);
	trackInArray[48] = Point(2500 / TIscale, 300 / TIscale);
	trackInArray[49] = Point(2000 / TIscale, -200 / TIscale);
	trackInArray[50] = Point(2000 / TIscale, -600 / TIscale);
	trackInArray[51] = Point(2300 / TIscale, -900 / TIscale);
	trackInArray[52] = Point(2300 / TIscale, -1100 / TIscale);
	trackInArray[53] = Point(2100 / TIscale, -1300 / TIscale);
	trackInArray[54] = Point(-2400 / TIscale, -1300 / TIscale);
	trackInArray[55] = Point(-2500 / TIscale, -1200 / TIscale);
	trackInArray[56] = Point(-2500 / TIscale, -1100 / TIscale);
	trackInArray[57] = Point(-2400 / TIscale, -1000 / TIscale);
	trackInArray[58] = Point(-2400 / TIscale, -700 / TIscale);
	trackInArray[59] = Point(-2100 / TIscale, -400 / TIscale);
	trackInArray[60] = Point(-2100 / TIscale, 400 / TIscale);
	trackInArray[61] = Point(-2400 / TIscale, 700 / TIscale);
	trackInArray[62] = Point(-2400 / TIscale, 1000 / TIscale);
	trackInPhysics = PhysicsBody::createEdgePolygon(trackInArray, 63, PhysicsMaterial(1, 1, 1), 10);
	trackInPhysics->setCollisionBitmask(2);
	trackInPhysics->setContactTestBitmask(true);
	trackInSprite->setPhysicsBody(trackInPhysics);
	//trackInSprite->setScale(1);
	this->addChild(trackInSprite, 6);

	//OUTSIDE TRACK BOUNDARY
	trackOutSprite = Sprite::create("TrackOne/trackoneouterrim.png");
	trackOutArray[0] = Point(-2900 / TIscale, 1000 / TIscale);
	trackOutArray[1] = Point(-2500 / TIscale, 1400 / TIscale);
	trackOutArray[2] = Point(-800 / TIscale, 1400 / TIscale);
	trackOutArray[3] = Point(-500 / TIscale, 1100 / TIscale);
	trackOutArray[4] = Point(-500 / TIscale, 700 / TIscale);
	trackOutArray[5] = Point(-800 / TIscale, 400 / TIscale);
	trackOutArray[6] = Point(-1400 / TIscale, 400 / TIscale);
	trackOutArray[7] = Point(-1600 / TIscale, 600 / TIscale);
	trackOutArray[8] = Point(-1700 / TIscale, 600 / TIscale);
	trackOutArray[9] = Point(-1800 / TIscale, 500 / TIscale);
	trackOutArray[10] = Point(-1800 / TIscale, -500 / TIscale);
	trackOutArray[11] = Point(-2000 / TIscale, -700 / TIscale);
	trackOutArray[12] = Point(-2000 / TIscale, -800 / TIscale);
	trackOutArray[13] = Point(-1900 / TIscale, -900 / TIscale);
	trackOutArray[14] = Point(-500 / TIscale, -900 / TIscale);
	trackOutArray[15] = Point(-400 / TIscale, -800 / TIscale);
	trackOutArray[16] = Point(-400 / TIscale, -600 / TIscale);
	trackOutArray[17] = Point(-500 / TIscale, -500 / TIscale);
	trackOutArray[18] = Point(-800 / TIscale, -500 / TIscale);
	trackOutArray[19] = Point(-900 / TIscale, -600 / TIscale);
	trackOutArray[20] = Point(-900 / TIscale, -700 / TIscale);
	trackOutArray[21] = Point(-1000 / TIscale, -800 / TIscale);
	trackOutArray[22] = Point(-1500 / TIscale, -800 / TIscale);
	trackOutArray[23] = Point(-1700 / TIscale, -600 / TIscale);
	trackOutArray[24] = Point(-1700 / TIscale, 100 / TIscale);
	trackOutArray[25] = Point(-1500 / TIscale, 300 / TIscale);
	trackOutArray[26] = Point(-700 / TIscale, 300 / TIscale);
	trackOutArray[27] = Point(-300 / TIscale, 700 / TIscale);
	trackOutArray[28] = Point(-300 / TIscale, 1300 / TIscale);
	trackOutArray[29] = Point(-200 / TIscale, 1400 / TIscale);
	trackOutArray[30] = Point(900 / TIscale, 1400 / TIscale);
	trackOutArray[31] = Point(1100 / TIscale, 1200 / TIscale);
	trackOutArray[32] = Point(1100 / TIscale, 700 / TIscale);
	trackOutArray[33] = Point(1000 / TIscale, 600 / TIscale);
	trackOutArray[34] = Point(500 / TIscale, 600 / TIscale);
	trackOutArray[35] = Point(400 / TIscale, 500 / TIscale);
	trackOutArray[36] = Point(400 / TIscale, 100 / TIscale);
	trackOutArray[37] = Point(300 / TIscale, 0 / TIscale);
	trackOutArray[38] = Point(300 / TIscale, -100 / TIscale);
	trackOutArray[39] = Point(500 / TIscale, -300 / TIscale);
	trackOutArray[40] = Point(500 / TIscale, -600 / TIscale);
	trackOutArray[41] = Point(800 / TIscale, -900 / TIscale);
	trackOutArray[42] = Point(1000 / TIscale, -900 / TIscale);
	trackOutArray[43] = Point(1600 / TIscale, -300 / TIscale);
	trackOutArray[44] = Point(1600 / TIscale, 1000 / TIscale);
	trackOutArray[45] = Point(1900 / TIscale, 1300 / TIscale);
	trackOutArray[46] = Point(2500 / TIscale, 1300 / TIscale);
	trackOutArray[47] = Point(2800 / TIscale, 1000 / TIscale);
	trackOutArray[48] = Point(2800 / TIscale, 0 / TIscale);
	trackOutArray[49] = Point(2400 / TIscale, -400 / TIscale);
	trackOutArray[50] = Point(2400 / TIscale, -500 / TIscale);
	trackOutArray[51] = Point(2800 / TIscale, -900 / TIscale);
	trackOutArray[52] = Point(2800 / TIscale, -1100 / TIscale);
	trackOutArray[53] = Point(2500 / TIscale, -1500 / TIscale);
	trackOutArray[54] = Point(-2600 / TIscale, -1500 / TIscale);
	trackOutArray[55] = Point(-2800 / TIscale, -1300 / TIscale);
	trackOutArray[56] = Point(-2800 / TIscale, -1100 / TIscale);
	trackOutArray[57] = Point(-2900 / TIscale, -1000 / TIscale);
	trackOutArray[58] = Point(-2900 / TIscale, 1000 / TIscale);
	trackOutPhysics = PhysicsBody::createEdgePolygon(trackOutArray, 59, PhysicsMaterial(1, 1, 1), 10);
	trackOutPhysics->setCollisionBitmask(2);
	trackOutPhysics->setContactTestBitmask(true);
	trackOutSprite->setPhysicsBody(trackOutPhysics);
	//trackOutSprite->setScale(1);
	this->addChild(trackOutSprite, 6);

	//OUTSIDE TRACK BOUNDARY
	trackInLetSprite = Sprite::create("TrackOne/trackinlet.png");
	trackInLetArray[0] = Point(-50 / TIscale, -400 / TIscale);
	trackInLetArray[1] = Point(-50 / TIscale, 400 / TIscale);
	trackInLetArray[2] = Point(50 / TIscale, 300 / TIscale);
	trackInLetArray[3] = Point(50 / TIscale, -300 / TIscale);
	trackInLetArray[4] = Point(-50 / TIscale, -400 / TIscale);
	trackInLetPhyscis = PhysicsBody::createEdgePolygon(trackInLetArray, 5, PhysicsMaterial(1, 1, 1), 10);
	trackInLetPhyscis->setCollisionBitmask(2);
	trackInLetPhyscis->setContactTestBitmask(true);
	trackInLetSprite->setPhysicsBody(trackInLetPhyscis);
	trackInLetSprite->setPosition(cocos2d::Vec2(-2350 / TIscale, 0 / TIscale));
	//trackOutSprite->setScale(1);
	this->addChild(trackInLetSprite, 6);
}

//AI WAY POINTS FOR AI TO FOLLOW - SAMUEL
void FirstWorld::AIWayPoints()
{
	//WE HAVE THIS EXTRA ARRAY HANDY FOR DIFFERENT USES - WE INITIALIZE THEM ALL FALSE
	for (int i = 0; i < 62; i++)
		WayPoint[i] = false;

	WayPoint[0] = true;//WE KNOW WE START AT FIRST WAY POINT - WHICH WILL HAVE 3 POINTS 

	WayPoints[0][0] = cocos2d::Vec2(-2460 / TIscale, 1000 / TIscale);//ZERO IS MOST TIGHT CORNER
	WayPoints[0][1] = cocos2d::Vec2(-2540 / TIscale, 1000 / TIscale);//ONE IS MIDDLE
	WayPoints[0][2] = cocos2d::Vec2(-2620 / TIscale, 1000 / TIscale);//TWO IS LEAST TIGHT CORNER

	WayPoints[1][0] = cocos2d::Vec2(-2330 / TIscale, 1150 / TIscale);
	WayPoints[1][1] = cocos2d::Vec2(-2370 / TIscale, 1200 / TIscale);//WAY POINT 2
	WayPoints[1][2] = cocos2d::Vec2(-2420 / TIscale, 1250 / TIscale);

	WayPoints[2][0] = cocos2d::Vec2(-1150 / TIscale, 1150 / TIscale);
	WayPoints[2][1] = cocos2d::Vec2(-1100 / TIscale, 1200 / TIscale);//WAY POINT 3
	WayPoints[2][2] = cocos2d::Vec2(-1050 / TIscale, 1250 / TIscale);

	WayPoints[3][0] = cocos2d::Vec2(-1050 / TIscale, 1020 / TIscale);
	WayPoints[3][1] = cocos2d::Vec2(-1000 / TIscale, 1050 / TIscale);//WAY POINT 4
	WayPoints[3][2] = cocos2d::Vec2(-950 / TIscale, 1080 / TIscale);

	WayPoints[4][0] = cocos2d::Vec2(-1050 / TIscale, 780 / TIscale);
	WayPoints[4][1] = cocos2d::Vec2(-1000 / TIscale, 750 / TIscale);//WAY POINT 5
	WayPoints[4][2] = cocos2d::Vec2(-950 / TIscale, 720 / TIscale);

	WayPoints[5][0] = cocos2d::Vec2(-1180 / TIscale, 650 / TIscale);
	WayPoints[5][1] = cocos2d::Vec2(-1155 / TIscale, 590 / TIscale);//WAY POINT 6
	WayPoints[5][2] = cocos2d::Vec2(-1128 / TIscale, 532 / TIscale);

	WayPoints[6][0] = cocos2d::Vec2(-1310 / TIscale, 650 / TIscale);
	WayPoints[6][1] = cocos2d::Vec2(-1330 / TIscale, 600 / TIscale);//WAY POINT 7
	WayPoints[6][2] = cocos2d::Vec2(-1350 / TIscale, 550 / TIscale);

	WayPoints[7][0] = cocos2d::Vec2(-1583 / TIscale, 638 / TIscale);
	WayPoints[7][1] = cocos2d::Vec2(-1559 / TIscale, 687 / TIscale);//WAY POINT 8
	WayPoints[7][2] = cocos2d::Vec2(-1540 / TIscale, 732 / TIscale);

	WayPoints[8][0] = cocos2d::Vec2(-1728 / TIscale, 641 / TIscale);
	WayPoints[8][1] = cocos2d::Vec2(-1758 / TIscale, 697 / TIscale);//WAY POINT 9
	WayPoints[8][2] = cocos2d::Vec2(-1776 / TIscale, 741 / TIscale);

	WayPoints[9][0] = cocos2d::Vec2(-1840 / TIscale, 528 / TIscale);
	WayPoints[9][1] = cocos2d::Vec2(-1884 / TIscale, 564 / TIscale);//WAY POINT 10
	WayPoints[9][2] = cocos2d::Vec2(-1925 / TIscale, 600 / TIscale);

	WayPoints[10][0] = cocos2d::Vec2(-1957 / TIscale, -420 / TIscale);
	WayPoints[10][1] = cocos2d::Vec2(-1924 / TIscale, -431 / TIscale);//WAY POINT 11
	WayPoints[10][2] = cocos2d::Vec2(-1895 / TIscale, -447 / TIscale);

	WayPoints[11][0] = cocos2d::Vec2(-2050 / TIscale, -700 / TIscale);
	WayPoints[11][1] = cocos2d::Vec2(-2100 / TIscale, -700 / TIscale);//WAY POINT 12
	WayPoints[11][2] = cocos2d::Vec2(-2150 / TIscale, -700 / TIscale);

	WayPoints[12][0] = cocos2d::Vec2(-2050 / TIscale, -850 / TIscale);
	WayPoints[12][1] = cocos2d::Vec2(-2100 / TIscale, -850 / TIscale);//WAY POINT 13
	WayPoints[12][2] = cocos2d::Vec2(-2150 / TIscale, -850 / TIscale);

	WayPoints[13][0] = cocos2d::Vec2(-1950 / TIscale, -950 / TIscale);
	WayPoints[13][1] = cocos2d::Vec2(-1985 / TIscale, -980 / TIscale);//WAY POINT 14
	WayPoints[13][2] = cocos2d::Vec2(-2020 / TIscale, -1020 / TIscale);

	WayPoints[14][0] = cocos2d::Vec2(-480 / TIscale, -931 / TIscale);
	WayPoints[14][1] = cocos2d::Vec2(-454 / TIscale, -965 / TIscale);//WAY POINT 15
	WayPoints[14][2] = cocos2d::Vec2(-430 / TIscale, -999 / TIscale);

	WayPoints[15][0] = cocos2d::Vec2(-350 / TIscale, -809 / TIscale);
	WayPoints[15][1] = cocos2d::Vec2(-295 / TIscale, -815 / TIscale);//WAY POINT 16
	WayPoints[15][2] = cocos2d::Vec2(-243 / TIscale, -818 / TIscale);

	WayPoints[16][0] = cocos2d::Vec2(-351 / TIscale, -585 / TIscale);
	WayPoints[16][1] = cocos2d::Vec2(-303 / TIscale, -567 / TIscale);//WAY POINT 17
	WayPoints[16][2] = cocos2d::Vec2(-252 / TIscale, -547 / TIscale);

	WayPoints[17][0] = cocos2d::Vec2(-486 / TIscale, -450 / TIscale);
	WayPoints[17][1] = cocos2d::Vec2(-466 / TIscale, -405 / TIscale);//WAY POINT 18
	WayPoints[17][2] = cocos2d::Vec2(-447 / TIscale, -356 / TIscale);

	WayPoints[18][0] = cocos2d::Vec2(-830 / TIscale, -450 / TIscale);
	WayPoints[18][1] = cocos2d::Vec2(-850 / TIscale, -410 / TIscale);//WAY POINT 19
	WayPoints[18][2] = cocos2d::Vec2(-870 / TIscale, -370 / TIscale);

	WayPoints[19][0] = cocos2d::Vec2(-987 / TIscale, -511 / TIscale);
	WayPoints[19][1] = cocos2d::Vec2(-964 / TIscale, -543 / TIscale);//WAY POINT 20
	WayPoints[19][2] = cocos2d::Vec2(-942 / TIscale, -566 / TIscale);

	WayPoints[20][0] = cocos2d::Vec2(-1030 / TIscale, -560 / TIscale);
	WayPoints[20][1] = cocos2d::Vec2(-1020 / TIscale, -580 / TIscale);//WAY POINT 21
	WayPoints[20][2] = cocos2d::Vec2(-1010 / TIscale, -600 / TIscale);

	WayPoints[21][0] = cocos2d::Vec2(-1188 / TIscale, -627 / TIscale);
	WayPoints[21][1] = cocos2d::Vec2(-1174 / TIscale, -653 / TIscale);//WAY POINT 22
	WayPoints[21][2] = cocos2d::Vec2(-1160 / TIscale, -683 / TIscale);

	WayPoints[22][0] = cocos2d::Vec2(-1323 / TIscale, -631 / TIscale);
	WayPoints[22][1] = cocos2d::Vec2(-1342 / TIscale, -661 / TIscale);//WAY POINT 23
	WayPoints[22][2] = cocos2d::Vec2(-1357 / TIscale, -686 / TIscale);

	WayPoints[23][0] = cocos2d::Vec2(-1540 / TIscale, -440 / TIscale);
	WayPoints[23][1] = cocos2d::Vec2(-1580 / TIscale, -460 / TIscale);//WAY POINT 24
	WayPoints[23][2] = cocos2d::Vec2(-1619 / TIscale, -485 / TIscale);

	WayPoints[24][0] = cocos2d::Vec2(-1540 / TIscale, -70 / TIscale);
	WayPoints[24][1] = cocos2d::Vec2(-1570 / TIscale, -35 / TIscale);//WAY POINT 25
	WayPoints[24][2] = cocos2d::Vec2(-1600 / TIscale, 10 / TIscale);

	WayPoints[25][0] = cocos2d::Vec2(-1420 / TIscale, 50 / TIscale);
	WayPoints[25][1] = cocos2d::Vec2(-1440 / TIscale, 85 / TIscale);//WAY POINT 26
	WayPoints[25][2] = cocos2d::Vec2(-1460 / TIscale, 120 / TIscale);

	WayPoints[26][0] = cocos2d::Vec2(-660 / TIscale, 260 / TIscale);
	WayPoints[26][1] = cocos2d::Vec2(-610 / TIscale, 220 / TIscale);//WAY POINT 27
	WayPoints[26][2] = cocos2d::Vec2(-570 / TIscale, 180 / TIscale);

	WayPoints[27][0] = cocos2d::Vec2(-270 / TIscale, 660 / TIscale);
	WayPoints[27][1] = cocos2d::Vec2(-230 / TIscale, 620 / TIscale);//WAY POINT 28
	WayPoints[27][2] = cocos2d::Vec2(-190 / TIscale, 580 / TIscale);

	WayPoints[28][0] = cocos2d::Vec2(-30 / TIscale, 1120 / TIscale);
	WayPoints[28][1] = cocos2d::Vec2(-80 / TIscale, 1155 / TIscale);//WAY POINT 29
	WayPoints[28][2] = cocos2d::Vec2(-135 / TIscale, 1190 / TIscale);

	WayPoints[29][0] = cocos2d::Vec2(80 / TIscale, 1230 / TIscale);
	WayPoints[29][1] = cocos2d::Vec2(60 / TIscale, 1255 / TIscale);//WAY POINT 30
	WayPoints[29][2] = cocos2d::Vec2(30 / TIscale, 1290 / TIscale);

	WayPoints[30][0] = cocos2d::Vec2(740 / TIscale, 1240 / TIscale);
	WayPoints[30][1] = cocos2d::Vec2(780 / TIscale, 1280 / TIscale);//WAY POINT 31
	WayPoints[30][2] = cocos2d::Vec2(820 / TIscale, 1320 / TIscale);

	WayPoints[31][0] = cocos2d::Vec2(850 / TIscale, 1120 / TIscale);
	WayPoints[31][1] = cocos2d::Vec2(900 / TIscale, 1150 / TIscale);//WAY POINT 32
	WayPoints[31][2] = cocos2d::Vec2(950 / TIscale, 1180 / TIscale);

	WayPoints[32][0] = cocos2d::Vec2(835 / TIscale, 980 / TIscale);
	WayPoints[32][1] = cocos2d::Vec2(870 / TIscale, 960 / TIscale);//WAY POINT 33
	WayPoints[32][2] = cocos2d::Vec2(910 / TIscale, 940 / TIscale);

	WayPoints[33][0] = cocos2d::Vec2(710 / TIscale, 860 / TIscale);
	WayPoints[33][1] = cocos2d::Vec2(720 / TIscale, 815 / TIscale);//WAY POINT 34
	WayPoints[33][2] = cocos2d::Vec2(730 / TIscale, 770 / TIscale);

	WayPoints[34][0] = cocos2d::Vec2(450 / TIscale, 650 / TIscale);
	WayPoints[34][1] = cocos2d::Vec2(400 / TIscale, 700 / TIscale);//WAY POINT 35
	WayPoints[34][2] = cocos2d::Vec2(350 / TIscale, 750 / TIscale);

	WayPoints[35][0] = cocos2d::Vec2(350 / TIscale, 550 / TIscale);
	WayPoints[35][1] = cocos2d::Vec2(300 / TIscale, 600 / TIscale);//WAY POINT 36
	WayPoints[35][2] = cocos2d::Vec2(250 / TIscale, 650 / TIscale);

	WayPoints[36][0] = cocos2d::Vec2(280 / TIscale, 150 / TIscale);
	WayPoints[36][1] = cocos2d::Vec2(220 / TIscale, 160 / TIscale);//WAY POINT 37
	WayPoints[36][2] = cocos2d::Vec2(170 / TIscale, 170 / TIscale);

	WayPoints[37][0] = cocos2d::Vec2(260 / TIscale, 0 / TIscale);
	WayPoints[37][1] = cocos2d::Vec2(220 / TIscale, 0 / TIscale);//WAY POINT 38
	WayPoints[37][2] = cocos2d::Vec2(170 / TIscale, 0 / TIscale);

	WayPoints[38][0] = cocos2d::Vec2(260 / TIscale, -100 / TIscale);
	WayPoints[38][1] = cocos2d::Vec2(220 / TIscale, -100 / TIscale);//WAY POINT 39
	WayPoints[38][2] = cocos2d::Vec2(170 / TIscale, -100 / TIscale);

	WayPoints[39][0] = cocos2d::Vec2(310 / TIscale, -400 / TIscale);
	WayPoints[39][1] = cocos2d::Vec2(340 / TIscale, -380 / TIscale);//WAY POINT 40
	WayPoints[39][2] = cocos2d::Vec2(380 / TIscale, -370 / TIscale);

	WayPoints[40][0] = cocos2d::Vec2(450 / TIscale, -650 / TIscale);
	WayPoints[40][1] = cocos2d::Vec2(400 / TIscale, -700 / TIscale);//WAY POINT 41
	WayPoints[40][2] = cocos2d::Vec2(350 / TIscale, -750 / TIscale);

	WayPoints[41][0] = cocos2d::Vec2(750 / TIscale, -950 / TIscale);
	WayPoints[41][1] = cocos2d::Vec2(700 / TIscale, -1000 / TIscale);//WAY POINT 42
	WayPoints[41][2] = cocos2d::Vec2(650 / TIscale, -1050 / TIscale);

	WayPoints[42][0] = cocos2d::Vec2(1050 / TIscale, -950 / TIscale);
	WayPoints[42][1] = cocos2d::Vec2(1093 / TIscale, -1000 / TIscale);//WAY POINT 43
	WayPoints[42][2] = cocos2d::Vec2(1150 / TIscale, -1050 / TIscale);

	WayPoints[43][0] = cocos2d::Vec2(1650 / TIscale, -350 / TIscale);
	WayPoints[43][1] = cocos2d::Vec2(1700 / TIscale, -400 / TIscale);//WAY POINT 44
	WayPoints[43][2] = cocos2d::Vec2(1750 / TIscale, -450 / TIscale);

	WayPoints[44][0] = cocos2d::Vec2(1850 / TIscale, 750 / TIscale);
	WayPoints[44][1] = cocos2d::Vec2(1800 / TIscale, 800 / TIscale);//WAY POINT 45
	WayPoints[44][2] = cocos2d::Vec2(1750 / TIscale, 850 / TIscale);

	WayPoints[45][0] = cocos2d::Vec2(2050 / TIscale, 950 / TIscale);
	WayPoints[45][1] = cocos2d::Vec2(2000 / TIscale, 1000 / TIscale);//WAY POINT 46
	WayPoints[45][2] = cocos2d::Vec2(1950 / TIscale, 1050 / TIscale);

	WayPoints[46][0] = cocos2d::Vec2(2350 / TIscale, 950 / TIscale);
	WayPoints[46][1] = cocos2d::Vec2(2400 / TIscale, 1000 / TIscale);//WAY POINT 47
	WayPoints[46][2] = cocos2d::Vec2(2450 / TIscale, 1060 / TIscale);

	WayPoints[47][0] = cocos2d::Vec2(2534 / TIscale, 731 / TIscale);
	WayPoints[47][1] = cocos2d::Vec2(2578 / TIscale, 770 / TIscale);//WAY POINT 48
	WayPoints[47][2] = cocos2d::Vec2(2618 / TIscale, 813 / TIscale);

	WayPoints[48][0] = cocos2d::Vec2(2550 / TIscale, 250 / TIscale);
	WayPoints[48][1] = cocos2d::Vec2(2600 / TIscale, 200 / TIscale);//WAY POINT 49
	WayPoints[48][2] = cocos2d::Vec2(2650 / TIscale, 150 / TIscale);

	WayPoints[49][0] = cocos2d::Vec2(2350 / TIscale, -350 / TIscale);
	WayPoints[49][1] = cocos2d::Vec2(2294 / TIscale, -310 / TIscale);//WAY POINT 50
	WayPoints[49][2] = cocos2d::Vec2(2226 / TIscale, -271 / TIscale);

	WayPoints[50][0] = cocos2d::Vec2(2350 / TIscale, -550 / TIscale);
	WayPoints[50][1] = cocos2d::Vec2(2293 / TIscale, -586 / TIscale);//WAY POINT 51
	WayPoints[50][2] = cocos2d::Vec2(2227 / TIscale, -627 / TIscale);

	WayPoints[51][0] = cocos2d::Vec2(2350 / TIscale, -900 / TIscale);
	WayPoints[51][1] = cocos2d::Vec2(2400 / TIscale, -900 / TIscale);//WAY POINT 52
	WayPoints[51][2] = cocos2d::Vec2(2450 / TIscale, -900 / TIscale);

	WayPoints[52][0] = cocos2d::Vec2(2350 / TIscale, -1100 / TIscale);
	WayPoints[52][1] = cocos2d::Vec2(2406 / TIscale, -1101 / TIscale);//WAY POINT 53
	WayPoints[52][2] = cocos2d::Vec2(2460 / TIscale, -1100 / TIscale);

	WayPoints[53][0] = cocos2d::Vec2(2150 / TIscale, -1340 / TIscale);
	WayPoints[53][1] = cocos2d::Vec2(2200 / TIscale, -1380 / TIscale);//WAY POINT 54
	WayPoints[53][2] = cocos2d::Vec2(2250 / TIscale, -1420 / TIscale);

	WayPoints[54][0] = cocos2d::Vec2(0 / TIscale, -1350 / TIscale);
	WayPoints[54][1] = cocos2d::Vec2(0 / TIscale, -1400 / TIscale);//WAY POINT 55
	WayPoints[54][2] = cocos2d::Vec2(0 / TIscale, -1450 / TIscale);

	WayPoints[55][0] = cocos2d::Vec2(-2450 / TIscale, -1350 / TIscale);
	WayPoints[55][1] = cocos2d::Vec2(-2500 / TIscale, -1400 / TIscale);//WAY POINT 56
	WayPoints[55][2] = cocos2d::Vec2(-2550 / TIscale, -1450 / TIscale);

	WayPoints[56][0] = cocos2d::Vec2(-2550 / TIscale, -1250 / TIscale);
	WayPoints[56][1] = cocos2d::Vec2(-2600 / TIscale, -1300 / TIscale);//WAY POINT 57
	WayPoints[56][2] = cocos2d::Vec2(-2650 / TIscale, -1350 / TIscale);

	WayPoints[57][0] = cocos2d::Vec2(-2557 / TIscale, -1100 / TIscale);
	WayPoints[57][1] = cocos2d::Vec2(-2612 / TIscale, -1100 / TIscale);//WAY POINT 58
	WayPoints[57][2] = cocos2d::Vec2(-2690 / TIscale, -1100 / TIscale);

	WayPoints[58][0] = cocos2d::Vec2(-2480 / TIscale, -620 / TIscale);//TURNING INTO GET HEALTH
	WayPoints[58][1] = cocos2d::Vec2(-2600 / TIscale, -620 / TIscale);//WAY POINT 59
	WayPoints[58][2] = cocos2d::Vec2(-2700 / TIscale, -620 / TIscale);

	WayPoints[59][0] = cocos2d::Vec2(-2200 / TIscale, -400 / TIscale);
	WayPoints[59][1] = cocos2d::Vec2(-2600 / TIscale, -400 / TIscale);//WAY POINT 60
	WayPoints[59][2] = cocos2d::Vec2(-2700 / TIscale, -400 / TIscale);

	WayPoints[60][0] = cocos2d::Vec2(-2200 / TIscale, 400 / TIscale);
	WayPoints[60][1] = cocos2d::Vec2(-2600 / TIscale, 400 / TIscale);//WAY POINT 61
	WayPoints[60][2] = cocos2d::Vec2(-2700 / TIscale, 400 / TIscale);

	WayPoints[61][0] = cocos2d::Vec2(-2450 / TIscale, 650 / TIscale);
	WayPoints[61][1] = cocos2d::Vec2(-2600 / TIscale, 650 / TIscale);//WAY POINT 62
	WayPoints[61][2] = cocos2d::Vec2(-2700 / TIscale, 650 / TIscale);


	wayPointCounter = 0;
	enemyOneCurrentWayPoint = WayPoints[wayPointCounter][enemyOneWayPointSkill];
	wayPointSprite = Sprite::create("TrackOne/WayPoint.png");
	wayPointSprite->setPosition(enemyOneCurrentWayPoint);
	this->addChild(wayPointSprite, 2);
}

//THE TRACK WAY POINTS USED FOR A LIST OF REASONS INCLUDING BACKWARDS DETECTION - DANIEL
void FirstWorld::trackWayPoints()
{
	DirectionWayPoint* finishLine = new DirectionWayPoint();
	finishLine->setID(false, 0, "5by2");
	finishLine->getSprite()->setPosition(Vec2(-2650 / TIscale, 0 / TIscale));
	this->addChild(finishLine->getSprite(), 2);
	this->directionalWayPoints.push_back(finishLine);

	DirectionWayPoint* dir1 = new DirectionWayPoint();
	dir1->setID(false, 1, "5by2");
	dir1->getSprite()->setPosition(Vec2(-2650 / TIscale, 760 / TIscale));
	this->addChild(dir1->getSprite(), 2);
	this->directionalWayPoints.push_back(dir1);

	DirectionWayPoint* dir2 = new DirectionWayPoint();
	dir2->setID(false, 2, "1by3");
	dir2->getSprite()->setPosition(Vec2(-2250 / TIscale, 1250 / TIscale));
	this->addChild(dir2->getSprite(), 2);
	this->directionalWayPoints.push_back(dir2);

	DirectionWayPoint* dir3 = new DirectionWayPoint();
	dir3->setID(false, 3, "1by3");
	dir3->getSprite()->setPosition(Vec2(-1250 / TIscale, 1250 / TIscale));
	this->addChild(dir3->getSprite(), 2);
	this->directionalWayPoints.push_back(dir3);

	DirectionWayPoint* dir4 = new DirectionWayPoint();
	dir4->setID(false, 4, "6by2");
	dir4->getSprite()->setPosition(Vec2(-800 / TIscale, 900 / TIscale));
	this->addChild(dir4->getSprite(), 2);
	this->directionalWayPoints.push_back(dir4);

	DirectionWayPoint* dir5 = new DirectionWayPoint();
	dir5->setID(false, 5, "1by3");
	dir5->getSprite()->setPosition(Vec2(-1250 / TIscale, 550 / TIscale));
	this->addChild(dir5->getSprite(), 2);
	this->directionalWayPoints.push_back(dir5);

	DirectionWayPoint* dir6 = new DirectionWayPoint();
	dir6->setID(false, 6, "1by3");
	dir6->getSprite()->setPosition(Vec2(-1650 / TIscale, 750 / TIscale));
	this->addChild(dir6->getSprite(), 2);
	this->directionalWayPoints.push_back(dir6);

	DirectionWayPoint* dir7 = new DirectionWayPoint();
	dir7->setID(false, 7, "2by1");
	dir7->getSprite()->setPosition(Vec2(-1900 / TIscale, 450 / TIscale));
	this->addChild(dir7->getSprite(), 2);
	this->directionalWayPoints.push_back(dir7);

	DirectionWayPoint* dir8 = new DirectionWayPoint();
	dir8->setID(false, 8, "2by1");
	dir8->getSprite()->setPosition(Vec2(-1900 / TIscale, -350 / TIscale));
	this->addChild(dir8->getSprite(), 2);
	this->directionalWayPoints.push_back(dir8);

	DirectionWayPoint* dir9 = new DirectionWayPoint();
	dir9->setID(false, 9, "3by1");
	dir9->getSprite()->setPosition(Vec2(-2150 / TIscale, -750 / TIscale));
	this->addChild(dir9->getSprite(), 2);
	this->directionalWayPoints.push_back(dir9);

	DirectionWayPoint* dir10 = new DirectionWayPoint();
	dir10->setID(false, 10, "3by1");
	dir10->getSprite()->setPosition(Vec2(-2150 / TIscale, -750 / TIscale));
	this->addChild(dir10->getSprite(), 2);
	this->directionalWayPoints.push_back(dir10);

	DirectionWayPoint* dir11 = new DirectionWayPoint();
	dir11->setID(false, 11, "1by2");
	dir11->getSprite()->setPosition(Vec2(-1850 / TIscale, -1000 / TIscale));
	this->addChild(dir11->getSprite(), 2);
	this->directionalWayPoints.push_back(dir11);

	DirectionWayPoint* dir12 = new DirectionWayPoint();
	dir12->setID(false, 12, "1by2");
	dir12->getSprite()->setPosition(Vec2(-550 / TIscale, -1000 / TIscale));
	this->addChild(dir12->getSprite(), 2);
	this->directionalWayPoints.push_back(dir12);

	DirectionWayPoint* dir13 = new DirectionWayPoint();
	dir13->setID(false, 13, "5by2");
	dir13->getSprite()->setPosition(Vec2(-150 / TIscale, -700 / TIscale));
	this->addChild(dir13->getSprite(), 2);
	this->directionalWayPoints.push_back(dir13);

	DirectionWayPoint* dir14 = new DirectionWayPoint();
	dir14->setID(false, 14, "3by3");
	dir14->getSprite()->setPosition(Vec2(-650 / TIscale, -350 / TIscale));
	this->addChild(dir14->getSprite(), 2);
	this->directionalWayPoints.push_back(dir14);

	DirectionWayPoint* dir15 = new DirectionWayPoint();
	dir15->setID(false, 15, "1by2");
	dir15->getSprite()->setPosition(Vec2(-1250 / TIscale, -700 / TIscale));
	this->addChild(dir15->getSprite(), 2);
	this->directionalWayPoints.push_back(dir15);

	DirectionWayPoint* dir16 = new DirectionWayPoint();
	dir16->setID(false, 16, "2by1");
	dir16->getSprite()->setPosition(Vec2(-1600 / TIscale, -350 / TIscale));
	this->addChild(dir16->getSprite(), 2);
	this->directionalWayPoints.push_back(dir16);

	DirectionWayPoint* dir17 = new DirectionWayPoint();
	dir17->setID(false, 17, "2by1");
	dir17->getSprite()->setPosition(Vec2(-1600 / TIscale, -150 / TIscale));
	this->addChild(dir17->getSprite(), 2);
	this->directionalWayPoints.push_back(dir17);

	DirectionWayPoint* dir18 = new DirectionWayPoint();
	dir18->setID(false, 18, "1by3");
	dir18->getSprite()->setPosition(Vec2(-1350 / TIscale, 150 / TIscale));
	this->addChild(dir18->getSprite(), 2);
	this->directionalWayPoints.push_back(dir18);

	DirectionWayPoint* dir19 = new DirectionWayPoint();
	dir19->setID(false, 19, "1by3");
	dir19->getSprite()->setPosition(Vec2(-750 / TIscale, 150 / TIscale));
	this->addChild(dir19->getSprite(), 2);
	this->directionalWayPoints.push_back(dir19);

	DirectionWayPoint* dir20 = new DirectionWayPoint();
	dir20->setID(false, 20, "3by1");
	dir20->getSprite()->setPosition(Vec2(-150 / TIscale, 750 / TIscale));
	this->addChild(dir20->getSprite(), 2);
	this->directionalWayPoints.push_back(dir20);

	DirectionWayPoint* dir21 = new DirectionWayPoint();
	dir21->setID(false, 21, "3by1");
	dir21->getSprite()->setPosition(Vec2(-150 / TIscale, 1050 / TIscale));
	this->addChild(dir21->getSprite(), 2);
	this->directionalWayPoints.push_back(dir21);

	DirectionWayPoint* dir22 = new DirectionWayPoint();
	dir22->setID(false, 22, "3by1");
	dir22->getSprite()->setPosition(Vec2(-150 / TIscale, 1050 / TIscale));
	this->addChild(dir22->getSprite(), 2);
	this->directionalWayPoints.push_back(dir22);

	DirectionWayPoint* dir23 = new DirectionWayPoint();
	dir23->setID(false, 23, "1by2");
	dir23->getSprite()->setPosition(Vec2(150 / TIscale, 1300 / TIscale));
	this->addChild(dir23->getSprite(), 2);
	this->directionalWayPoints.push_back(dir23);

	DirectionWayPoint* dir24 = new DirectionWayPoint();
	dir24->setID(false, 24, "1by2");
	dir24->getSprite()->setPosition(Vec2(650 / TIscale, 1300 / TIscale));
	this->addChild(dir24->getSprite(), 2);
	this->directionalWayPoints.push_back(dir24);

	DirectionWayPoint* dir25 = new DirectionWayPoint();
	dir25->setID(false, 25, "3by1");
	dir25->getSprite()->setPosition(Vec2(950 / TIscale, 1050 / TIscale));
	this->addChild(dir25->getSprite(), 2);
	this->directionalWayPoints.push_back(dir25);

	DirectionWayPoint* dir26 = new DirectionWayPoint();
	dir26->setID(false, 26, "2by3");
	dir26->getSprite()->setPosition(Vec2(600 / TIscale, 750 / TIscale));
	this->addChild(dir26->getSprite(), 2);
	this->directionalWayPoints.push_back(dir26);

	DirectionWayPoint* dir27 = new DirectionWayPoint();
	dir27->setID(false, 27, "3by1");
	dir27->getSprite()->setPosition(Vec2(250 / TIscale, 450 / TIscale));
	this->addChild(dir27->getSprite(), 2);
	this->directionalWayPoints.push_back(dir27);

	DirectionWayPoint* dir28 = new DirectionWayPoint();
	dir28->setID(false, 28, "3by1");
	dir28->getSprite()->setPosition(Vec2(250 / TIscale, 250 / TIscale));
	this->addChild(dir28->getSprite(), 2);
	this->directionalWayPoints.push_back(dir28);

	DirectionWayPoint* dir29 = new DirectionWayPoint();
	dir29->setID(false, 29, "4by1");
	dir29->getSprite()->setPosition(Vec2(100 / TIscale, -50 / TIscale));
	this->addChild(dir29->getSprite(), 2);
	this->directionalWayPoints.push_back(dir29);

	DirectionWayPoint* dir30 = new DirectionWayPoint();
	dir30->setID(false, 30, "3by2");
	dir30->getSprite()->setPosition(Vec2(350 / TIscale, -500 / TIscale));
	this->addChild(dir30->getSprite(), 2);
	this->directionalWayPoints.push_back(dir30);

	DirectionWayPoint* dir31 = new DirectionWayPoint();
	dir31->setID(false, 31, "2by3");
	dir31->getSprite()->setPosition(Vec2(900 / TIscale, -1050 / TIscale));
	this->addChild(dir31->getSprite(), 2);
	this->directionalWayPoints.push_back(dir31);

	DirectionWayPoint* dir32 = new DirectionWayPoint();
	dir32->setID(false, 32, "2by3");
	dir32->getSprite()->setPosition(Vec2(900 / TIscale, -1050 / TIscale));
	this->addChild(dir32->getSprite(), 2);
	this->directionalWayPoints.push_back(dir32);

	DirectionWayPoint* dir33 = new DirectionWayPoint();
	dir33->setID(false, 33, "3by1");
	dir33->getSprite()->setPosition(Vec2(1750 / TIscale, -250 / TIscale));
	this->addChild(dir33->getSprite(), 2);
	this->directionalWayPoints.push_back(dir33);

	DirectionWayPoint* dir34 = new DirectionWayPoint();
	dir34->setID(false, 34, "3by1");
	dir34->getSprite()->setPosition(Vec2(1750 / TIscale, 650 / TIscale));
	this->addChild(dir34->getSprite(), 2);
	this->directionalWayPoints.push_back(dir34);

	DirectionWayPoint* dir35 = new DirectionWayPoint();
	dir35->setID(false, 35, "2by4");
	dir35->getSprite()->setPosition(Vec2(2200 / TIscale, 1100 / TIscale));
	this->addChild(dir35->getSprite(), 2);
	this->directionalWayPoints.push_back(dir35);

	DirectionWayPoint* dir36 = new DirectionWayPoint();
	dir36->setID(false, 36, "3by1");
	dir36->getSprite()->setPosition(Vec2(2650 / TIscale, 650 / TIscale));
	this->addChild(dir36->getSprite(), 2);
	this->directionalWayPoints.push_back(dir36);

	DirectionWayPoint* dir37 = new DirectionWayPoint();
	dir37->setID(false, 37, "3by1");
	dir37->getSprite()->setPosition(Vec2(2650 / TIscale, 350 / TIscale));
	this->addChild(dir37->getSprite(), 2);
	this->directionalWayPoints.push_back(dir37);

	DirectionWayPoint* dir38 = new DirectionWayPoint();
	dir38->setID(false, 38, "4by1");
	dir38->getSprite()->setPosition(Vec2(2200 / TIscale, -450 / TIscale));
	this->addChild(dir38->getSprite(), 2);
	this->directionalWayPoints.push_back(dir38);

	DirectionWayPoint* dir39 = new DirectionWayPoint();
	dir39->setID(false, 39, "5by2");
	dir39->getSprite()->setPosition(Vec2(2550 / TIscale, -1000 / TIscale));
	this->addChild(dir39->getSprite(), 2);
	this->directionalWayPoints.push_back(dir39);

	DirectionWayPoint* dir40 = new DirectionWayPoint();
	dir40->setID(false, 40, "2by2");
	dir40->getSprite()->setPosition(Vec2(2000 / TIscale, -1400 / TIscale));
	this->addChild(dir40->getSprite(), 2);
	this->directionalWayPoints.push_back(dir40);

	DirectionWayPoint* dir41 = new DirectionWayPoint();
	dir41->setID(false, 41, "2by2");
	dir41->getSprite()->setPosition(Vec2(100 / TIscale, -1400 / TIscale));
	this->addChild(dir41->getSprite(), 2);
	this->directionalWayPoints.push_back(dir41);

	DirectionWayPoint* dir42 = new DirectionWayPoint();
	dir42->setID(false, 42, "2by2");
	dir42->getSprite()->setPosition(Vec2(-2300 / TIscale, -1400 / TIscale));
	this->addChild(dir42->getSprite(), 2);
	this->directionalWayPoints.push_back(dir42);

	DirectionWayPoint* dir43 = new DirectionWayPoint();
	dir43->setID(false, 43, "3by1");
	dir43->getSprite()->setPosition(Vec2(-2650 / TIscale, -1150 / TIscale));
	this->addChild(dir43->getSprite(), 2);
	this->directionalWayPoints.push_back(dir43);
}

//VEHICLES OBJECTS FOR OUR FIRST SCENE - DANIEL
void FirstWorld::vehicleObjects()
{
	//PLAYER VEHICLE OBJECT - DANIEL
	playerVehicleObject = new Vehicle();
	playerVehicleObject->setAngle(-90);
	playerVehicleObject->setPosition(Vec2(-2650 / TIscale, 0 / TIscale));
	playerVehicleObject->setSteeringPower(2);
	playerVehicleObject->setType("player");
	this->addChild(playerVehicleObject->getSprite(), 9);
	vehicles.push_back(playerVehicleObject);

	//AI CAR I VEHICLE OBJECT - DANIEL
	enemyOneVehicleObject = new Vehicle();
	enemyOneVehicleObject->setAngle(-90);
	enemyOneVehicleObject->setPosition(Vec2(-2550 / TIscale, 0 / TIscale));
	enemyOneVehicleObject->setAutoControl(true);
	enemyOneVehicleObject->setSpeed(10);
	enemyOneVehicleObject->setSteeringPower(3);
	enemyOneVehicleObject->setType("enemy");
	this->addChild(enemyOneVehicleObject->getSprite(), 9);
	vehicles.push_back(enemyOneVehicleObject);
	
	this->runAction(cocos2d::Follow::create(playerVehicleObject->getSprite()));
}

//ALL OBSTACLES OBJECTS FOR OUR FIRST SCENE - SAMUEL
void FirstWorld::obstacles()
{
		GameObjectPhysics* circleObject1 = new Circle();
		circleObject1->getSprite()->setPosition(-2700 / TIscale, 1000 / TIscale);
		this->objects.push_back(circleObject1);
		this->addChild(circleObject1->getSprite(), 4);
		circleObject1->animate();

		GameObjectPhysics* circleObject2 = new Circle();
		circleObject2->getSprite()->setPosition(-2825 / TIscale, 1000 / TIscale);
		this->objects.push_back(circleObject2);
		this->addChild(circleObject2->getSprite(), 4);

		GameObjectPhysics* circleObject3 = new Circle();
		circleObject3->getSprite()->setPosition(-2860 / TIscale, 880 / TIscale);
		this->objects.push_back(circleObject3);
		this->addChild(circleObject3->getSprite(), 4);

		GameObjectPhysics* circleObject4 = new Circle();
		circleObject4->getSprite()->setPosition(-2860 / TIscale, 900 / TIscale);
		this->objects.push_back(circleObject4);
		this->addChild(circleObject4->getSprite(), 4);

		GameObjectPhysics* circleObject5 = new Circle();
		circleObject5->getSprite()->setPosition(-2860 / TIscale, 920 / TIscale);
		this->objects.push_back(circleObject5);
		this->addChild(circleObject5->getSprite(), 4);

		GameObjectPhysics* circleObject6 = new Circle();
		circleObject6->getSprite()->setPosition(-2860 / TIscale, 940 / TIscale);
		this->objects.push_back(circleObject6);
		this->addChild(circleObject6->getSprite(), 4);

		GameObjectPhysics* circleObject7 = new Circle();
		circleObject7->getSprite()->setPosition(-2860 / TIscale, 1000 / TIscale);
		this->objects.push_back(circleObject7);
		this->addChild(circleObject7->getSprite(), 4);

		GameObjectPhysics* circleObject8 = new Circle();
		circleObject8->getSprite()->setPosition(-2860 / TIscale, 1000 / TIscale);
		this->objects.push_back(circleObject8);
		this->addChild(circleObject8->getSprite(), 4);

		GameObjectPhysics* circleObject9 = new Circle();
		circleObject9->getSprite()->setPosition(-2825 / TIscale, 1010 / TIscale);
		this->objects.push_back(circleObject9);
		this->addChild(circleObject9->getSprite(), 4);

		GameObjectPhysics* circleObject10 = new Circle();
		circleObject10->getSprite()->setPosition(-2790 / TIscale, 1010 / TIscale);
		this->objects.push_back(circleObject10);
		this->addChild(circleObject10->getSprite(), 4);

		GameObjectPhysics* circleObject11 = new Circle();
		circleObject11->getSprite()->setPosition(-2820 / TIscale, 1050 / TIscale);
		this->objects.push_back(circleObject11);
		this->addChild(circleObject11->getSprite(), 4);

		GameObjectPhysics* circleObject12 = new Circle();
		circleObject12->getSprite()->setPosition(-2780 / TIscale, 1070 / TIscale);
		this->objects.push_back(circleObject12);
		this->addChild(circleObject12->getSprite(), 4);

		GameObjectPhysics* circleObject13 = new Circle();
		circleObject13->getSprite()->setPosition(-2750 / TIscale, 1070 / TIscale);
		this->objects.push_back(circleObject13);
		this->addChild(circleObject13->getSprite(), 4);

		GameObjectPhysics* circleObject14 = new Circle();
		circleObject14->getSprite()->setPosition(-2770 / TIscale, 1100 / TIscale);
		this->objects.push_back(circleObject14);
		this->addChild(circleObject14->getSprite(), 4);

		GameObjectPhysics* circleObject15 = new Circle();
		circleObject15->getSprite()->setPosition(-2740 / TIscale, 1100 / TIscale);
		this->objects.push_back(circleObject15);
		this->addChild(circleObject15->getSprite(), 4);

		GameObjectPhysics* circleObject16 = new Circle();
		circleObject16->getSprite()->setPosition(-2700 / TIscale, 1100 / TIscale);
		this->objects.push_back(circleObject16);
		this->addChild(circleObject16->getSprite(), 4);

		GameObjectPhysics* circleObject17 = new Circle();
		circleObject17->getSprite()->setPosition(-2720 / TIscale, 1150 / TIscale);
		this->objects.push_back(circleObject17);
		this->addChild(circleObject17->getSprite(), 4);

		GameObjectPhysics* circleObject18 = new Circle();
		circleObject18->getSprite()->setPosition(-2690 / TIscale, 1150 / TIscale);
		this->objects.push_back(circleObject18);
		this->addChild(circleObject18->getSprite(), 4);

		GameObjectPhysics* circleObject19 = new Circle();
		circleObject19->getSprite()->setPosition(-2650 / TIscale, 1150 / TIscale);
		this->objects.push_back(circleObject19);
		this->addChild(circleObject19->getSprite(), 4);

		GameObjectPhysics* circleObject20 = new Circle();
		circleObject20->getSprite()->setPosition(-2680 / TIscale, 1180 / TIscale);
		this->objects.push_back(circleObject20);
		this->addChild(circleObject20->getSprite(), 4);

		GameObjectPhysics* circleObject21 = new Circle();
		circleObject21->getSprite()->setPosition(-2650 / TIscale, 1180 / TIscale);
		this->objects.push_back(circleObject21);
		this->addChild(circleObject21->getSprite(), 4);

		GameObjectPhysics* circleObject22 = new Circle();
		circleObject22->getSprite()->setPosition(-2600 / TIscale, 1200 / TIscale);
		this->objects.push_back(circleObject22);
		this->addChild(circleObject22->getSprite(), 4);

		GameObjectPhysics* circleObject23 = new Circle();
		circleObject23->getSprite()->setPosition(-2620 / TIscale, 1220 / TIscale);
		this->objects.push_back(circleObject23);
		this->addChild(circleObject23->getSprite(), 4);

		GameObjectPhysics* circleObject24 = new Circle();
		circleObject24->getSprite()->setPosition(-2600 / TIscale, 1220 / TIscale);
		this->objects.push_back(circleObject24);
		this->addChild(circleObject24->getSprite(), 4);

		GameObjectPhysics* circleObject25 = new Circle();
		circleObject25->getSprite()->setPosition(-2550 / TIscale, 1250 / TIscale);
		this->objects.push_back(circleObject25);
		this->addChild(circleObject25->getSprite(), 4);

		GameObjectPhysics* circleObject26 = new Circle();
		circleObject26->getSprite()->setPosition(-2600 / TIscale, 1280 / TIscale);
		this->objects.push_back(circleObject26);
		this->addChild(circleObject26->getSprite(), 4);

		GameObjectPhysics* circleObject27 = new Circle();
		circleObject27->getSprite()->setPosition(-2550 / TIscale, 1280 / TIscale);
		this->objects.push_back(circleObject27);
		this->addChild(circleObject27->getSprite(), 4);

		GameObjectPhysics* circleObject28 = new Circle();
		circleObject28->getSprite()->setPosition(-2500 / TIscale, 1310 / TIscale);
		this->objects.push_back(circleObject28);
		this->addChild(circleObject28->getSprite(), 4);

		GameObjectPhysics* circleObject29 = new Circle();
		circleObject29->getSprite()->setPosition(-2520 / TIscale, 1350 / TIscale);
		this->objects.push_back(circleObject29);
		this->addChild(circleObject29->getSprite(), 4);

		GameObjectPhysics* circleObject30 = new Circle();
		circleObject30->getSprite()->setPosition(-2480 / TIscale, 1350 / TIscale);
		this->objects.push_back(circleObject30);
		this->addChild(circleObject30->getSprite(), 4);

		GameObjectPhysics* triangle1Object1 = new Triangle();
		triangle1Object1->getSprite()->setPosition(-2480 / TIscale, 1350 / TIscale);
		this->objects.push_back(triangle1Object1);
		this->addChild(triangle1Object1->getSprite(), 4);

		GameObjectPhysics* square1Object1 = new Square();
		square1Object1->getSprite()->setPosition(-2480 / TIscale, 1350 / TIscale);
		this->objects.push_back(square1Object1);
		this->addChild(square1Object1->getSprite(), 4);
}

//EVENT LISTENERS FOR OUR FIRST SCENE - DANIEL
void FirstWorld::eventListeners()
{
	//ACTION LISTENERS FOR TOUCH SCREEN
	touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(FirstWorld::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);


	//OBJECTS COLLISION DETECTION AND ACTION
	contactListenerBegin = EventListenerPhysicsContact::create();
	contactListenerBegin->onContactBegin = CC_CALLBACK_1(FirstWorld::onContactBegin, this);
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
				if(playerVehicleObject->availableWeapon())
				{
					//CHECK WHICH WEAPON IS AVAILABLE AND USE
					if (playerVehicleObject->getRocketStatus())
					{
						cocos2d::Sprite* target;
						for (auto vehicle : this->vehicles)
						{
							if (vehicle->getType() != "player")
							{
								float distance = std::sqrt(std::pow((vehicle->getSprite()->getPosition().x - playerVehicleObject->getSprite()->getPosition().x), 2) + std::pow((vehicle->getSprite()->getPosition().y - playerVehicleObject->getSprite()->getPosition().y), 2));
								CCLOG("DISTANCE ROCKET : %f", distance);
								if (distance < 300)
								{
									target = vehicle->getSprite();
								}
							}
						}
						GameObject* rocket = playerVehicleObject->fireRocket(target, false);
						this->addChild(rocket->getSprite());//ROCKET CAN BE LOCK ON OR NOT
						projectiles.push_back(rocket);
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
		}
	};
	eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		//REMOVE KEY
		keys.erase(keyCode);
		playerVehicleObject->setSlowDownStatus(true);
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
}

//GAME HUD DISPLAY - SAMANTHA
void FirstWorld::hud()
{
	//HUD LAYER SITS ON TOP OF GAME LAYER - WE CAN REST INFORMATION HERE AND UPDATE THAT INFORMATION IN THE UPDATE FUCNTION
	HUD = LayerGradient::create(Color4B(0, 0, 0, 0), Color4B(0, 0, 0, 0));
	HUD->setContentSize(visibleSize);
	this->addChild(HUD, 10);//Z-INDEX 2
}

//DIRECTOR & SCREEN ORIGIN CENTER POINT
void FirstWorld::director()
{
	//DIRECTOR RESOLUTION - VISIBLSIZE CAN BE USED THROUGH OUT CLASS TO GET SCREEN WIDTH AND HEIGHT - DANIEL
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();//GETS CENTER OF DISPLAY
}

//LABELS
void FirstWorld::labels()
{
	//BACKWARDS NOTIFICATION
	backwardsLabel = Label::createWithTTF("", "fonts/Marker Felt.ttf", 50);
	HUD->addChild(backwardsLabel);
	backwardsLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

	//SPEED STATUS
	speed = Label::createWithTTF(std::to_string(playerVehicleObject->getSpeed()), "fonts/Marker Felt.ttf", 20);
	HUD->addChild(speed);
	speed->setPosition(Vec2(20, visibleSize.height - 50));
	speed->setAnchorPoint(cocos2d::Vec2(0,0));

	slowDownStatus = Label::createWithTTF("TRUE", "fonts/Marker Felt.ttf", 20);
	HUD->addChild(slowDownStatus);
	slowDownStatus->setPosition(Vec2(20, visibleSize.height - 100));
	slowDownStatus->setAnchorPoint(cocos2d::Vec2(0, 0));

	angle = Label::createWithTTF("", "fonts/Marker Felt.ttf", 20);
	HUD->addChild(angle);
	angle->setPosition(Vec2(20, visibleSize.height - 150));
	angle->setAnchorPoint(cocos2d::Vec2(0, 0));

	//TIMER - SAMUEL
	timer = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 20);
	HUD->addChild(timer);
	timer->setPosition(Vec2(50, visibleSize.height - 200));
	angle->setAnchorPoint(cocos2d::Vec2(0, 0));

	//WEAPON AVAILABLE
	weaponLabel = Label::createWithTTF("", "fonts/Marker Felt.ttf", 20);
	HUD->addChild(weaponLabel);
	weaponLabel->setPosition(Vec2(30, visibleSize.height - 250));
	weaponLabel->setAnchorPoint(cocos2d::Vec2(0, 0));
}

//CAMERA
void FirstWorld::moveWorld() 
{
	//auto ws = playerVehicleObject->getParent()->convertToWorldSpace(playerVehicleObject->getPosition()); // 1
	//auto ns = worldNode->getParent()->convertToNodeSpace(ws); // 2
	//worldNode->setPosition(worldNode->getPosition() - ns + Director::getInstance()->getWinSize() / 2); // 3
}

//CRONO CLOCK FOR TIMER FUNCTIONALITY
std::map<cocos2d::EventKeyboard::KeyCode, std::chrono::high_resolution_clock::time_point> FirstWorld::keys;