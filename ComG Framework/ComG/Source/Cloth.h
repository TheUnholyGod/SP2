#ifndef _CLOTH_H
#define _CLOTH_H

#include "Resources.h"
class Cloth :
	public Resources
{
public:
	Cloth(Vector3 = (0, 0, 0));
	~Cloth();
};

#endif