//SAMANTHA MARAH
//K0020078 

#ifndef AMMO_H
#define AMMO_H

class Ammo
{
public:
	void ammo_number(int number_id);
	virtual void set_number_id();
	int get_number_id();

	int m_number_id;
};

#endif
