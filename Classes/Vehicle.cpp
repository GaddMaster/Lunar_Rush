#include "Vehicle.h"

USING_NS_CC;

//CONSTRUCTOR - DE-CONSTRUCTOR
Vehicle::Vehicle() ://WE INITIALIZE ALL VARIABLES TO DEFAULT VALUES
	trusterStatus(false),
	machineGunStatus(false),
	rocketStatus(true),
	shieldStatus(false),
	mineStatus(false),
	velocityPoint(cocos2d::Vec2(0, 0)),
	angle_I(0.0), angle_II(0.0),
	slowDown(false),
	m_speed(0.0),
	driveStatus(true),
	bulletSpawnPoint(cocos2d::Vec2(0, 0)),
	bulletFirePoint(cocos2d::Vec2(0, 0)),
	weaponStatus("Empty"),
	position(Vec2(0, 0)),
	TIScale(1.7068),//1.7068
	steeringPower(5),
	autoDrive(false),
	angle_III(0.0),
	driveOffTimer(5),
	machineGunVelocity(500),
	machineGunSpawnGap(50),
	m_health(24),
	bullets(10),
	accelerateLock(false),
	de_accelerateLock(false),
	rocketSpeed(200),
	shieldLock(false),
	rocketSpawnGap(30),
	dead(false),
	currentWayPoint(cocos2d::Vec2(0,0)),
	wayPointCount(0)
{
	//CAR SPRITE
	sprite = Sprite::create("Ship/VehicleOne/idleSingle.png");

	//PHYSICS BODY
	mArray[0] = cocos2d::Vec2(-26 / TIscale, -3 / TIscale);
	mArray[1] = cocos2d::Vec2(-22 / TIscale, -6 / TIscale);
	mArray[2] = cocos2d::Vec2(35 / TIscale, -3 / TIscale);
	mArray[3] = cocos2d::Vec2(37 / TIscale, -1 / TIscale);
	mArray[4] = cocos2d::Vec2(37 / TIscale, 1 / TIscale);
	mArray[5] = cocos2d::Vec2(35 / TIscale, 3 / TIscale);
	mArray[6] = cocos2d::Vec2(-22 / TIscale, 6 / TIscale);
	mArray[7] = cocos2d::Vec2(-26 / TIscale, 3 / TIscale);
	mArray[8] = cocos2d::Vec2(-26 / TIscale, -3 / TIscale);
	physicsBody = PhysicsBody::createPolygon(mArray, 9, PhysicsMaterial(1, 0, 0));
	physicsBody->setCollisionBitmask(5);
	physicsBody->setContactTestBitmask(true);
	physicsBody->setAngularDamping(10);
	physicsBody->setDynamic(true);

	sprite->setPhysicsBody(physicsBody);

	wayPointSprite = Sprite::create("TrackOne/WayPoint.png");
	wayPointSprite->setPosition(cocos2d::Vec2(0,0));
}
Vehicle::~Vehicle()
{
	//NOT BEEN USED YET FOR ANYTHING MUCH
}

//SET & GET THE VELOCITY POINT FOR THE VEHICLE
void Vehicle::setVelocityPoint()
{
	if (driveStatus)
	{
		//RESET VELOCITY POINT
		velocityPoint = cocos2d::Vec2(0,0);

		angle_II = getAngle();

		//VELOCITY FUNCTIONALITY - QUADRANT CHECK AND ENTER
		if (angle_II >= 0 && angle_II < 90)//QUADRANT 1
		{
			//THIS MEANS WE ONLY DEAL WITH X AXIS - Y AXIS MUST BE ZERO
			if (angle_II == 0)
			{
				//VELOCITY POINT
				velocityPoint.x = m_speed;
			}
			//WE FIND OUR POINTS IN THE 1ST QUADRANT
			else
			{
				//VELOCITY POINT
				velocityPoint.x += m_speed*(cos(angle_II * 3.14 / 180));
				velocityPoint.y -= m_speed*(sin(angle_II * 3.14 / 180));
			}
		}
		else if (angle_II >= 90 && angle_II <= 180)//QUADRANT 2
		{
			if (angle_II == 90)
			{
				//VELOCITY POINT
				velocityPoint.x = 0;
				velocityPoint.y -= m_speed;
			}
			else if (angle_II == 180)
			{
				//VELOCITY POINT
				velocityPoint.x -= m_speed;
			}
			else
			{
				//VELOCITY POINT
				velocityPoint.x -= m_speed * (cos((180 - angle_II) * 3.14 / 180));
				velocityPoint.y -= m_speed * (sin((180 - angle_II) * 3.14 / 180));
			}
		}
		else if (angle_II < -90 && angle_II >= -180)//QUADRANT 3
		{
			if (angle_II == -180 || angle_II == 180)
			{
				//VELOCITY POINT
				velocityPoint.x -= m_speed;
				velocityPoint.y = 0;
			}
			else
			{
				//VELOCITY POINT
				velocityPoint.x -= m_speed*(cos((180 + angle_II) * 3.14 / 180));
				velocityPoint.y += m_speed*(sin((180 + angle_II) * 3.14 / 180));
			}
		}
		else if (angle_II < 0 && angle_II >= -90)//QUADRANT 4
		{
			if (angle_II == -90)
			{
				//VELOCITY POINT
				velocityPoint.x = 0;
				velocityPoint.y += m_speed;
			}
			else
			{
				//VELOCITY POINT
				velocityPoint.x += m_speed*(cos(fabs(angle_II) * 3.14 / 180));
				velocityPoint.y += m_speed*(sin(fabs(angle_II) * 3.14 / 180));
			}
		}
		else//ERROR JUST DEFAULT NOTHING
		{
			physicsBody->setVelocity(Vec2(0, 0));
		}
	}
}
cocos2d::Vec2 Vehicle::getVelocityPoint()
{
	return velocityPoint;//GET VELOCITY POINT OF PHYSICS BODY
}
void Vehicle::setVelocity()
{
	physicsBody->setVelocity(velocityPoint);//GET VELOCITY POINT OF PHYSICS BODY
}

