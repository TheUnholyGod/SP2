#ifndef _CARROTJUICE_H
#define _CARROTJUICE_H

#include "Food.h"

class CarrotJuice : public Food
{
public:
	CarrotJuice(Vector3 = (0, 0, 0));
	~CarrotJuice();

	virtual void Eat();
};

#endif