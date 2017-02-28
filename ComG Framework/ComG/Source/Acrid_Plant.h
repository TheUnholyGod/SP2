#ifndef _ACRID_PLANT_H
#define _ACRID_PLANT_H

#include "Enemy.h"
#include "Player.h"
#include "Projectile.h"
class Acrid_Plant : public Enemy
{
public:
	Acrid_Plant();
	~Acrid_Plant();

	static std::vector<Projectile*> acidProjectile;
	void Update(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy);

	std::clock_t shootStart;
	float elapsed;
};

#endif