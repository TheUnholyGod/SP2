#ifndef ANT_H
#define ANT_H

#include "Enemy.h"
class Ant : public Enemy
{
public:
	Ant();
	~Ant();
	void Update(double dt) {}
};

#endif