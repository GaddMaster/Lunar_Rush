#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include "cocos2d.h"
#include "Bullet.h"
#include "LandMine.h"
#include "Rocket.h"
#include "Vehicle.h"

class Vehicle
{
	public://////////////////////////////////////////////////////////////

		//CONSTRUCTOR & DE-CONSTRUCTOR
		Vehicle();
		~Vehicle();

		//SET POINTS/GET POINTS - VELOCITY - WEAPONS SPAWN - WEAPON VELOCITY
		void setVelocityPoint();
		cocos2d::Vec2 getVelocityPoint();
		void setVelocity();

		void setMachineGunPoints();
		cocos2d::Vec2 getBulletSpawnPoint();
		cocos2d::Vec2 getBulletVelocityPoint();

		void setRocketPoints(cocos2d::Sprite* target);
		cocos2d::Vec2 getRocketSpawnPoint();
		cocos2d::Vec2 getRocketVelocityPoint();

		//GET SPRITE AND PHYSICS BODY
		cocos2d::Sprite* getSprite();
		cocos2d::PhysicsBody* getPhysicsBody();
		cocos2d::Node* getParent();

		//DRIVING, SPEED, VELOCITY DAMPING, DRIVE STATUS
		void accelerate();
		void brake();
		float getSpeed();
		void setSpeed(float speed);
		bool getSlowDownStatus();
		void setSlowDownStatus(bool status);
		void VelocityDamping();
		void setDriveOFF();
		void setDriveON();
		bool getActiveStatus();

		//WEAPONS USE & WEAPONS CALCULATIONS
		std::string getWeapon();
		void setRocketStatus(bool status);
		bool getRocketStatus();
		void setMineStatus(bool status);
		bool getMineStatus();
		void setMachineGunStatus(bool status);
		bool getMachineGunStatus();
		void setShieldStatus(bool status);
		bool getShieldStatus();
		void setTrusterStatus(bool status);
		bool getTrusterStatus();
		Rocket* fireRocket(cocos2d::Sprite* target, bool lockOn);
		LandMine* layMine();
		Bullet* fireMachineGun();
		void deployShield();
		void terminateShield();
		void endWeapon();
		void truster();
		bool availableWeapon();//RETURN TRUE IF ANY AVAILABLE WEAPON 
		void setDamage(std::string projectile);
		int getHealth();
		void destroyVehicle();

		//ANGLE, POSITION - GET - SET 
		void setAngle(float angle);
		float getAngle();
		cocos2d::Vec2 getPosition();
		void setPosition(cocos2d::Vec2 pos);
		void turnLeft();
		void turnRight();

		//AUTO CONTROL - AI - PLAYER AUTO PILOT ABILITY
		void autoControlPlayer(std::vector<cocos2d::Vec2> wayPointVectors);
		void autoControlAI(cocos2d::Vec2 destination);
		void setAutoControl(bool status);
		bool getAutoControl();
		bool wayPointCollision(cocos2d::Sprite* wayPointSprite);
		void setSteeringPower(float power);
		void setCornering(int status);
		int getCornering();

		//ANIMATIONS
		void anim_drive();
		void anim_idle();
		void anim_accelerate();
		void anim_de_accelerate();
		bool getAccelerateLock();
		bool getDe_AccelerateLock();
		void anim_shield();
		void replaceSprite(const std::string& resourceName, int zIndex);

		//void replaceSprite(const std::string & resourceName, int zIndex);

	private://////////////////////////////////////////////////////////////

		//SPRITES
		cocos2d::Sprite* sprite;
		cocos2d::Sprite* spriteShield;
		cocos2d::PhysicsBody* physicsBody;
		cocos2d::PhysicsBody* physicsBodyShield;
		cocos2d::Sprite* bulletSprite;
		cocos2d::PhysicsBody* bulletPhysicsBody;

		//VELOCITY, SPAWN POINTS
		cocos2d::Vec2 velocityPoint;
		cocos2d::Vec2 bulletSpawnPoint;
		cocos2d::Vec2 bulletFirePoint;
		cocos2d::Vec2 position;
		cocos2d::Vec2 rocketVelocityPoint;
		cocos2d::Vec2 rocketSpawnPoint;

		//ANGLES USED FOR TRIGONOMETRY CALCULATIONS
		float angle_I;//ACTUAL SPRITE ANGLE
		float angle_II;//TRANSFORMED ANGLE FOR EASE OF USE(FLIPPED)
		float angle_III;//WAY POINT ANGLE

		//VARIOUS USEFUL VARIABLES AND BOOLEANS
		bool slowDown;
		float m_speed;
		int driveOffTimer;
		float TIscale = 1.71;
		bool trusterStatus;
		bool rocketStatus;
		bool machineGunStatus;
		float machineGunVelocity;
		float rocketSpeed;
		float machineGunSpawnGap;
		bool shieldStatus;
		int shieldLock;
		bool mineStatus;
		bool driveStatus;
		bool autoDrive;
		float TIScale;
		float steeringPower;
		int cornering;
		int m_health;
		int bullets;
		bool accelerateLock;
		bool de_accelerateLock;
		bool wayPointCounter;
		std::string weaponStatus;

		cocos2d::Vector<cocos2d::SpriteFrame*> animationFramesI;
		cocos2d::Vector<cocos2d::SpriteFrame*> animationFramesII;
		cocos2d::Vec2 mArray[9];//CHILD CLASSES COULD USE LESS - BUT ENOUGH GIVEN FOR ALL 
		cocos2d::Vec2 shieldArray[13];
};

#endif

