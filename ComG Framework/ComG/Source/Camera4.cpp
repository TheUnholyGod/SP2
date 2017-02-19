#include "Camera4.h"
#include "Application.h"
#include "Mtx44.h"

POINT cursorpoint;

Camera4::Camera4()
{
	windowX = 0;
	windowY = 0;
	cursorpoint.x = 0;
	cursorpoint.y = 0;
	pitch = 0;
	yaw = 0;
	pitchLimit = 0;
}

Camera4::~Camera4()
{
}

void Camera4::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{

}

void Camera4::Update(double dt, Vector3 charpos, Vector3 righto, Vector3 for_what, Vector3*camForward, Vector3*camRight)
{
	
}

void Camera4::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}

Vector3 Camera4::getPosition()
{
	return position;
}