#ifndef _LIZARD_H
#define _LIZARD_H

#include "Enemy.h"
#include "Player.h"

class Lizard : public Enemy
{
public:
	Lizard();
	~Lizard();
	void Update(double dt);
};

#endif