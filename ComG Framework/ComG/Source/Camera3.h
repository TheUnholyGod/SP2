#ifndef CAMERA_3_H
#define CAMERA_3_H

#include "Camera.h"
//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

class Camera3 : public Camera
{
public:
	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;
	Vector3 camVec;
	Vector3 temp;
	int windowX, windowY;
	int anchorX, anchorY;
	float pitch, yaw;
	float pitchLimit;

	Camera3();
	~Camera3();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Update(double dt, Vector3 charpos, Vector3 righto, Vector3 for_what, double* rotate, Vector3*camForward,Vector3*camRight);
	virtual void Reset();

};

#endif