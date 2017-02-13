#ifndef SCENE_MODEL_H
#define SCENE_MODEL_H

#include "Scene.h"
#include "Camera.h"
#include "Camera2.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Utility.h"
#include <vector>

class SceneModel : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_TEXT,
		GEO_QUAD,
		GEO_BED,
		//SkyBox
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,
		
		GEO_CHARACTERMODEL,
		GEO_BARNMODEL,
		GEO_SUN,
		GEO_FENCE,
		GEO_POTATO,
		GEO_CARROT,
		GEO_CABBAGE,

		//---Horns---//
		GEO_HORN1,
		GEO_HORN2,
		//---Head---//
		GEO_HEADCYLINDER,
		GEO_HEADSPHERE,
		GEO_HEADCONE,
		GEO_EYES,
		GEO_EYEPUPIL,
		//---Neck---//
		GEO_NECK,
		//---Body---//
		GEO_BODYSPHERE,
		GEO_BODYCYLINDER,
		//---Legs---//
		GEO_LEGCYLINDER,
		GEO_LEGSPHERE,

		NUM_GEOMETRY,
	};
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHTENABLED,
		//add these enum in UNIFORM_TYPE before U_TOTAL
		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		U_NUMLIGHTS,
		//add these enum in UNIFORM_TYPE before U_TOTAL
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,

		U_TEXT_ENABLED,
		U_TEXT_COLOR,

		U_TOTAL,
	};


public:
	SceneModel();
	~SceneModel();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
private:
	unsigned m_vertexArrayID;
	Mesh *meshList[NUM_GEOMETRY];

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	struct bounds
	{
		float max_x, max_z, min_x, min_z;
	}barnwall1, bed, fence1, fence2, fence3, fence4, barnwall2, barnwall3, barnwall4;

	MS modelStack, viewStack, projectionStack;
	Vector3 forward, right, chardirection, camForward, camRight;
	Camera2 camera;
	Camera3 fp_camera;
	Light light[1];
	Vector3 lighting;
	void RenderMesh(Mesh *mesh, bool enableLight);
	float LSPEED;

	double y,x,z;

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
	double lightrotate,sunrotate;
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
	std::string charx, chary, charz ,carrotstr,cabbagestr,potatostr;
	void generateGoat();
	void renderGoat();
	void updateGoat(double dt,Vector3 forwhat);
	struct vegegrowth
	{
		double growpotato;
		double maxsize;
		Vector3 vegepos;
		int numtype;
		bool picked,onhotbar;
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
};

extern GLFWwindow* m_window;

#endif