//SET & GET MACHINE GUN SPAWN POINT AND VELOCITY POINT
void Vehicle::setMachineGunPoints()
{
	//SET BOTH SPAWN POINT AND VELOCITY POINT FOR A BULLET OBJECT
	//RESET POINT VALUES
	bulletSpawnPoint = Vec2(0, 0);
	bulletFirePoint = Vec2(0, 0);
	position = sprite->getPosition();

	//GET SPRITE ANGLE _TRANSFORMED
	angle_II = getAngle();

	//VELOCITY & SPAWN FUNCTIONALITY - QUADRANT CHECK AND ENTER
	if (angle_II >= 0 && angle_II < 90)//QUADRANT 1
	{
		//THIS MEANS WE ONLY DEAL WITH X AXIS - Y AXIS MUST BE ZERO
		if (angle_II == 0)
		{
			//BULLET SPAWN POINT
			bulletSpawnPoint.x = position.x + machineGunSpawnGap;
			bulletSpawnPoint.y = position.y;

			//BULLET FIRE VELOCITY POINT
			bulletFirePoint.x = machineGunVelocity;
		}
		else//WE FIND OUR POINTS IN THE 1ST QUADRANT
		{
			//BULLET SPAWN POINT
			bulletSpawnPoint.x = position.x + (machineGunSpawnGap * (cos(angle_II * 3.14 / 180)));
			bulletSpawnPoint.y = position.y - (machineGunSpawnGap * (sin(angle_II * 3.14 / 180)));

			//BULLET FIRE VELOCITY POINT
			bulletFirePoint.x += machineGunVelocity * (cos(angle_II * 3.14 / 180));
			bulletFirePoint.y -= machineGunVelocity * (sin(angle_II * 3.14 / 180));
		}
	}
	else if (angle_II >= 90 && angle_II <= 180)//QUADRANT 2
	{
		if (angle_II == 90)
		{
			//BULLET SPAWN POINT
			bulletSpawnPoint.x = position.x;
			bulletSpawnPoint.y = position.y - machineGunSpawnGap;

			//BULLET FIRE VELOCITY POINT
			bulletFirePoint.y -= machineGunVelocity;
		}
		else if (angle_II == 180)
		{
			//BULLET SPAWN POINT
			bulletSpawnPoint.x = position.x - machineGunSpawnGap;
			bulletSpawnPoint.y = position.y;

			//BULLET FIRE VELOCITY POINT
			bulletFirePoint.x -= machineGunVelocity;
		}
		else
		{
			//BULLET SPAWN POINT
			bulletSpawnPoint.x = position.x - (machineGunSpawnGap * (cos((180 - angle_II) * 3.14 / 180)));
			bulletSpawnPoint.y = position.y - (machineGunSpawnGap * (sin((180 - angle_II) * 3.14 / 180)));

			//BULLET FIRE VELOCITY POINT
			bulletFirePoint.x += machineGunVelocity * (cos(angle_II * 3.14 / 180));
			bulletFirePoint.y -= machineGunVelocity * (sin(angle_II * 3.14 / 180));
		}
	}
	else if (angle_II < -90 && angle_II >= -180)//QUADRANT 3
	{
		if (angle_II == -180)
		{
			//BULLET SPAWN POINT
			bulletSpawnPoint.x = position.x - machineGunSpawnGap;
			bulletSpawnPoint.y = position.y;

			//BULLET FIRE VELOCITY POINT
			bulletFirePoint.x -= machineGunVelocity;
		}
		else
		{
			//BULLET SPAWN POINT
			bulletSpawnPoint.x = position.x - (machineGunSpawnGap * (cos((180 + angle_II) * 3.14 / 180)));
			bulletSpawnPoint.y = position.y + (machineGunSpawnGap * (sin((180 + angle_II) * 3.14 / 180)));

			//BULLET FIRE VELOCITY POINT
			bulletFirePoint.x = machineGunVelocity * (cos(angle_II * 3.14 / 180));
			bulletFirePoint.y -= machineGunVelocity * (sin(angle_II * 3.14 / 180));
		}
	}
	else if (angle_II < 0 && angle_II >= -90)//QUADRANT 4
	{
		if (angle_II == -90)
		{
			//BULLET SPAWN POINT
			bulletSpawnPoint.x = position.x;
			bulletSpawnPoint.y = position.y + machineGunSpawnGap;

			//BULLET FIRE VELOCITY POINT
			bulletFirePoint.y = machineGunVelocity;
		}
		else
		{
			//BULLET SPAWN POINT
			bulletSpawnPoint.x = position.x + (machineGunSpawnGap * (cos(fabs(angle_II) * 3.14 / 180)));
			bulletSpawnPoint.y = position.y + (machineGunSpawnGap * (sin(fabs(angle_II) * 3.14 / 180)));

			//BULLET FIRE VELOCITY POINT
			bulletFirePoint.x += machineGunVelocity * (cos(angle_II * 3.14 / 180));
			bulletFirePoint.y -= machineGunVelocity * (sin(angle_II * 3.14 / 180));
		}
	}
	else//ERROR JUST DEFAULT NOTHING
	{
		physicsBody->setVelocity(Vec2(0, 0));
	}

}
cocos2d::Vec2 Vehicle::getBulletSpawnPoint()
{
	return bulletSpawnPoint;//WHERE BULLET SPAWNS 
}
cocos2d::Vec2 Vehicle::getBulletVelocityPoint()
{
	return bulletFirePoint;//GET BULLET VELOCITY POINT
}

