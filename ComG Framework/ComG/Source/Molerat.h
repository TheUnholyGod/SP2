#ifndef _MOLERAT_H
#define _MOLERAT_H

#include "Enemy.h"
#include "Building.h"
#include "Player.h"

class Molerat : public Enemy
{
private:
	Vector3 goal, newDIr;
	bool goalreached;
public:
	Molerat();
	~Molerat();
	void Update(double dt, std::list<Building*> Buildings, std::vector<Enemy*> Enemy) override;
	void pathfinding();
};

#endif