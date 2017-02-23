#ifndef _STONE_H
#define _STONE_H

#include "Resources.h"
class Stone :
	public Resources
{
public:
	Stone(Vector3 = (0, 0, 0));
	~Stone();
};

#endif