#ifndef _WEAPON_H
#define _WEAPON_H

#include "Item.h"

class Weapon : public Item
{
public:
	Weapon();
	~Weapon();
private:
	float attack;
	float Durability;
};

#endif