//GET - SET ROCKET VELOCITY POINT AND SPAWN POINT
void Vehicle::setRocketPoints(cocos2d::Sprite* target)
{
	rocketSpawnPoint = Vec2(0, 0);
	position = sprite->getPosition();

	//GET SPRITE ANGLE _TRANSFORMED
	angle_II = getAngle();

	//VELOCITY & SPAWN FUNCTIONALITY - QUADRANT CHECK AND ENTER
	if (angle_II >= 0 && angle_II < 90)//QUADRANT 1
	{
		//THIS MEANS WE ONLY DEAL WITH X AXIS - Y AXIS MUST BE ZERO
		if (angle_II == 0)
		{
			//ROCKET SPAWN POINT
			rocketSpawnPoint.x = position.x + rocketSpawnGap;
			rocketSpawnPoint.y = position.y;
		}
		else//WE FIND OUR POINTS IN THE 1ST QUADRANT
		{
			//ROCKET SPAWN POINT
			rocketSpawnPoint.x = position.x + (rocketSpawnGap * (cos(angle_II * 3.14 / 180)));
			rocketSpawnPoint.y = position.y - (rocketSpawnGap * (sin(angle_II * 3.14 / 180)));
		}
	}
	else if (angle_II >= 90 && angle_II <= 180)//QUADRANT 2
	{
		if (angle_II == 90)
		{
			//ROCKET SPAWN POINT
			rocketSpawnPoint.x = position.x;
			rocketSpawnPoint.y = position.y - rocketSpawnGap;
		}
		else if (angle_II == 180)
		{
			//ROCKET SPAWN POINT
			rocketSpawnPoint.x = position.x - rocketSpawnGap;
			rocketSpawnPoint.y = position.y;
		}
		else
		{
			//ROCKET SPAWN POINT
			rocketSpawnPoint.x = position.x - (rocketSpawnGap * (cos((180 - angle_II) * 3.14 / 180)));
			rocketSpawnPoint.y = position.y - (rocketSpawnGap * (sin((180 - angle_II) * 3.14 / 180)));
		}
	}
	else if (angle_II < -90 && angle_II >= -180)//QUADRANT 3
	{
		if (angle_II == -180)
		{
			//BULLET SPAWN POINT
			rocketSpawnPoint.x = position.x - rocketSpawnGap;
			rocketSpawnPoint.y = position.y;
		}
		else
		{
			//BULLET SPAWN POINT
			rocketSpawnPoint.x = position.x - (rocketSpawnGap * (cos((180 + angle_II) * 3.14 / 180)));
			rocketSpawnPoint.y = position.y + (rocketSpawnGap * (sin((180 + angle_II) * 3.14 / 180)));
		}
	}
	else if (angle_II < 0 && angle_II >= -90)//QUADRANT 4
	{
		if (angle_II == -90)
		{
			//BULLET SPAWN POINT
			rocketSpawnPoint.x = position.x;
			rocketSpawnPoint.y = position.y + rocketSpawnGap;
		}
		else
		{
			//BULLET SPAWN POINT
			rocketSpawnPoint.x = position.x + (rocketSpawnGap * (cos(fabs(angle_II) * 3.14 / 180)));
			rocketSpawnPoint.y = position.y + (rocketSpawnGap * (sin(fabs(angle_II) * 3.14 / 180)));
		}
	}
	else//ERROR JUST DEFAULT NOTHING
	{
		physicsBody->setVelocity(Vec2(0, 0));
	}

	rocketVelocityPoint.x = 3*(-(getPosition().x - target->getPosition().x));
	rocketVelocityPoint.y = 3*(-(getPosition().y - target->getPosition().y));

	float opp = -(getPosition().y - target->getPosition().y);
	float adj = -(getPosition().x - target->getPosition().x);

 	angle_I = -(std::atan2(opp, adj)  * (180.0 / 3.14));

	CCLOG("Angle I : %f", std::atan2(1, 1)  * (180.0 / 3.14));
	CCLOG("Angle I : %f", std::atan2(1, 2)  * (180.0 / 3.14));
	CCLOG("Angle I : %f", std::atan2(2, 1)  * (180.0 / 3.14));
	CCLOG("Angle I : %f", std::atan2(1, 0)  * (180.0 / 3.14));


	CCLOG("Angle I : %f", angle_I);
}
cocos2d::Vec2 Vehicle::getRocketSpawnPoint()
{
	return rocketSpawnPoint;//GET ROCKET SPAWN POINT
}
cocos2d::Vec2 Vehicle::getRocketVelocityPoint()
{
	return rocketVelocityPoint;//GET ROCKET VELOCITY POINT
}

