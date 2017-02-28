#include "Collision.h"
#include "Utility.h"
#include <math.h>

AABB::AABB(Vector3 size, Vector3 pos) :size(size)
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

void AABB::resizeAABB(Vector3 size)
{
	max = defaultmax = size * (0.5, 0.5, 0.5) + defaultposition;
	min = defaultmin = defaultposition - size * (0.5, 0.5, 0.5);
}

void AABB::reset()
{
	max = defaultmax;
	min = defaultmin;
}

bool AABB::pointtoAABB(Vector3 pos,Vector3 forward)
{
	//returna true when in bounds
	return (pos.x + forward.x < max.x && pos.x + forward.x > min.x) && (pos.y + forward.y < max.y && pos.y + forward.y > min.y) && (pos.z + forward.z < max.z && pos.z + forward.z > min.z);
}

bool AABB::AABBtoAABB(AABB box)
{
	return ((this->min.x <= box.max.x && this->max.x >= box.min.x) && (this->min.y <= box.max.y && this->max.y >= box.min.y) && (this->min.z <= box.max.z && this->max.z >= box.min.z));
}