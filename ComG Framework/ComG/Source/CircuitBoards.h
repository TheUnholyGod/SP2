#ifndef _CIRCUITBOARD_H
#define _CIRCUITBOARD_H

#include "Resources.h"
class CircuitBoards :
	public Resources
{
public:
	CircuitBoards(Vector3 = (0, 0, 0));
	~CircuitBoards();
};

#endif