//GET SPRITE AND PHYSICS BODY OBJECT POINTER
cocos2d::Sprite* Vehicle::getSprite()
{
	return sprite;//GET SPRITE OBJECT POINTER
}
cocos2d::PhysicsBody* Vehicle::getPhysicsBody()
{
	return physicsBody;//GET PHYSICS OBJECT POINTER
}
cocos2d::Node* Vehicle::getParent()
{
	
	return sprite->getParent();
}

//GET - SET VEHICLE SPEED FUNCTIONS
void Vehicle::accelerate()
{
	if (slowDown) slowDown = false;

	if (m_speed < 300) m_speed++;
}
void Vehicle::brake()
{
	if (m_speed < 0) m_speed = 0;
	else if (m_speed >= 10) m_speed -= 10;
	else if (m_speed < 10) m_speed = 0;
}
float Vehicle::getSpeed()
{
	return m_speed;
}
void Vehicle::setSpeed(float speed)
{
	m_speed = speed;
}
bool Vehicle::getSlowDownStatus()
{
	return slowDown;
}
void Vehicle::setSlowDownStatus(bool status)
{
	slowDown = status;
}
void Vehicle::VelocityDamping()
{
	//IF THE THE PLAYER HAS LET GO OF THE ACCELERATE KEY (UP KEY) THEN VEHICLE WILL START TO SLOW DOWN
	if (m_speed > 0)//IF SPEED IS MORE THAN ZERO
		m_speed--;//REDUCE SPEED
}
void Vehicle::setDriveOFF()
{
	driveStatus = false;
}
void Vehicle::setDriveON()
{
	driveStatus = true;
}
bool Vehicle::getActiveStatus()
{
	return driveStatus;
}

