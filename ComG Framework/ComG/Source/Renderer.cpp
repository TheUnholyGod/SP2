#include "Renderer.h"

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

void Renderer::translate(Vector3 direction, double speed)
{
	this->position_ += direction * speed;
}

void Renderer::rotate(Vector3 axisofrotate, double rotatespeed, float rotateangle)
{
	if (rotateangle > rotatemax)
	{
		forward_ += axisofrotate * rotatespeed;
	}
	rotatemax += rotatespeed;
}