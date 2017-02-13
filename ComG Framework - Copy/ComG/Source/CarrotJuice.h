#ifndef _CARROTJUICE_H
#define _CARROTJUICE_H

#include "Food.h"

class CarrotJuice : public Food
{
public:
	CarrotJuice();
	~CarrotJuice();

	virtual void Eat();
};

#endif