#ifndef SCENE_UI_H
#define SCENE_UI_H

#include "Scene.h"
#include "Camera.h"
#include "Camera2.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Utility.h"
#include <vector>

class SceneUI : public Scene
{
public:
	SceneUI();
	~SceneUI();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
private:

	struct bounds
	{
		float max_x, max_z, min_x, min_z;
	}barnwall1, bed, fence1, fence2, fence3, fence4, barnwall2, barnwall3, barnwall4;

	Vector3 forward, right, chardirection, camForward, camRight;
	Camera2 camera;
	Camera3 fp_camera;
	Light light[1];
	Vector3 lighting;
	void RenderMesh(Mesh *mesh, bool enableLight);
	float LSPEED;

	double y, x, z;

	void LoadSkybox();
	void RenderSkybox();

	void UpdateCharacter(double dt);
	Vector3 charpos;

	void DebugMode(double dt);
	bool ifInDebug;

	void cameraupdates(double dt);
	bool fps;

	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);

	void LightUpdate(double dt);
	double lightrotate, sunrotate;
	Mtx44 LightPos;
	bool sunup;

	std::vector<bounds> walls;
	bool loadBounds();
	bool ifBounds(Vector3 forwhat);
	bool sleep(Vector3 forwhat);
	void LightReset(double dt);
	bool reset;
	float suntimer;
	void growVege(double dt);
	void plantVege(int vegeno);
	void textupdates();
	std::string charx, chary, charz, carrotstr, cabbagestr, potatostr;
	void generateGoat();
	void renderGoat();
	void updateGoat(double dt, Vector3 forwhat);
	struct vegegrowth
	{
		double growpotato;
		double maxsize;
		Vector3 vegepos;
		int numtype;
		bool picked, onhotbar;
		float max_x, max_z, min_x, min_z;
	};
	std::vector<vegegrowth*>  allvegetables;
	int potatoseeds;
	int carrotseeds;
	int cabbageseeds;
	int potato;
	int carrot;
	int cabbage;
	void vegepicked(Vector3 forwhat);
	double cooldown;

	struct goats
	{
		float max_x, max_z, min_x, min_z;
		Vector3 goatspos;
		float yrotate;
		float legrotate1, legrotate2;
		float outermax_x, outermax_z, outermin_x, outermin_z;
		bool frontorreverse;
		bool facechar;
	};

	std::vector<goats*> allgoats;
	bool holdingvege;
	void feedgoat(int no);
	void RenderMeshOnScreen(Mesh* mesh, int x, int y, int
		sizex, int sizey);
};

#endif