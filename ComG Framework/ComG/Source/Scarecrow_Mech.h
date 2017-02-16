#ifndef _SCARECROW_MECH_H
#define _SCARECROW_MECH_H

#include "Enemy.h"
class Scarecrow_Mech : public Enemy
{
public:
	Scarecrow_Mech();
	~Scarecrow_Mech();
	void Update(double dt) {}
};

#endif