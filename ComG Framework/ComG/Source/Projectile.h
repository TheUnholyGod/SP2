#ifndef _PROJECTILES_H
#define _PROJECTILES_H

#include "Item.h"
#include "Collision.h"
#include "Vector3.h"
#include "Application.h"

class Projectile :public Item
{
private:
	bool fired;
	Vector3 position_;//traack movement
	Vector3 defaultposition_;//pos before fire
	double proj_speed_;
	float attack_dmg_;
	float range_;
public:
	Projectile();
	~Projectile();
	void FireProjectile(Vector3 forward, double dt);
	bool hit();
	void update(Vector3 pos, Vector3 forward, double dt);
};

#endif
