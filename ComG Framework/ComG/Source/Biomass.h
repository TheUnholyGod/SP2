#ifndef _BIOMASS_H
#define _BIOMASS_H

#include "Resources.h"
class Biomass :
	public Resources
{
public:
	Biomass(Vector3 = (0, 0, 0));
	~Biomass();
};

#endif