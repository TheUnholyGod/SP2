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
	bool isAcid;
	double proj_speed_;
	float attack_dmg_;
	float range_;
	Vector3 defaultpos;
public:
	Projectile();
	~Projectile();
	void FireProjectile(Vector3 pos, Vector3 forward);
	void FireAcidProjectile(Vector3 pos, Vector3 forward);
	void setProjectilespeed(double speed){ proj_speed_ = speed; }
	bool hit(std::list<Building*>buildings, std::vector<Enemy*>enemies);
	void update(double dt, std::list<Building*>buildings, std::vector<Enemy*>enemies);
	bool toDelete() { return deletepls_; }
};

#endif
