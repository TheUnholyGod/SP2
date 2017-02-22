#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"

POINT point;

Camera3::Camera3()
{

}

Camera3::~Camera3()
{
}

void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = forward = target;
	this->up = defaultUp = up;
	this->right = forward.Cross(up);
	right.Normalize();
	forward = target;
	windowX = 0;
	windowY = 0;
	point.x = point.y = 0;
	glfwGetWindowSize(Application::m_window, &windowX, &windowY);
	SetCursorPos(windowX / 2, windowY / 2);
	GetCursorPos(&point);
	ShowCursor(false);
	anchorX = point.x;
	anchorY = point.y;
	pitch = 0;
	yaw = 0;
	pitchLimit = 0.f;
	is_menu = false;
}

void Camera3::Update(double dt, Vector3 charpos,Vector3 righto,Vector3 for_what,Vector3*camForward,Vector3*camRight)
{
	static const float CAMERA_SPEED = 10.f;
	static const float CAMERA_SPEED_2 = 125.f;
	
	if (!is_menu)
	{
		position = charpos;
		target = position + forward;
		right = forward.Cross(up);

		glfwGetWindowSize(Application::m_window, &windowX, &windowY);
		GetCursorPos(&point);
		if (anchorX > point.x)
		{
			this->yaw = (float)(CAMERA_SPEED_2 * dt);
			Mtx44 rotation;
			rotation.SetToRotation(yaw, 0, 1, 0);
			forward = rotation * forward;
			up = rotation * up;
			right = forward.Cross(up).Normalize();
		}

		else if (anchorX < point.x)
		{
			this->yaw = (float)(-CAMERA_SPEED_2 * dt);
			Mtx44 rotation;
			rotation.SetToRotation(yaw, 0, 1, 0);
			forward = rotation * forward;
			up = rotation * up;
			right = forward.Cross(up).Normalize();
		}

		if (pitchLimit < 80 && point.y < anchorY)
		{
			this->pitch = (float)(CAMERA_SPEED * (anchorY - point.y) * dt);
			Mtx44 rotation;
			rotation.SetToRotation(pitch, right.x, right.y, right.z);
			forward = rotation * forward;
			up = right.Cross(forward);
			up.Normalize();
			pitchLimit += pitch;
		}
		else if (pitchLimit > -80 && point.y > anchorY)
		{
			this->pitch = (float)(-CAMERA_SPEED * (point.y - anchorY) * dt);
			Mtx44 rotation;
			rotation.SetToRotation(pitch, right.x, right.y, right.z);
			forward = rotation * forward;
			up = right.Cross(forward);
			up.Normalize();
			pitchLimit += pitch;
		}
		if (Application::IsKeyPressed('X'))
		{
			Reset();
		}
		SetCursorPos(windowX / 2, windowY / 2);
		point.x = windowX / 2;
		point.y = windowY / 2;
		anchorX = windowX / 2;
		anchorY = windowY / 2;
		*camForward = forward;
		*camRight = right;
	}
}

void Camera3::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}

Vector3 Camera3::getPosition()
{
	return position;
}

Vector3 Camera3::getForward()
{
	return target;
}