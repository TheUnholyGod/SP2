#include "Renderer.h"

Renderer::Renderer()
{

}

Renderer::Renderer(Vector3 position, Vector3 forward) : position_(position),forward_(forward),scaling(1)
{
	up_ = Vector3(0, 1, 0);
	right_ = forward_.Cross(up_).Normalized();
}

Renderer::~Renderer()
{

}

void Renderer::translate(Vector3 direction, double speed)
{
	this->position_ += direction * speed;
	if (this->position_.y < 0)
	{
		this->position_.y = 0;
	}
}

void Renderer::rotate(Vector3 axisofrotate, double rotatespeed, float rotateangle)
{
	Mtx44 Rotation;
	Rotation.SetToRotation(rotatespeed, 0, 1, 0);
	if (rotateangle > rotatemax)
	{
		forward_ = Rotation * forward_;
		right_ = Rotation * right_;
		rotatemax += rotatespeed;
	}
	right_ = up_.Cross(forward_).Normalized();
}

void Renderer::rotate(Vector3 axisofrotate, double rotatespeed, Vector3 target)
{
	Mtx44 Rotation;
	Rotation.SetToRotation(rotatespeed, 0, 1, 0);
	if (forward_ != target)
	{
		forward_ = Rotation * forward_;
		right_ = Rotation * right_;
		rotatemax += rotatespeed;
	}
	right_ = up_.Cross(forward_).Normalized();
}

Mtx44 Renderer::getMatrix()
{
	right_.Normalize();
	forward_.Normalize();
	up_.Normalize();
	return matrix_ = Mtx44(right_.x*scaling, right_.y*scaling, right_.z*scaling, 0, up_.x*scaling, up_.y*scaling, up_.z*scaling, 0, forward_.x*scaling, forward_.y*scaling, forward_.z*scaling, 0, position_.x, position_.y, position_.z, 1);
}