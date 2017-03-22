//SAMANTHA MARAH
//K00200782

#include "PickUps.h"

USING_NS_CC;

//PickUps Constructor
PickUps::PickUps()
{};

//Pickups Destructor
PickUps::~PickUps()
{};

void PickUps::setID(int id)
{
	m_ID = id;
};

void PickUps::seeID()
{
	m_ID;
};

int PickUps::getID()
{
	return m_ID;
};