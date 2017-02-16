#ifndef _GOAT_H
#define _GOAT_H

#include "Enemy.h"
class Goat : public Enemy
{
public:
	Goat();
	~Goat();
	void Update(double dt) {}
};

#endif