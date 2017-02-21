#ifndef CAMERA_4_H
#define CAMERA_4_H

#include "Camera.h"
//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

class Camera4 : public Camera
{
public:
	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;
	Vector3 camVec;
	Vector3 view;
	Vector3 right;
	static Vector3 getPosition();

	float yaw;
	float pitch;

	int windowX;
	int windowY;

	int anchorX;
	int anchorY;

	double cursorX;
	double cursorY;

	int cursorXDiff;
	int cursorYDiff;

	bool is_menu;

	Camera4();
	~Camera4();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Update(double dt, Vector3 charpos, Vector3 righto, Vector3 for_what, Vector3* camForward, Vector3* camRight);
	virtual void Reset();

};

#endif