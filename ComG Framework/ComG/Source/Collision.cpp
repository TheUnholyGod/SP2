#include "Collision.h"
#include "Utility.h"

AABB::AABB(Vector3 size, Vector3 pos)
{
	defaultposition = pos;
	max = defaultmax = size * (0.5, 0.5, 0.5) + pos;
	min = defaultmin = pos - size * (0.5, 0.5, 0.5);
}

AABB::~AABB()
{
	
}

void AABB::setMinMax(Vector3 pos)
{
	if (pos != defaultposition)
	{
		Vector3 diff = pos - defaultposition;
		max += diff;
		min += diff;
		defaultposition = pos;
	}
}

void AABB::reset()
{
	max = defaultmax;
	min = defaultmin;
}

bool AABB::pointtoAABB(Vector3 pos)
{
	return (pos.x <= max.x && pos.x >= min.x) && (pos.y <= max.y && pos.y >= min.y) && (pos.z <= max.z && pos.z >= min.z);
}

bool AABB::AABBtoAABB(AABB box)
{
	return (box.min.x <= max.x && box.max.x >= min.x) && (box.min.y <= max.y && box.max.y >= min.y) && (box.min.z <= max.z && box.max.z >= min.z);
}