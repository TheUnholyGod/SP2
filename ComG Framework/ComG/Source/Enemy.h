#ifndef _ENEMY_H
#define _ENEMY_H

#include "GameObject.h"
#include "Ability.h"
#include <string>
#include <list>

class Enemy : public GameObject
{
protected:
	enum ENEMYTYPE
	{
		NORMAL,
		BOSS,
	}TYPE;
	std::string location_;	//Location of Enemy
	float health_;			//Enemy HP
	float defence_;			//Enemy Armour
	float attack_;			//Enemy Damage
	const std::list<Ability*> Abilities; //Enemy Abilities
	const std::string kname_;	//Name of Object
public:
	Enemy(int, std::string, ENEMYTYPE, std::string, float, float, float);
	virtual ~Enemy();

	const std::string getName() { return kname_; }
};

#endif