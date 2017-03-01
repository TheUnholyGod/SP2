#ifndef _ANT_HILL_H
#define _ANT_HILL_H

#include "Enemy.h"
class Ant_Hill : public Enemy
{
	std::vector<Enemy*> hills;
public:
	Ant_Hill();
	~Ant_Hill();
	void Update(double dt) {}
	std::vector<Enemy*> getHills() { return hills; }
};

#endif