//WEAPONS FUNCTIONS
std::string Vehicle::getWeapon()
{
	if (trusterStatus == true)
	{
		weaponStatus = "Truster";
	}
	else if (mineStatus == true)
	{
		weaponStatus = "Mine";
	}
	else if (rocketStatus == true)
	{
		weaponStatus = "Rocket";
	}
	else if (machineGunStatus == true)
	{
		weaponStatus = "Machine Gun";
	}
	else if (shieldStatus == true)
	{
		weaponStatus = "Shield";
	}
	else
	{
		weaponStatus = "Empty";
	}

	return weaponStatus;
}
void Vehicle::setRocketStatus(bool status)
{
	rocketStatus = status;
}
bool Vehicle::getRocketStatus()
{
	return rocketStatus;
}
void Vehicle::setMineStatus(bool status)
{
	mineStatus = status;
}
bool Vehicle::getMineStatus()
{
	return mineStatus;
}
void Vehicle::setMachineGunStatus(bool status)
{
	if(status)
		bullets = 10;

	machineGunStatus = status;
}
bool Vehicle::getMachineGunStatus()
{
	return machineGunStatus;
}
void Vehicle::setShieldStatus(bool status)
{
	shieldStatus = status;
}
bool Vehicle::getShieldStatus()
{
	return shieldStatus;
}
void Vehicle::setTrusterStatus(bool status)
{
	trusterStatus = status;
}
bool Vehicle::getTrusterStatus()
{
	return trusterStatus;
}
Rocket* Vehicle::fireRocket(cocos2d::Sprite* target, bool lockOn)
{
	Rocket* rocket = new Rocket();
	setRocketPoints(target);
	float distance = std::sqrt(std::pow((target->getPosition().x - getPosition().x), 2) + std::pow((target->getPosition().y - getPosition().y), 2));
	if (distance < 300)
	{
		CCLOG("Distance Less Than 300 - %f", distance);
		rocket->getSprite()->setPosition(rocketSpawnPoint);
		rocket->getSprite()->setRotation(angle_I);
		rocket->getPhysicsBody()->setVelocity(rocketVelocityPoint);
		rocketStatus = false;
		return rocket;
	}
	else
	{
		CCLOG("Distance More Than 200 - %f", distance);
		return NULL;
	}
}
LandMine* Vehicle::layMine()
{
	LandMine* mine = new LandMine();
	mine->getSprite()->setPosition(sprite->getPosition());
	mine->animate();
	mineStatus = false;
	return mine;
}
Bullet* Vehicle::fireMachineGun()
{
	if (bullets > 0)
	{
		CCLOG("Machine Gun Fired");
		Bullet* bullet = new Bullet();
		setMachineGunPoints();//SET VELOCITY & SPAWN POINTS
		bullet->getSprite()->setPosition(bulletSpawnPoint);
		bullet->getSprite()->setRotation(sprite->getRotation());
		bullet->getPhysicsBody()->setVelocity(bulletFirePoint);
		CCLOG("Bullets Left : %d\n", bullets);
		bullets--;
		return bullet;
	}
	else
	{
		machineGunStatus = false;
		return NULL;
	}
}
void Vehicle::deployShield()
{
	shieldStatus = false;
	auto angle = sprite->getRotation();
	auto velocity = physicsBody->getVelocity();
	sprite->removeComponent(physicsBody);

	mArray[0] = cocos2d::Vec2(-30 / TIscale, -13 / TIscale);
	mArray[1] = cocos2d::Vec2(-36 / TIscale, -9 / TIscale);
	mArray[2] = cocos2d::Vec2(-40 / TIscale, -2 / TIscale);
	mArray[3] = cocos2d::Vec2(-40 / TIscale, 2 / TIscale);
	mArray[4] = cocos2d::Vec2(-36 / TIscale, 9 / TIscale);
	mArray[5] = cocos2d::Vec2(-30 / TIscale, 13 / TIscale);
	mArray[6] = cocos2d::Vec2(40 / TIscale, 12 / TIscale);
	mArray[7] = cocos2d::Vec2(47 / TIscale, 7 / TIscale);
	mArray[8] = cocos2d::Vec2(50 / TIscale, 2 / TIscale);
	mArray[9] = cocos2d::Vec2(50 / TIscale, -2 / TIscale);
	mArray[10] = cocos2d::Vec2(47 / TIscale, -7 / TIscale);
	mArray[11] = cocos2d::Vec2(40 / TIscale, -12 / TIscale);
	mArray[12] = cocos2d::Vec2(-30 / TIscale, -13 / TIscale);
	physicsBody = PhysicsBody::createPolygon(mArray, 13, PhysicsMaterial(0.5, 0.5, 0.5));
	physicsBody->setCollisionBitmask(4);
	physicsBody->setContactTestBitmask(true);
	physicsBody->setAngularDamping(10);
	physicsBody->setDynamic(true);

	sprite->setRotation(0);
	sprite->addComponent(physicsBody);
	sprite->setRotation(angle);

	sprite->setTexture("Ship/VehicleOne/vehicleOneShield.png");

	physicsBody->setVelocity(velocity);
}
void Vehicle::terminateShield()
{
	//VEHICLE SPRITE WITH SHIELD
	auto angle = sprite->getRotation();
	auto velocity = physicsBody->getVelocity();
	sprite->removeComponent(physicsBody);
	mArray[0] = cocos2d::Vec2(-26 / TIscale, -3 / TIscale);
	mArray[1] = cocos2d::Vec2(-22 / TIscale, -6 / TIscale);
	mArray[2] = cocos2d::Vec2(35 / TIscale, -3 / TIscale);
	mArray[3] = cocos2d::Vec2(37 / TIscale, -1 / TIscale);
	mArray[4] = cocos2d::Vec2(37 / TIscale, 1 / TIscale);
	mArray[5] = cocos2d::Vec2(35 / TIscale, 3 / TIscale);
	mArray[6] = cocos2d::Vec2(-22 / TIscale, 6 / TIscale);
	mArray[7] = cocos2d::Vec2(-26 / TIscale, 3 / TIscale);
	mArray[8] = cocos2d::Vec2(-26 / TIscale, -3 / TIscale);
	physicsBody = PhysicsBody::createPolygon(mArray, 9, PhysicsMaterial(1, 0, 0));
	physicsBody->setCollisionBitmask(4);
	physicsBody->setContactTestBitmask(true);
	physicsBody->setAngularDamping(10);
	physicsBody->setDynamic(true);

	sprite->setRotation(0);
	sprite->addComponent(physicsBody);
	sprite->setRotation(angle);
	if (m_speed > 0) {sprite->setTexture("Ship/VehicleOne/driveSingle.png");}
	else {sprite->setTexture("Ship/VehicleOne/idleSingle.png");}
	physicsBody->setVelocity(velocity);
}
void Vehicle::endWeapon()//TERMINATE ALL WEAPON ABILITIES
{
	rocketStatus = false;
	machineGunStatus = false;
	trusterStatus = false;
	shieldStatus = false;
	mineStatus = false;
	terminateShield();
}
void Vehicle::truster()
{
	trusterStatus = false;
	m_speed = 500;
}
bool Vehicle::availableWeapon()
{
	if (getRocketStatus())
		return true;
	else if (getMineStatus())
		return true;
	else if (getMachineGunStatus())
		return true;
	else if (getTrusterStatus())
		return true;
	else if (getShieldStatus())
		return true;
	else
		return false;
}
int Vehicle::getHealth()
{
	return m_health;
}
void Vehicle::setDamage(std::string projectile)
{
	if (projectile == "rocket")
		m_health = m_health - 25;
	else if (projectile == "mine")
		m_health = m_health - 30;
	else if (projectile == "rocket")
		m_health = m_health - 10;

	if (m_health <= 0)
	{
		dead = true;
	}
}
void Vehicle::destroyVehicle()
{
	delete this;
}
bool Vehicle::isDead()
{
	return dead;
}

