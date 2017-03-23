//SAMANTHA MARAH
//K00200782

//Inclues The PickUps Header File
#include "PickUps.h"

USING_NS_CC;

//PickUps Constructor
PickUps::PickUps()
{};

//Pickups Destructor
PickUps::~PickUps()
{};

//PickUps setID Function
//A Virtual Function That Will Be Used To Give Each Instance Of That Object An ID
//This Will Be Used To Assign A Type Of Weapon Or Shield
//To An Instance Of The WeaponShieldPickup Object Dependent
//On Its ID
void PickUps::setID(int id)
{
	m_ID = id;
};

//FOR DEBUGGING
void PickUps::seeID()
{
	m_ID;
};

//PickUps getID Function
//A Function That Will Return The ID Being Used
//For Each Instance Of The WeaponShieldPickup Object.
int PickUps::getID()
{
	return m_ID;
};