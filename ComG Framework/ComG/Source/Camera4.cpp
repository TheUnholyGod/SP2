#include "Camera4.h"
#include "Application.h"
#include "Mtx44.h"

Camera4::Camera4()
{
	anchorX = 0;
	anchorY = 0;

	cursorX = 0;
	cursorY = 0;

	windowX = 0;
	windowY = 0;

	cursorXDiff = 0;
	cursorYDiff = 0;

	yaw = 0;
	pitch = 0;
}

Camera4::~Camera4()
{
}

void Camera4::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	this->view = (target - position).Normalized();
	this->right = Vector3(1, 0, 0);
	this->up = Vector3(0, 1, 0);

	glfwGetWindowSize(Application::m_window, &windowX, &windowY);
	glfwGetCursorPos(Application::m_window, &cursorX, &cursorY);

	anchorX = windowX / 2;
	anchorY = windowY / 2;

	//glfwSetInputMode(Application::m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Camera4::Update(double dt, Vector3 charpos, Vector3 righto, Vector3 for_what, Vector3*camForward, Vector3*camRight)
{
	static const float CAMERA_SPEED = 2.f;

	right = view.Cross(up);
	position = charpos;
	target = position + view;

	Mtx44 rotation;
	Mtx44 camPitch;
	Mtx44 camYaw;

	glfwGetCursorPos(Application::m_window, &cursorX, &cursorY);
	glfwSetCursorPos(Application::m_window, anchorX, anchorY);

	cursorXDiff = anchorX - cursorX;
	cursorYDiff = anchorY - cursorY;

	yaw = cursorXDiff / CAMERA_SPEED;
	pitch = cursorYDiff / CAMERA_SPEED;

	if (pitch > 2)
	{
		pitch = 1.99;
	}
	if (pitch < -2)
	{
		pitch = -1.99;
	}

	camYaw.SetToRotation(yaw, 0, 1, 0);
	camPitch.SetToRotation(pitch, right.x, right.y, right.z);
	rotation = camPitch * camYaw;

	view = (rotation * view).Normalized();
	target = (position + view);
	up = camYaw * up;
	right = camPitch * right;

	anchorX = windowX / 2;
	anchorY = windowY / 2;

	*camForward = (target - position).Normalized();
	*camRight = right;

	if (Application::IsKeyPressed('X'))
	{
		Reset();
	}
}

void Camera4::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;

	glfwGetWindowSize(Application::m_window, &windowX, &windowY);

	anchorX = windowX / 2;
	anchorY = windowY / 2;

	cursorXDiff = 0;
	cursorYDiff = 0;

	yaw = 0;
	pitch = 0;
}

Vector3 Camera4::getPosition()
{
	return position;
}