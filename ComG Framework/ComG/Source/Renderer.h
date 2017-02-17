#ifndef _RENDERER_H
#define _RENDERER_H

#include "Vector3.h"
#include "Mtx44.h"
#include <list>

class Renderer
{
private:
	Vector3 forward_, position_, up_, right_;
	Mtx44 matrix_;
	float rotatemax;
	//pls export tis
	struct AABB
	{
		Vector3 Max, Min;
	};
	std::list<AABB> allAABB_;
public:
	Renderer();
	Renderer(Vector3, Vector3);
	~Renderer();
	void translate(Vector3, double);
	Vector3 getForward() { return forward_; }
	Vector3 getRight() { right_ = forward_.Cross(up_); return right_; }
	Vector3 getPosition() { return position_; }
	void setUp(Vector3 newUp) { up_ = newUp; }
	void rotate(Vector3, double, float);
	void setForward(Vector3 newforward) { this->forward_ = newforward; right_ = forward_.Cross(up_);}
	Mtx44 getMatrix();
	void setPosition(Vector3 newposition) { position_ = newposition; }
	void rotate(Vector3 axisofrotate, double rotatespeed, Vector3 target);
};

#endif