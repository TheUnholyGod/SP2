#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"

POINT point;

Camera3::Camera3()
{
	windowX = 0;
	windowY = 0;
	//anchor_.x = anchor_.y = 0;
	point.x = point.y = 0;
	pitch = 0;
	yaw = 0;
	pitchLimit = 0;
	is_menu = false;
}

Camera3::~Camera3()
{
}

void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.Normalize();
	this->up = defaultUp = up;
	temp = target;
	glfwGetWindowSize(Application::m_window, &windowX, &windowY);
	SetCursorPos(windowX / 2, windowY / 2);
	GetCursorPos(&point);
	ShowCursor(false);
	anchorX = point.x;
	anchorY = point.y;
}

void Camera3::Update(double dt, Vector3 charpos,Vector3 righto,Vector3 for_what,Vector3*camForward,Vector3*camRight)
{
	static const float CAMERA_SPEED = 10.f;
	static const float CAMERA_SPEED_2 = 125.f;
	
	if (!is_menu)
	{
		position = charpos;
		target = position + temp;

		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);

		glfwGetWindowSize(Application::m_window, &windowX, &windowY);
		GetCursorPos(&point);

		if (anchorX > point.x)
		{
			this->yaw = (float)(CAMERA_SPEED_2 * dt);
			Mtx44 rotation;
			rotation.SetToRotation(yaw, 0, 1, 0);
			temp = rotation * temp;
			up = rotation * up;
			up.Normalize();
		}

		if (anchorX < point.x)
		{
			this->yaw = (float)(-CAMERA_SPEED_2 * dt);
			Mtx44 rotation;
			rotation.SetToRotation(yaw, 0, 1, 0);
			temp = rotation * temp;
			up = rotation * up;
			up.Normalize();
		}

		if (pitchLimit < 160 && point.y < anchorY)
		{
			this->pitch = (float)(CAMERA_SPEED * (anchorY - point.y)) * dt;
			Mtx44 rotation;
			rotation.SetToRotation(pitch, right.x, right.y, right.z);
			temp = rotation * temp;
			target = position + temp;
			up = right.Cross(view);
			up.Normalize();
			pitchLimit += (anchorY - point.y);
		}
		else if (pitchLimit > -200 && point.y > anchorY)
		{
			this->pitch = (float)(-CAMERA_SPEED * (point.y - anchorY)) * dt;
			Mtx44 rotation;
			rotation.SetToRotation(pitch, right.x, right.y, right.z);
			temp = rotation * temp;
			target = position + temp;
			up = right.Cross(view);
			up.Normalize();
			pitchLimit -= (point.y - anchorY);
		}

		if (Application::IsKeyPressed('X'))
		{
			Reset();
		}
		SetCursorPos(windowX / 2, windowY / 2);
		anchorX = windowX / 2;
		anchorY = windowY / 2;
		*camForward = view;
		*camRight = right;
		std::cout << "Up: " << up << std::endl;

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