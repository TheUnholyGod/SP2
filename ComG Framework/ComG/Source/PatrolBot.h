#ifndef _PATROLBOT_H
#define _PATROLBOT_H

#include "Enemy.h"
class PatrolBot : public Enemy
{
public:
	PatrolBot();
	~PatrolBot();
	void Update(double dt) {}
};

#endif