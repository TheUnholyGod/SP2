#ifndef _WATER_H
#define _WATER_H

#include "Resources.h"
class Water :
	public Resources
{
public:
	Water(Vector3 = (0, 0, 0));
	~Water();
};

#endif