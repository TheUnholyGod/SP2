#ifndef _CENTIPEDE_H
#define _CENTIPEDE_H

#include "Enemy.h"
class Centipede : public Enemy
{
public:
	Centipede();
	~Centipede();
	void Update(double dt) {}
};

#endif