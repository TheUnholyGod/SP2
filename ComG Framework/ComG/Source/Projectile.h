#ifndef _PROJECTILES_H
#define _PROJECTILES_H

#include "Item.h"
#include "Collision.h"
#include "Vector3.h"
#include "Application.h"

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
	bool hit();
	void update(double dt);
	bool toDelete() { return deletepls_; }
};

#endif
