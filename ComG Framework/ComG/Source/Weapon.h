#ifndef _WEAPON_H
#define _WEAPON_H

#include "Item.h"
#include <string>

class Weapon : public Item
{
protected:
	enum WEAPONTYPE
	{
		MELEE,
		FIREARMS,
	}TYPE;

	const WEAPONTYPE kType_;
	float kattack_;
	float kdurability_;

public:
	Weapon(std::string, WEAPONTYPE, float atk, float dura_);
	~Weapon();
};

#endif