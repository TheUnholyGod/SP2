#ifndef SCENE_SplashScreen_H
#define SCENE_SplashScreen_H

#include "Scene.h"
#include "Camera.h"
#include "Camera2.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Utility.h"
#include <vector>

class SceneSplashScreen : public Scene
{
public:
	SceneSplashScreen();
	~SceneSplashScreen();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
private:
	Camera2 camera;
	Light light[1];
	Vector3 lighting;
	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void essentials();
};

#endif