//GET - SET ANGLE AND POSITION
void Vehicle::setAngle(float angle)
{
	sprite->setRotation(angle);//SET SPRITE ACTUALY ANGLE
}
float Vehicle::getAngle()
{
	//GET SPRITE ANGLE
	angle_I = sprite->getRotation();

	//SORTING ANGLE SO ITS USABLE
	if (angle_I < 0)
	{
		angle_II = int(round(angle_I)) % -360;
	}
	else if (angle_I >= 0)
	{
		angle_II = int(round(angle_I)) % 360;
	}
	else if (angle_I == -0)
	{
		angle_II = 0;
	}

	//FIX OUT OF BOUNDS (ABOVE 180 OR BELOW -180)
	if (angle_II > 180)
	{
		angle_II = (float(int(angle_II) % 180)) + (-180);
	}
	else if (angle_II < -180)
	{
		angle_II = float(((int(angle_II) % -180)) + (180));
	}

	return angle_II;//RETURN TRANSFORMED ANGLE(FLIPPED)
}
cocos2d::Vec2 Vehicle::getPosition()
{
	return sprite->getPosition();
}
void Vehicle::setPosition(cocos2d::Vec2 pos)
{
	position.x = pos.x;
	position.y = pos.y;
	sprite->setPosition(position);
}
void Vehicle::turnLeft()
{
	sprite->setRotation(sprite->getRotation() - steeringPower);
}
void Vehicle::turnRight()
{
	sprite->setRotation(sprite->getRotation() + steeringPower);
}

