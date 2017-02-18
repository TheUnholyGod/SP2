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
	/*this->position = defaultPosition = pos;
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
	anchorY = point.y;*/

	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();

	glfwGetWindowSize(Application::m_window, &windowX, &windowY);
	glfwSetCursorPos(Application::m_window, windowX / 2, windowY / 2);
	glfwSetInputMode(Application::m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	anchorX = windowX / 2;
	anchorY = windowY / 2;
}

void Camera4::Update(double dt, Vector3 charpos, Vector3 righto, Vector3 for_what, Vector3*camForward, Vector3*camRight)
{
	/*static const float CAMERA_SPEED = 10.f;
	static const float CAMERA_SPEED_2 = 125.f;
	position = charpos;
	target = position + temp;

	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);

	glfwGetWindowSize(Application::m_window, &windowX, &windowY);
	GetCursorPos(&cursorpoint);

	if (anchorX > cursorpoint.x)
	{
		this->yaw = (float)(CAMERA_SPEED_2 * dt);
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		temp = rotation * temp;
		up = rotation * up;
	}

	if (anchorX < cursorpoint.x)
	{
		this->yaw = (float)(-CAMERA_SPEED_2 * dt);
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		temp = rotation * temp;
		up = rotation * up;
	}

	if (pitchLimit < 160 && cursorpoint.y < anchorY)
	{
		this->pitch = (float)(CAMERA_SPEED * (anchorY - cursorpoint.y)) * dt;
		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		temp = rotation * temp;
		target = position + temp;
		pitchLimit += (anchorY - cursorpoint.y);
	}
	else if (pitchLimit > -200 && cursorpoint.y > anchorY)
	{
		this->pitch = (float)(-CAMERA_SPEED * (cursorpoint.y - anchorY)) * dt;
		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		temp = rotation * temp;
		target = position + temp;
		pitchLimit -= (cursorpoint.y - anchorY);
	}

	if (Application::IsKeyPressed('X'))
	{
		Reset();
	}
	SetCursorPos(windowX / 2, windowY / 2);
	anchorX = windowX / 2;
	anchorY = windowY / 2;
	*camForward = view;
	*camRight = right;*/

	static const float CAMERA_SPEED = 50.f;
	glfwGetCursorPos(Application::m_window, &cursorX, &cursorY);

	position = charpos;
	target = position + temp;

	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	
	if (anchorX > cursorpoint.x)
	{
		this->yaw = (float)(CAMERA_SPEED * dt);
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		temp = rotation * temp;
		up = rotation * up;
	}

	if (anchorX < cursorpoint.x)
	{
		this->yaw = (float)(-CAMERA_SPEED * dt);
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		temp = rotation * temp;
		up = rotation * up;
	}

	if (pitchLimit < 160 && cursorpoint.y < anchorY)
	{
		this->pitch = (float)(CAMERA_SPEED * (anchorY - cursorpoint.y)) * dt;
		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		temp = rotation * temp;
		target = position + temp;
		pitchLimit += (anchorY - cursorpoint.y);
	}
	else if (pitchLimit > -200 && cursorpoint.y > anchorY)
	{
		this->pitch = (float)(-CAMERA_SPEED * (cursorpoint.y - anchorY)) * dt;
		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		temp = rotation * temp;
		target = position + temp;
		pitchLimit -= (cursorpoint.y - anchorY);
	}

	glfwSetCursorPos(Application::m_window, windowX / 2, windowY / 2);
	anchorX = windowX / 2;
	anchorY = windowY / 2;
	*camForward = view;
	*camRight = right;
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