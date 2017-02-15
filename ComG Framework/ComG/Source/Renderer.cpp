#include "Renderer.h"

Renderer::Renderer()
{

}

Renderer::Renderer(Vector3 position, Vector3 forward) : position_(position),forward_(forward)
{
	up_ = Vector3(0, 1, 0);
	right_ = forward_.Cross(up_);
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

Mtx44 Renderer::getMatrix()
{
	return matrix_ = Mtx44(right_.x, right_.y, right_.z, 0, up_.x, up_.y, up_.z, 0, forward_.x, forward_.y, forward_.z, 0, position_.x, position_.y, position_.z, 1);
}