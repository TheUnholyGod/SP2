#ifndef _COLLISION_H
#define _COLLISION_H

#include "Vector3.h"

class AABB
{
private:
	Vector3 max;
	Vector3 min;
	Vector3 defaultmax;
	Vector3 defaultmin;
	Vector3 position;
	Vector3 defaultposition;

public:
	AABB(Vector3, Vector3);
	~AABB();
	void setMinMax(Vector3);
	void reset();
	bool pointtoAABB(Vector3 pos);
	bool AABBtoAABB(AABB box);
};

#endif