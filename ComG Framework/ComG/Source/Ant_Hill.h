#ifndef _ANT_HILL_H
#define _ANT_HILL_H

#include "Enemy.h"
class Ant_Hill : public Enemy
{
public:
	Ant_Hill();
	~Ant_Hill();
	void Update(double dt) {}
};

#endif