//CHANGE AI ANGLE TOWARDS CURRENT WAYPOINT
void Vehicle::autoControlAI(cocos2d::Vec2 destination)
{
	if (autoDrive)
	{
		//GTE POSITION
		position = sprite->getPosition();

		//SET VEHICLE VELOCITY
		float opp = destination.y - position.y;//Y VALUE
		float adj = destination.x - position.x;//X VALUE

											   //AI DRIVE TOWARDS NEXT WAY POINT TRIGONOMETRY

		if (opp >= 0 && adj > 0)//QUADRANT IV
		{
			angle_III = atan2(adj, opp) * (180.0 / 3.14);
			angle_III = -(-(angle_III)+90);
		}
		else if (opp > 0 && adj <= 0)//QUADRANT III
		{
			angle_III = atan2(adj, opp) * (180.0 / 3.14);
			angle_III = -(-(angle_III)+90);
		}
		else if (opp <= 0 && adj < 0)//QUADRANT II
		{
			angle_III = atan2(adj, opp) * (180.0 / 3.14);
			angle_III = 180 + (angle_III + 90);
		}
		else if (opp < 0 && adj > 0)//QUADRANT I
		{
			angle_III = atan2(adj, opp) * (180.0 / 3.14);
			angle_III = angle_III - 90;
		}

		//FIX OUT OF ANGLE ISSUE - RANGE is 180 to -180
		if (angle_III < -180)
		{
			angle_III = 180 - (int(angle_III) % 180);
		}
		else if (angle_III > 180)
		{
			angle_III = 180 - (int(angle_III) % 180);
		}

		//GET OUR TRANSFORMED ANGLE
		angle_II = getAngle();

		//ROTATE TOWARDS WAY POINT
		if (angle_III > angle_II)
		{
			if (angle_III >= 0 && angle_II >= 0)
			{
				if ((angle_III - 3) <= angle_II)
				{
					angle_II = angle_III;
					sprite->setRotation(angle_II);
				}
				else
					sprite->setRotation(angle_II + steeringPower);
			}
			else if (angle_III < 0 && angle_II < 0)
			{
				if ((angle_III - 3) <= angle_II)
				{
					angle_II = angle_III;
					sprite->setRotation(angle_II);
				}
				else
					sprite->setRotation(angle_II + steeringPower);
			}
			else if (angle_III >= 0 && angle_II < 0)
			{
				if ((angle_III > 177 && angle_II < -179) || (angle_III > 178 && angle_II < -178) || (angle_III > 179 && angle_II < -177))
				{
					angle_II = angle_III;
				}
				else if ((fabs(angle_III) + fabs(angle_II)) <= 180)
					sprite->setRotation(angle_II + steeringPower);
				else if ((fabs(angle_III) + fabs(angle_II)) > 180)
					sprite->setRotation(angle_II - steeringPower);
			}
		}
		else if (angle_III < angle_II)
		{
			if (angle_III < 0 && angle_II < 0)
			{
				if ((angle_III + 3) >= angle_II)
				{
					angle_II = angle_III;
					sprite->setRotation(angle_II);
				}
				else
					sprite->setRotation(angle_II - steeringPower);
			}
			else if (angle_III >= 0 && angle_II >= 0)
			{
				if ((angle_III + 3) >= angle_II)
				{
					angle_II = angle_III;
					sprite->setRotation(angle_II);
				}
				else
					sprite->setRotation(angle_II - steeringPower);
			}
			else if (angle_III < 0 && angle_II >= 0)
			{
				if ((angle_III < -177 && angle_II > 179) || (angle_III < -178 && angle_II > 178) || (angle_III < -179 && angle_II > 177))
				{
					angle_II = angle_III;
				}
				else if ((fabs(angle_III) + fabs(angle_II)) <= 180)
					sprite->setRotation(angle_II - steeringPower);
				else if ((fabs(angle_III) + fabs(angle_II)) > 180)
					sprite->setRotation(angle_II + steeringPower);
			}
		}
	}
}
void Vehicle::setAutoControl(bool status)
{
	autoDrive = status;
}
bool Vehicle::getAutoControl()
{
	return autoDrive;
}
bool Vehicle::wayPointCollision(cocos2d::Sprite* wayPointSprite)
{
	//CHECK IF VEHICLE HAS COLLIDED WITH NEXT WAYPOINT
	cocos2d::Rect rect1 = sprite->getBoundingBox();
	cocos2d::Rect rect2 = wayPointSprite->getBoundingBox();
	if (rect1.intersectsRect(rect2))
	{
		return true;
	}
}

//SET STEERING POWER OF VEHICLE (HOW WELL THEY CAN TURN)
void Vehicle::setSteeringPower(float power)
{
	steeringPower = power;
}

//DECIDES HOW TIGHT THE AI CUTS INTO CORNERS
void Vehicle::setCornering(int status)
{
	switch (status)
	{
	case 1:cornering = 0;
		break;
	case 2:cornering = 1;
		break;
	case 3:cornering = 2;
		break;
	default:cornering = 1;
		break;
	}
}

