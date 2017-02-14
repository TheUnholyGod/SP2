#ifndef _RENDERER_H
#define _RENDERER_H

#include "Vector3.h"
#include "Mtx44.h"
#include <list>

class Renderer
{
private:
	Vector3 forward_, position_;
	Mtx44 rotation_, scaling_, translation_;
	struct AABB
	{
		Vector3 Max, Min;
	};
	std::list<AABB> allAABB_;
public:
	Renderer() {}
	~Renderer() {}
};

#endif