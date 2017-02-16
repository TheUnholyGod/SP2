#ifndef _DRONE_H
#define _DRONE_H

#include "Enemy.h"
class Drone : public Enemy
{
public:
	Drone();
	~Drone();
	void Update(double dt) {}
};

#endif