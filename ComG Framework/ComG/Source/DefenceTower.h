#ifndef DEFENCETOWER_H
#define DEFENCETOWER_H

#include "Building.h"
#include "Collision.h"
#include "Enemy.h"
#include <string>

class DefenceTower : public Building
{
protected:
	const std::string kName_;
	std::string source_location_;
	int health_;
	bool enter_;
	static Vector3 s_position;
	static Vector3 s_forward;
	static AABB* aoe;
	static std::list<Enemy*> enemiesInRange;
public:
	DefenceTower(Vector3=(0,0,5));
	virtual ~DefenceTower();

	int get_Health();

	virtual void update(double dt);
	static void turretTargetUpdate(std::vector<Enemy*> enemies);
};

#endif