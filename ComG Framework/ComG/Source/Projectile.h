#ifndef _PROJECTILES_H
#define _PROJECTILES_H

#include "Item.h"
#include "Collision.h"
#include "Vector3.h"
#include "Application.h"
#include "Building.h"
#include "Enemy.h"

class Projectile :public Item
{
private:
	bool fired_;
	bool deletepls_;
	double proj_speed_;
	float attack_dmg_;
	float range_;
	Vector3 defaultpos;
public:
	Projectile();
	~Projectile();
	void FireProjectile();
	bool hit(std::list<Building*>buildings, std::list<Enemy*>enemies);
	void update(double dt, std::list<Building*>buildings, std::list<Enemy*>enemies);
	bool toDelete() { return deletepls_; }
};

#endif
