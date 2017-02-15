#ifndef _RENDERER_H
#define _RENDERER_H

#include "Vector3.h"
#include "Mtx44.h"
#include <list>

class Renderer
{
private:
	Vector3 forward_, position_, up_, right_;
	Mtx44 rotation_, scaling_, translation_;
	float rotatemax;
	struct AABB
	{
		Vector3 Max, Min;
	};
	std::list<AABB> allAABB_;
public:
	Renderer();
	~Renderer();
	void translate(Vector3, double);
	Vector3 getForward() { return forward_; }
	Vector3 getRight() { return right_; }
	Vector3 getPosition() { return position_; }
	void rotate(Vector3, double, float);
	void setForward(Vector3 newforward) { this->forward_ = newforward; }
};

#endif