//RETURNS HOW TIGHT THE AI CUTS INTO CORNERS
int Vehicle::getCornering()
{
	return cornering;
}
cocos2d::Vec2 Vehicle::getCurrentWayPoint()
{
	return currentWayPoint;
}
void Vehicle::setCurrentWayPoint(cocos2d::Vec2 wayPoint)
{
	currentWayPoint = wayPoint;
}
int Vehicle::getWayPointCounter()
{
	return wayPointCount;
}
void Vehicle::setWayPointCounter(int counter)
{
	wayPointCount = counter;
}
cocos2d::Sprite* Vehicle::returnWayPointSprite()
{
	return wayPointSprite;

}
void Vehicle::moveWayPointSprite(cocos2d::Vec2 position)
{
	wayPointSprite->setPosition(position);
}

//AUTO PILOT ABILITY - CURRENTLY DEVELOPING
void Vehicle::autoControlPlayer(std::vector<cocos2d::Vec2> wayPointVectors)
{

}

//ANIMATION CONTROL
void Vehicle::anim_drive()
{
	animationFramesII.clear();
	for (int i = 0; i < 2; i++)
	{
		auto frame = SpriteFrame::create("Ship/VehicleOne/drive.png", Rect(90 * i / TIscale, 0 / TIscale, 90 / TIscale, 30 / TIscale));
		animationFramesII.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(animationFramesII, 0.1f);
	auto animate = Animate::create(animation);
	sprite->runAction(RepeatForever::create(animate));
}
void Vehicle::anim_accelerate()//ACCELERATE
{
		animationFramesI.clear();
		for (int i = 0; i < 6; i++)
		{
			auto frame = SpriteFrame::create("Ship/VehicleOne/accelerate.png", Rect(90 * i / TIscale, 0 / TIscale, 90 / TIscale, 30 / TIscale));
			animationFramesI.pushBack(frame);
		}
		auto animation = Animation::createWithSpriteFrames(animationFramesI, 0.1f);
		auto animate = Animate::create(animation);
		sprite->runAction(CCSequence::create(cocos2d::Repeat::create(animate, 1), Repeat::create(animate, 1), CallFunc::create([this]() { anim_drive(); }), NULL));
}
void Vehicle::anim_shield()//Deploy Shield
{
	animationFramesI.clear();
	for (int i = 0; i < 1; i++)
	{
		auto frame = SpriteFrame::create("Ship/VehicleOne/vehicleOneShield.png", Rect(90 * i / TIscale, 0 / TIscale, 90 / TIscale, 30 / TIscale));
		animationFramesI.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(animationFramesI, 0.01f);
	auto animate = Animate::create(animation);
	sprite->runAction(cocos2d::Repeat::create(animate, 1));
}
void Vehicle::setType(std::string type)
{
	mType = type;
}
std::string Vehicle::getType()
{
	return mType;
}
void Vehicle::anim_idle()
{
	animationFramesII.clear();
	for (int i = 0; i < 4; i++)
	{
		auto frame = SpriteFrame::create("Ship/VehicleOne/idle.png", Rect(90 * i / TIscale, 0 / TIscale, 90 / TIscale, 30 / TIscale));
		animationFramesII.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(animationFramesII, 0.1f);
	auto animate = Animate::create(animation);
	sprite->runAction(RepeatForever::create(animate));
}
void Vehicle::anim_de_accelerate()//DE-ACCELERATE
{
	animationFramesI.clear();
	for (int i = 0; i < 4; i++)
	{
		auto frame = SpriteFrame::create("Ship/VehicleOne/de_accelerate.png", Rect(90 * i / TIscale, 0 / TIscale, 90 / TIscale, 30 / TIscale));
		animationFramesI.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(animationFramesI, 0.1f);
	auto animate = Animate::create(animation);
	sprite->runAction(CCSequence::create(cocos2d::Repeat::create(animate, 1), Repeat::create(animate, 1), CallFunc::create([this]() { anim_idle(); }) , NULL));
}
bool Vehicle::getAccelerateLock()
{
	return accelerateLock;
}
bool Vehicle::getDe_AccelerateLock()
{
	return de_accelerateLock;
}
//OBJECT EXPODES ON CONTACT
void Vehicle::explode()
{
	animationFramesI.clear();
	for (int i = 0; i < 10; i++)
	{
		auto frame = cocos2d::SpriteFrame::create("Particles/explosionLarge.png", cocos2d::Rect(80 * i, 0 , 80 , 80 ));
		animationFramesI.pushBack(frame);
	}
	auto animation = cocos2d::Animation::createWithSpriteFrames(animationFramesI, 0.1f);
	auto animate = cocos2d::Animate::create(animation);
	sprite->runAction(cocos2d::CCSequence::create(cocos2d::Repeat::create(animate, 1), cocos2d::CallFunc::create([this]() { dead = true; }), NULL));
}