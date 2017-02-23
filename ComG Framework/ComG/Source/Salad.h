#ifndef _SALAD_H
#define _SALAD_H

#include "Food.h"
class Salad :
	public Food
{
public:
	Salad(Vector3 = (0, 0, 0));
	~Salad();

	virtual void Eat();
};

#endif