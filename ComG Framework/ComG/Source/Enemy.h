#ifndef _ENEMY_H
#define _ENEMY_H

#include "Ability.h"
#include "GameObject.h"
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
	const std::list<Ability*> Abilities;
	const std::string kname_;	//Name of Object
public:
	Enemy(int, std::string, std::string, std::string, ENEMYTYPE, std::string, float, float, float);
	virtual ~Enemy();
	virtual void Update(double dt) {}
	const std::string getName() { return kname_; }
	void takeDamage(int dmg) { health_ -= (int)(dmg); if (health_ < 0) { health_ = 0; } std::cout << health_ << std::endl; }
	bool isDead() { if (!health_) return true; else return false; }
};

#endif