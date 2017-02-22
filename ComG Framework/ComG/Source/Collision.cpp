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
	bool x = (std::fabs(this->position.x - box.position.x) <= (this->size.x + box.size.x));
	bool y = (std::fabs(this->position.y - box.position.y) <= (this->size.y + box.size.y));
	bool z = (std::fabs(this->position.z - box.position.z) <= (this->size.z + box.size.z));
	return x && y && z;
}