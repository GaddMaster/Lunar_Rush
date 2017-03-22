//SAMANTHA MARAH
//K00200782

#ifndef PICKUPS_H
#define PICKUPS_H

//Includes The COCOS2D-X Libraries Into This Header File
#include "cocos2d.h"

//PickUps Class That Will Be Inherited By The Following:
//-HealthPickup Class
//-ThrusterPickup Class
//WeaponShieldPickup Class
class PickUps
{
public:
	//PickUps getSprite Function
	//A Virtual Function That Will Return The Sprites Being Used
	//For The Different Objects
	virtual cocos2d::Sprite* getSprite() = 0;

	//PickUps getPhysicsBody Function
	//A Virtual Function That Will Return The PhysicsBodies Being Used
	//For The Different Objects
	virtual cocos2d::PhysicsBody* getPhysicsBody() = 0;

	//PickUps rotate Function
	//A Virtual Function That Will Rotate The Objects Being Used
	virtual void rotate() = 0;

	//PickUps setID Function
	//A Virtual Function That Will Be Used To Give Each Instance Of That Object An ID
	//This Will Be Used To Assign A Type Of Weapon Or Shield
	//To An Instance Of The WeaponShieldPickup Object Dependent
	//On Its ID
	virtual void setID(int id);

	//FOR DEBUGGING
	virtual void seeID();

	//PickUps getID Function
	//A Function That Will Return The ID Being Used
	//For Each Instance Of The WeaponShieldPickup Object.
	virtual int getID();

protected:
	//PickUps Constructor
	PickUps();

	//Pickups Destructor
	virtual ~PickUps();

	//Variables That Can Be Used In The
	//Classes Inheriting The PickUp Class Only
	cocos2d::Sprite* sprite;
	cocos2d::PhysicsBody* physicsBody;
	int m_ID;
};

#endif
