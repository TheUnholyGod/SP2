#ifndef _WOOD_H
#define _WOOD_H

#include "Resources.h"
class Wood :
	public Resources
{
public:
	Wood(Vector3 = (0, 0, 0));
	~Wood();
};

#endif