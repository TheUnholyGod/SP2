#include "SceneModel.h"
#include "GL\glew.h"
#include "shader.hpp"
#include "Mtx44.h"
#include "Application.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"
#include "SceneManager.h"

#include <sstream>

SceneModel::SceneModel()
{
}

SceneModel::~SceneModel()
{
}

void SceneModel::Init()
{
#if DEBUG
	ifInDebug = true;
#endif

	sunup = 1;

	LSPEED = 10.f;
	// Init VBO here

	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);

	//Enable back face culling
	glEnable(GL_CULL_FACE);

	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");

	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");



	glUseProgram(m_programID);

	// Make sure you pass uniform parameters after glUseProgram()
	glUniform1i(m_parameters[U_NUMLIGHTS], 1);


	y = 0;
	x = 0;
	z = 0;
	charpos.x = x;
	charpos.y = 10;
	charpos.z = z;
	fps = false;
	forward.z = 1;
	right.x = 1;
	chardirection = forward;
	lighting.y = 1.f;
	reset = false;
	sunup = true;
	cooldown = 0;

	//Initialize camera settings
	camera.Init(-forward * 20, charpos, Vector3(0, 1, 0));

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 10000.f);
	projectionStack.LoadMatrix(projection);

	light[0].type = Light::LIGHT_DIRECTIONAL;
	light[0].position.Set(0, 100, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 1.f;
	light[0].kC = 100.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(0.f, 1.f, 0.f);

	// Make sure you pass uniform parameters after glUseProgram()
	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);
	glUniform1i(m_parameters[U_NUMLIGHTS], 1);

	meshList[GEO_CHARACTERMODEL] = MeshBuilder::GenerateOBJ("model1", "OBJ//Character.obj");
	meshList[GEO_CHARACTERMODEL]->textureID = LoadTGA("Image//t_dither500_m.tga");

	meshList[GEO_BARNMODEL] = MeshBuilder::GenerateOBJ("car", "OBJ//car.obj");
	meshList[GEO_BARNMODEL]->textureID = LoadTGA("Image//car.tga");

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad1("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//ground.tga");

	meshList[GEO_SUN] = MeshBuilder::GenerateSphere("sun", Color(1, 1, 0), 5.f);

	meshList[GEO_BED] = MeshBuilder::GenerateOBJ("bed", "OBJ//BED.obj");
	meshList[GEO_BED]->textureID = LoadTGA("Image//Bed.tga");

	meshList[GEO_FENCE] = MeshBuilder::GenerateOBJ("fence", "OBJ//fence.obj");
	meshList[GEO_FENCE]->textureID = LoadTGA("Image//wood.tga");

	meshList[GEO_POTATO] = MeshBuilder::GenerateOBJ("potato", "OBJ//potato.obj");
	meshList[GEO_POTATO]->textureID = LoadTGA("Image//potato.tga");

	meshList[GEO_CARROT] = MeshBuilder::GenerateOBJ("carrot", "OBJ//carrot.obj");
	meshList[GEO_CARROT]->textureID = LoadTGA("Image//carrot.tga");

	meshList[GEO_CABBAGE] = MeshBuilder::GenerateOBJ("cabbage", "OBJ//cabbage.obj");
	meshList[GEO_CABBAGE]->textureID = LoadTGA("Image//Cabbage.tga");

	bool temp = loadBounds();
	LoadSkybox();
	suntimer = 1;
	generateGoat();
	cabbageseeds = 3;
	carrotseeds = 3;
    potatoseeds = 3;
	cabbage = 0;
	carrot = 0;
	potato = 0;
	holdingvege = false;
}

void SceneModel::Update(double dt)
{
	if (ifInDebug)
		DebugMode(dt);

	if (Application::IsKeyPressed('F'))
	{
		plantVege(1);
	}
	else if (Application::IsKeyPressed('G'))
	{
		plantVege(2);
	}
	else if (Application::IsKeyPressed('H'))
	{
		plantVege(3);
	}
	if (Application::IsKeyPressed('R'))
	{
		vegepicked(forward);
	}
	if (Application::IsKeyPressed('E'))
	{
		SceneManager::currScene = 2;
	}

	LightUpdate(dt);
	UpdateCharacter(dt);
	cameraupdates(dt);
	growVege(dt);
	textupdates();
	updateGoat(dt,forward);

	if (potato + carrot + cabbage <= 0)
	{
		holdingvege = false;
	}
}

void SceneModel::Render()
{
	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	viewStack.LoadIdentity();
	if (fps == false)
	{
		viewStack.LookAt(camera.position.x, camera.position.y,
			camera.position.z, camera.target.x, camera.target.y,
			camera.target.z, camera.up.x, camera.up.y, camera.up.z);
	}
	else if (fps == true)
	{
		viewStack.LookAt(fp_camera.position.x, fp_camera.position.y,
			fp_camera.position.z, fp_camera.target.x, fp_camera.target.y,
			fp_camera.target.z, fp_camera.up.x, fp_camera.up.y, fp_camera.up.z);
	}
	modelStack.LoadIdentity();

	if (light[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[0].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}

	RenderMesh(meshList[GEO_AXES], false);

	RenderSkybox();

	modelStack.PushMatrix();
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_QUAD], true);
	modelStack.PopMatrix();

	if (!fps)
	{
		modelStack.PushMatrix();
		modelStack.Translate(charpos.x, charpos.y - 10, charpos.z);
		modelStack.Rotate(y, 0, 1, 0);
		modelStack.Scale(5, 5, 5);
		RenderMesh(meshList[GEO_CHARACTERMODEL], true);
		modelStack.PopMatrix();
	}

	//modelStack.PushMatrix();
	//modelStack.Rotate(90, 1, 0, 0);
	////modelStack.Rotate(180, 0, 1, 0);
	////modelStack.Rotate(90, 0, 0, 1);
	//modelStack.Scale(10, 0, 10);
	//RenderText(meshList[GEO_TEXT], "Hello World", Color(0, 1, 0));
	//modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-220, 0, 210);
	modelStack.Scale(4, 4, 4);
	RenderMesh(meshList[GEO_BED], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
//	modelStack.Translate(-200, 0, 200);
	modelStack.Scale(4, 4, 4);
	RenderMesh(meshList[GEO_BARNMODEL], true);
	modelStack.PopMatrix();

	for (int i = -250; i <= 250; i += 10)
	{
		modelStack.PushMatrix();
		modelStack.Translate(i, 0, -250);
		modelStack.Scale(4, 4, 4);
		RenderMesh(meshList[GEO_FENCE], true);
		modelStack.PopMatrix();
	}

	for (int i = -250; i <= 250; i += 10)
	{
		modelStack.PushMatrix();
		modelStack.Translate(i, 0, 250);
		modelStack.Scale(4, 4, 4);
		RenderMesh(meshList[GEO_FENCE], true);
		modelStack.PopMatrix();
	}

	for (int i = -250; i <= 250; i += 10)
	{
		modelStack.PushMatrix();
		modelStack.Translate(250, 0, i);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(4, 4, 4);
		RenderMesh(meshList[GEO_FENCE], true);
		modelStack.PopMatrix();
	}

	for (int i = -250; i <= 250; i += 10)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-250, 0, i);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(4, 4, 4);
		RenderMesh(meshList[GEO_FENCE], true);
		modelStack.PopMatrix();
	}

	for (auto &i : allvegetables)
	{
		modelStack.PushMatrix();
		modelStack.Translate(i->vegepos.x, i->vegepos.y, i->vegepos.z);
		if (!i->picked)
			modelStack.Scale(i->growpotato, i->growpotato, i->growpotato);
		else
			modelStack.Scale(i->growpotato*0.1, i->growpotato*0.1, i->growpotato*0.1);
		RenderMesh(meshList[i->numtype], true);
		modelStack.PopMatrix();
	}

	RenderTextOnScreen(meshList[GEO_TEXT], charx, Color(0, 1, 0), 3, 1, 3);
	RenderTextOnScreen(meshList[GEO_TEXT], chary, Color(0, 1, 0), 3, 1, 2);
	RenderTextOnScreen(meshList[GEO_TEXT], charz, Color(0, 1, 0), 3, 1, 1);
	RenderTextOnScreen(meshList[GEO_TEXT], potatostr, Color(0, 1, 1), 3, 1, 19);
	RenderTextOnScreen(meshList[GEO_TEXT], carrotstr, Color(0, 1, 1), 3, 1, 18);
	RenderTextOnScreen(meshList[GEO_TEXT], cabbagestr, Color(0, 1, 1), 3, 1, 17);
	//renderGoat();

	for (auto &i : allvegetables)
	{
		if (i->growpotato > 1 && i->picked)
		{
			if (((charpos.x) >= i->min_x && (charpos.x) <= i->max_x) &&
				((charpos.z) >= i->min_z && (charpos.z) <= i->max_z))
			{
				RenderTextOnScreen(meshList[GEO_TEXT], "Press R to harvest ", Color(0, 1, 0), 3, 5, 5);
				break;
			}
		}
	}
}

void SceneModel::Exit()
{
	glDeleteProgram(m_programID);
	glDeleteVertexArrays(1, &m_vertexArrayID);
}

void SceneModel::RenderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
	if (enableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}

	if (mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render(); //this line should only be called once
	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}

void SceneModel::LoadSkybox()
{
	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1.f);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//Skybox-Day//left.tga");

	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1.f);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//Skybox-Day//back.tga"); 

	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1.f);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//Skybox-Day//front.tga");

	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1.f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//Skybox-Day//right.tga");

	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1.f);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//Skybox-Day//bottom.tga");

	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1.f);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//Skybox-Day//top.tga");

	/////////////////////////////////////////////////////////////////////////////////

	meshList[GEO_FRONT1] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1.f);
	meshList[GEO_FRONT1]->textureID = LoadTGA("Image//Skybox-Night//newleft.tga");

	meshList[GEO_LEFT1] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1.f);
	meshList[GEO_LEFT1]->textureID = LoadTGA("Image//Skybox-Night//newback.tga");

	meshList[GEO_RIGHT1] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1.f);
	meshList[GEO_RIGHT1]->textureID = LoadTGA("Image//Skybox-Night//newfront.tga");

	meshList[GEO_BACK1] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1.f);
	meshList[GEO_BACK1]->textureID = LoadTGA("Image//Skybox-Night//newright.tga");

	meshList[GEO_BOTTOM1] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1.f);
	meshList[GEO_BOTTOM1]->textureID = LoadTGA("Image//Skybox-Night//newbottom.tga");

	meshList[GEO_TOP1] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1.f);
	meshList[GEO_TOP1]->textureID = LoadTGA("Image//Skybox-Night//newtop.tga");

	/////////////////////////////////////////////////////////////////////////////////

	meshList[GEO_FRONT2] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1.f);
	meshList[GEO_FRONT2]->textureID = LoadTGA("Image//Skybox-Transition//tranleft.tga");

	meshList[GEO_LEFT2] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1.f);
	meshList[GEO_LEFT2]->textureID = LoadTGA("Image//Skybox-Transition//tranback.tga");

	meshList[GEO_RIGHT2] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1.f);
	meshList[GEO_RIGHT2]->textureID = LoadTGA("Image//Skybox-Transition//tranfront.tga");

	meshList[GEO_BACK2] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1.f);
	meshList[GEO_BACK2]->textureID = LoadTGA("Image//Skybox-Transition//tranright.tga");

	meshList[GEO_BOTTOM2] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1.f);
	meshList[GEO_BOTTOM2]->textureID = LoadTGA("Image//Skybox-Transition//tranbottom.tga");

	meshList[GEO_TOP2] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1.f);
	meshList[GEO_TOP2]->textureID = LoadTGA("Image//Skybox-Transition//trantop.tga");
}

void SceneModel::RenderSkybox()
{
	modelStack.PushMatrix();
	modelStack.Translate(charpos.x, 0, charpos.z);
	modelStack.PushMatrix();
	modelStack.Scale(1000, 1000, 1000);
	modelStack.PushMatrix();
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Rotate(270, 1, 0, 0);
	modelStack.Translate(0, 0.5, 0);

	if (sunup == 1)
		RenderMesh(meshList[GEO_LEFT], false);

	else if(sunup == 2)
		RenderMesh(meshList[GEO_LEFT1], false);

	else if (sunup == 3)
		RenderMesh(meshList[GEO_LEFT2], false);

	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Translate(0, -0.5, 0);
	modelStack.Scale(1, 1, -1);

	if (sunup == 1)
		RenderMesh(meshList[GEO_BOTTOM], false);

	else if (sunup == 2)
		RenderMesh(meshList[GEO_BOTTOM1], false);

	else if (sunup == 3)
		RenderMesh(meshList[GEO_BOTTOM2], false);

	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Translate(0, 0.5, 0);

	if (sunup == 1)
		RenderMesh(meshList[GEO_RIGHT], false);

	else if (sunup == 2)
		RenderMesh(meshList[GEO_RIGHT1], false);

	else if (sunup == 3)
		RenderMesh(meshList[GEO_RIGHT2], false);

	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(0.5, 0, 0);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Rotate(180, 1, 0, 0);

	if (sunup == 1)
		RenderMesh(meshList[GEO_BACK], false);

	else if (sunup == 2)
		RenderMesh(meshList[GEO_BACK1], false);

	else if (sunup == 3)
		RenderMesh(meshList[GEO_BACK2], false);

	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Translate(0, 0.5, 0);

	if (sunup == 1)
		RenderMesh(meshList[GEO_TOP], false);

	else if (sunup == 2)
		RenderMesh(meshList[GEO_TOP1], false);

	else if (sunup == 3)
		RenderMesh(meshList[GEO_TOP2], false);

	modelStack.PopMatrix();
	modelStack.Translate(-0.5, 0, 0);
	modelStack.Rotate(90, 0, 0, 1);

	if (sunup == 1)
		RenderMesh(meshList[GEO_FRONT], false);

	else if (sunup == 2)
		RenderMesh(meshList[GEO_FRONT1], false);

	else if (sunup == 3)
		RenderMesh(meshList[GEO_FRONT2], false);

	modelStack.PopMatrix();
	modelStack.PopMatrix();
}

void SceneModel::DebugMode(double dt)
{
	if (Application::IsKeyPressed('1')) //enable back face culling
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2')) //disable back face culling
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode
}

void SceneModel::UpdateCharacter(double dt)
{
	if (!fps)
	{
		if (Application::IsKeyPressed('A'))
		{
			float YOUR;
			Mtx44 calledYOURING;
			YOUR = dt * 100;
			calledYOURING.SetToRotation(YOUR, 0, 1, 0);
			forward = calledYOURING * forward;
			right = calledYOURING * right;
			y += dt * 100;
		}
		if (Application::IsKeyPressed('D'))
		{
			float YOUR;
			Mtx44 calledYOURING;
			YOUR = dt * -100;
			calledYOURING.SetToRotation(YOUR, 0, 1, 0);
			forward = calledYOURING * forward;
			right = calledYOURING * right;
			y += dt * -100;
		}
		if (Application::IsKeyPressed('S') && !ifBounds(-forward))
		{
			charpos -= forward * 10 * dt;
		}
		if (Application::IsKeyPressed('W') && !ifBounds(forward))
		{
			charpos += forward * 10 * dt;
		}
	}
	else if (fps)
	{
		if (forward != camForward)
		{
			forward = camForward;
		}
		if (Application::IsKeyPressed('A') && !ifBounds(-right))
		{
			charpos -= camRight * 10 * dt;
		}
		if (Application::IsKeyPressed('D') && !ifBounds(right))
		{
			charpos += camRight * 10 * dt;
		}
		if (Application::IsKeyPressed('S') && !ifBounds(-forward))
		{
			charpos -= camForward * 10 * dt;
		}
		if (Application::IsKeyPressed('W') && !ifBounds(forward))
		{
			charpos += camForward * 10 * dt;
		}
	}
	if (sleep(forward) && Application::IsKeyPressed('E'))
	{
		LightReset(dt);
	}
}

void SceneModel::cameraupdates(double dt)
{
	if (Application::IsKeyPressed('C') && !fps)
	{
		fps = true;
		fp_camera.Init(charpos, forward, Vector3(0, 1, 0));
	}
	else if (Application::IsKeyPressed('V') && fps)
	{
		fps = false;
		camera.Init(-forward*20, charpos, Vector3(0, 1, 0));
	}

	if (fps == true)
	{
		fp_camera.Update(dt, charpos, forward, right,&y,&camForward,&camRight);
	}
	if (fps == false)
	{
		camera.Update(dt, charpos);
	}
}

void SceneModel::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void SceneModel::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
		if (!mesh || mesh->textureID <= 0) //Proper error check
			return;

		glDisable(GL_DEPTH_TEST);
		Mtx44 ortho;
		ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
		projectionStack.PushMatrix();
		projectionStack.LoadMatrix(ortho);
		viewStack.PushMatrix();
		viewStack.LoadIdentity(); //No need camera for ortho mode
		modelStack.PushMatrix();
		modelStack.LoadIdentity(); //Reset modelStack
		modelStack.Scale(size, size, size);
		modelStack.Translate(x, y, 0);

		glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
		glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
		for (unsigned i = 0; i < text.length(); ++i)
		{
			Mtx44 characterSpacing;
			characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
			Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

			mesh->Render((unsigned)text[i] * 6, 6);
		}
		glBindTexture(GL_TEXTURE_2D, 0);
		glUniform1i(m_parameters[U_TEXT_ENABLED], 0);

		projectionStack.PopMatrix();
		viewStack.PopMatrix();
		modelStack.PopMatrix();
		glEnable(GL_DEPTH_TEST);
}

void SceneModel::LightUpdate(double dt)
{
	if (!reset)
	{
		suntimer = 1;
	}
	lightrotate = (dt * suntimer) * 10;
	sunrotate += lightrotate;
	LightPos.SetToRotation(lightrotate, 0, 0, 1);
	lighting = LightPos * lighting;

	if (lighting.y <= 0)
	{
		light[0].power = 0;
		glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
		if (lighting.y >= 0 && lighting.y <= 0.5)
		{
			sunup = 3;
			reset = false;
		}
		else if (lighting.y <= -0.5)
		{
			sunup = 2;
			reset = false;
		}	
	}
	else
	{
		light[0].type = Light::LIGHT_DIRECTIONAL;
		light[0].position.Set(lighting.x, lighting.y, lighting.z);
		light[0].power = 1;
		glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
		
		if (lighting.y >= 0 && lighting.y < 0.5)
		{
			sunup = 3;
		}
		else if (lighting.y > 0.5)
		{
			sunup = 1;
		}
	}

	std::cout << "Lighting Level: " << lighting.y << std::endl;
}

bool SceneModel::loadBounds()
{
	bed.min_x = -225;
	bed.min_z = 200;
	bed.max_x = -215;
	bed.max_z = 217;
	walls.push_back(bed);
	fence1.max_x = 245;
	fence1.max_z = 350;
	fence1.min_x = -245;
	fence1.min_z = 245;
	walls.push_back(fence1);
	fence2.max_x = 245;
	fence2.max_z = -249;
	fence2.min_x = -245;
	fence2.min_z = -350;
	walls.push_back(fence2);
	fence3.max_x = 350;
	fence3.max_z = 245;
	fence3.min_x = 249;
	fence3.min_z = -245;
	walls.push_back(fence3);
	fence4.max_x = -245;
	fence4.max_z = 245;
	fence4.min_x = -349;
	fence4.min_z = -245;
	walls.push_back(fence4);
	barnwall1.max_x = -160;
	barnwall1.max_z = 180;
	barnwall1.min_x = -242;
	barnwall1.min_z = 178;
	walls.push_back(barnwall1);
	barnwall2.max_x = -240;
	barnwall2.max_z = 222;
	barnwall2.min_x = -242;
	barnwall2.min_z = 179;
	walls.push_back(barnwall2);
	barnwall3.max_x = -160;
	barnwall3.max_z = 222;
	barnwall3.min_x = -241;
	barnwall3.min_z = 220;
	walls.push_back(barnwall3);
	return true;
}

bool SceneModel::ifBounds(Vector3 forwhat)
{
	bool local = false;
	for (auto &i : walls)
	{
		if (((charpos.x + forwhat.x) >= i.min_x && (charpos.x + forwhat.x) <= i.max_x) &&
			((charpos.z + forwhat.z) >= i.min_z && (charpos.z + forwhat.z) <= i.max_z))
		{
			local = true;
			break;
		}
	}

	if ((((charpos.x + forwhat.x) >= allgoats[0]->min_x && (charpos.x + forwhat.x) <= allgoats[0]->max_x) &&
		((charpos.z + forwhat.z) >= allgoats[0]->min_z && (charpos.z + forwhat.z) <= allgoats[0]->max_z)))
	{
		local = true;
	}
	return local;
}

bool SceneModel::sleep(Vector3 forwhat)
{
	if (((charpos.x + forwhat.x) >= bed.min_x && (charpos.x + forwhat.x) <= bed.max_x) &&
		((charpos.z + forwhat.z) >= bed.min_z && (charpos.z + forwhat.z) <= bed.max_z))
	{
		return true;
	}
	else
		return false;
}

void SceneModel::LightReset(double dt)
{
	suntimer = 20;
	reset = true;
}

void  SceneModel::growVege(double dt)
{
	for (auto &i : allvegetables)
	{
		if (!i->picked)
		{
			holdingvege = false;
			if (i->growpotato >= i->maxsize)
				continue;

			i->growpotato += dt * 0.01 * suntimer;
			i->max_x = i->vegepos.x + i->growpotato;
			i->max_z = i->vegepos.z + i->growpotato;
			i->min_x = i->vegepos.x - i->growpotato;
			i->min_x = i->vegepos.z - i->growpotato;
		}
		else
		{
			i->vegepos = charpos;
			holdingvege = true;
		}
	}
}

void SceneModel::textupdates()
{
	std::stringstream ss;
	ss << "X:" << charpos.x;
	ss >> charx;
	std::stringstream ss1;
	ss1 << "Y:" << charpos.y;
	ss1 >> chary;
	std::stringstream ss2;
	ss2 << "Z:" << charpos.z;
	ss2 >> charz;
	std::stringstream ss3;
	ss3 << "Carrot"<<"Vegetable:" <<carrot<<"Seeds:"<<carrotseeds;
	ss3 >> carrotstr;
	std::stringstream ss4;
	ss4 << "Cabbage"<<"Vegetable:" << cabbage << "Seeds:" << cabbageseeds;
	ss4 >> cabbagestr;
	std::stringstream ss5;
	ss5 << "Potato"<<"Vegetable:" << potato << "Seeds:" << potatoseeds;
	ss5 >> potatostr;
}

void SceneModel::generateGoat()
{
	//Head and Neck	
	meshList[GEO_HORN1] = MeshBuilder::GenerateCone("horn1", Color(0.4f, 0.3f, 0.2f), 8.f, 15, 5, 36);
	meshList[GEO_HORN2] = MeshBuilder::GenerateSphere("horn2", Color(0.4f, 0.3f, 0.2f), 8.f, 36);
	meshList[GEO_HEADCYLINDER] = MeshBuilder::GenerateCylinder("headcylinder", Color(0.7f, 0.5f, 0), 36,10.f,10.f,20.f);
	meshList[GEO_HEADSPHERE] = MeshBuilder::GenerateSphere("headsphere", Color(0.7f, 0.5f, 0), 10.0f, 36);
	meshList[GEO_HEADCONE] = MeshBuilder::GenerateCone("headcone", Color(0.7f, 0.5f, 0), 10.0f, 20);
	meshList[GEO_NECK] = MeshBuilder::GenerateCylinder("neckcylinder", Color(0.7f, 0.5f, 0), 7.5f,7.5f, 7.5f, 15.f);
	meshList[GEO_EYES] = MeshBuilder::GenerateSphere("eye", Color(1, 1, 0), 5);
	meshList[GEO_EYEPUPIL] = MeshBuilder::GenerateSphere("eyepupil", Color(0, 0, 0), 5);

	//Body
	meshList[GEO_BODYCYLINDER] = MeshBuilder::GenerateCylinder("bodycylinder", Color(0.7f, 0.5f, 0), 36.f, 10.f, 10.f, 20.f);
	meshList[GEO_BODYSPHERE] = MeshBuilder::GenerateSphere("bodysphere", Color(0.7f, 0.5f, 0), 10.0f, 36);

	//Leg
	meshList[GEO_LEGCYLINDER] = MeshBuilder::GenerateCylinder("legcylinder", Color(0.7f, 0.5f, 0), 36, 2.5f, 2.5f, 5);
	meshList[GEO_LEGSPHERE] = MeshBuilder::GenerateSphere("legsphere", Color(0.7f, 0.5f, 0), 2.5f, 36);
	for (int i = 0; i < 1; i++)
	{
		goats* goaty = new goats;
		goaty->goatspos = (10, 0, 20);
		goaty->max_x = goaty->goatspos.x + 5;
		goaty->max_z = goaty->goatspos.z + 5;
		goaty->min_x = goaty->goatspos.x - 5;
		goaty->min_z = goaty->goatspos.z - 5;
		goaty->outermax_x = goaty->goatspos.x + 10;
		goaty->outermax_z = goaty->goatspos.z + 10;
		goaty->outermin_x = goaty->goatspos.x - 10;
		goaty->outermin_z = goaty->goatspos.z - 10;
		goaty->yrotate = 0;
		goaty->legrotate1 = 0; goaty->legrotate2 = 0;
		goaty->frontorreverse = false;
		goaty->facechar = true;
		allgoats.push_back(goaty);
	}
}

void SceneModel::renderGoat()
{
	for (auto &i : allgoats)
	{
		modelStack.PushMatrix();
		modelStack.Translate(i->goatspos.x, i->goatspos.y + 5, i->goatspos.z);
		modelStack.Rotate(i->yrotate, 0, 1, 0);
		modelStack.Scale(0.1, 0.1, 0.1);
		modelStack.PushMatrix();
		modelStack.Translate(x, 0, z);
		modelStack.PushMatrix(); //Body
		modelStack.PushMatrix(); //Body Cylinder
		modelStack.PushMatrix(); //Body Front Sphere
		modelStack.Translate(0, 0, -20);
		modelStack.PushMatrix();//Neck
		modelStack.Translate(0, 0, -20);
		modelStack.PushMatrix(); //Head
		modelStack.Rotate(25, 1, 0, 0);
		modelStack.PushMatrix(); //Head
		modelStack.Translate(0, 10, -20);

		modelStack.PushMatrix();//Eyes
		modelStack.Translate(5, 6, -5.5f);
		RenderMesh(meshList[GEO_EYES], true);
		modelStack.PushMatrix();//Pupil
		modelStack.Translate(1.f, 0, -1.f);
		modelStack.Scale(0.75f, 0.1f, 1);
		RenderMesh(meshList[GEO_EYEPUPIL], true);
		modelStack.PopMatrix();
		modelStack.PopMatrix();

		modelStack.PushMatrix();//Eyes
		modelStack.Translate(-5, 6, -5.5f);
		RenderMesh(meshList[GEO_EYES], true);
		modelStack.PushMatrix();//Pupil
		modelStack.Translate(-1.f, 0, -1.f);
		modelStack.Scale(0.75f, 0.1f, 1);
		RenderMesh(meshList[GEO_EYEPUPIL], true);
		modelStack.PopMatrix();
		modelStack.PopMatrix();
		for (float i = 0; i < 30; i += 0.5f) //Horn1
		{
			modelStack.PushMatrix();
			modelStack.Translate(4, 10, 0);
			modelStack.PushMatrix();
			modelStack.Rotate(i, 1, 0, 0);
			modelStack.Translate(0, i, 0);
			modelStack.Scale(0.5f, 0.3f, 0.5f);
			RenderMesh(meshList[GEO_HORN1], true);
			modelStack.PopMatrix();
			modelStack.PopMatrix();
		}
		for (float i = 0; i < 15; i += 0.5f) //Horn2
		{
			modelStack.PushMatrix();
			modelStack.Translate(-4, 10, 0);
			modelStack.PushMatrix();
			modelStack.Rotate(i, 1, 0, 0);
			modelStack.Translate(0, i, 0);
			modelStack.Scale(0.5f, 0.7f, 0.5f);
			RenderMesh(meshList[GEO_HORN2], true);
			modelStack.PopMatrix();
			modelStack.PopMatrix();
		}
		modelStack.PushMatrix(); //HeadTop
		modelStack.Translate(0, 10, 0);
		modelStack.PushMatrix();
		modelStack.Translate(0, -20, 0);
		modelStack.PushMatrix();
		modelStack.Rotate(180, 1, 0, 0);
		modelStack.Scale(1.25f, 1.25f, 1.25f);
		RenderMesh(meshList[GEO_HEADCONE], true);
		modelStack.PopMatrix();
		modelStack.Scale(1.25f, 1.25f, 1.25f);
		RenderMesh(meshList[GEO_HEADSPHERE], true);
		modelStack.PopMatrix();
		RenderMesh(meshList[GEO_HEADSPHERE], true);
		modelStack.PopMatrix();
		RenderMesh(meshList[GEO_HEADCYLINDER], true);
		modelStack.PopMatrix();

		modelStack.PopMatrix(); //Head End
		modelStack.Rotate(-45, 1, 0, 0);
		modelStack.Scale(1, 2, 1);
		RenderMesh(meshList[GEO_NECK], true);
		modelStack.PopMatrix();
		modelStack.Scale(1.875f, 2.5f, 1.875f);
		RenderMesh(meshList[GEO_BODYSPHERE], true);
		modelStack.PopMatrix();
		modelStack.PushMatrix(); //Body Back Sphere
		modelStack.Translate(0, 0, 20);
		modelStack.Scale(1.875f, 2.5f, 1.875f);
		RenderMesh(meshList[GEO_BODYSPHERE], true);
		modelStack.PopMatrix();
		modelStack.PushMatrix(); //Legs

		modelStack.PushMatrix(); //Legs Top Cylinder (Front Right Leg)
		modelStack.Translate(8, -20, -20);
		modelStack.Rotate(i->legrotate1, 1, 0, 0);
		modelStack.PushMatrix(); //Legs Sphere
		modelStack.Translate(0, -12.5, 0);
		modelStack.Rotate(i->legrotate2, 1, 0, 0);
		modelStack.PushMatrix(); //Legs Bottom Cylinder
		modelStack.Translate(0, -12.5, 0);
		modelStack.Scale(2.5, 5, 2.5);
		RenderMesh(meshList[GEO_LEGCYLINDER], true);
		modelStack.PopMatrix();
		modelStack.Scale(2.5, 2.5, 2.5);
		RenderMesh(meshList[GEO_LEGSPHERE], true);
		modelStack.PopMatrix();
		modelStack.Scale(2.5, 5, 2.5);
		RenderMesh(meshList[GEO_LEGCYLINDER], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix(); //Legs Top Cylinder (Front Left Leg)
		modelStack.Translate(-8, -20, -20);
		modelStack.Rotate(i->legrotate2, 1, 0, 0);
		modelStack.PushMatrix(); //Legs Sphere
		modelStack.Translate(0, -12.5, 0);
		modelStack.Rotate(i->legrotate1, 1, 0, 0);
		modelStack.PushMatrix(); //Legs Bottom Cylinder
		modelStack.Translate(0, -12.5, 0);
		modelStack.Scale(2.5, 5, 2.5);
		RenderMesh(meshList[GEO_LEGCYLINDER], true);
		modelStack.PopMatrix();
		modelStack.Scale(2.5, 2.5, 2.5);
		RenderMesh(meshList[GEO_LEGSPHERE], true);
		modelStack.PopMatrix();
		modelStack.Scale(2.5, 5, 2.5);
		RenderMesh(meshList[GEO_LEGCYLINDER], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix(); //Legs Top Cylinder (Back Right Leg)
		modelStack.Translate(8, -20, 20);
		modelStack.Rotate(i->legrotate2, 1, 0, 0);
		modelStack.PushMatrix(); //Legs Sphere
		modelStack.Translate(0, -12.5, 0);
		modelStack.Rotate(i->legrotate1, 1, 0, 0);
		modelStack.PushMatrix(); //Legs Bottom Cylinder
		modelStack.Translate(0, -12.5, 0);
		modelStack.Scale(2.5, 5, 2.5);
		RenderMesh(meshList[GEO_LEGCYLINDER], true);
		modelStack.PopMatrix();
		modelStack.Scale(2.5, 2.5, 2.5);
		RenderMesh(meshList[GEO_LEGSPHERE], true);
		modelStack.PopMatrix();
		modelStack.Scale(2.5, 5, 2.5);
		RenderMesh(meshList[GEO_LEGCYLINDER], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix(); //Legs Top Cylinder (Back Left Leg)
		modelStack.Translate(-8, -20, 20);
		modelStack.Rotate(i->legrotate1, 1, 0, 0);
		modelStack.PushMatrix(); //Legs Sphere
		modelStack.Translate(0, -12.5, 0);
		modelStack.Rotate(i->legrotate2, 1, 0, 0);
		modelStack.PushMatrix(); //Legs Bottom Cylinder
		modelStack.Translate(0, -12.5, 0);
		modelStack.Scale(2.5, 5, 2.5);
		RenderMesh(meshList[GEO_LEGCYLINDER], true);
		modelStack.PopMatrix();
		modelStack.Scale(2.5, 2.5, 2.5);
		RenderMesh(meshList[GEO_LEGSPHERE], true);
		modelStack.PopMatrix();
		modelStack.Scale(2.5, 5, 2.5);
		RenderMesh(meshList[GEO_LEGCYLINDER], true);
		modelStack.PopMatrix();

		modelStack.PopMatrix(); //Legs End
		modelStack.Rotate(90, 1, 0, 0);
		modelStack.Scale(1.875f, 2, 2.5f);
		RenderMesh(meshList[GEO_BODYCYLINDER], true);
		modelStack.PopMatrix();
		modelStack.PopMatrix(); //Body End
		modelStack.PopMatrix();
	}
}

void SceneModel::updateGoat(double dt,Vector3 forwhat)
{
	for (auto &i : allgoats)
	{
		bool blocked = false;
		if (((charpos.x) >= i->outermin_x && (charpos.x) <= i->outermax_x) &&
			((charpos.z) >= i->outermin_z && (charpos.z) <= i->outermax_z))
		{
			if (holdingvege)
			{
				if (Application::IsKeyPressed('T'))
					feedgoat(14);
				if (Application::IsKeyPressed('Y'))
					feedgoat(15);
				if (Application::IsKeyPressed('U'))
					feedgoat(16);

				for (auto &j : walls)
				{
					if (((i->min_x) >= j.min_x && (i->min_x) <= j.max_x) &&
						((i->min_z) >= j.min_z && (i->min_z) <= j.max_z))
					{
						blocked = true;
						break;
					}
				}
				i->yrotate = Math::RadianToDegree(acos(Vector3(-1, 0, 0).Dot(forwhat)));
				if (i->yrotate >= acos(Vector3(-1, 0, 0).Dot(-forwhat)))
				{
					i->yrotate = acos(Vector3(-1, 0, 0).Dot(-forwhat));
				}

				if (!blocked)
				{
					i->goatspos.z += 10 * dt * cos(Math::DegreeToRadian(i->yrotate));
					i->goatspos.x += 10 * dt * sin(Math::DegreeToRadian(i->yrotate));
					i->max_x = i->goatspos.x + 5;
					i->max_z = i->goatspos.z + 5;
					i->min_x = i->goatspos.x - 5;
					i->min_z = i->goatspos.z - 5;
					i->outermax_x = i->goatspos.x + 10;
					i->outermax_z = i->goatspos.z + 10;
					i->outermin_x = i->goatspos.x - 10;
					i->outermin_z = i->goatspos.z - 10;
				}
				if (i->frontorreverse == true)
				{
					i->legrotate1 += 80 * dt;
					i->legrotate2 = -i->legrotate1;
					if (i->legrotate1 >= 40)
					{
						i->frontorreverse = false;
					}
				}
				else if (i->frontorreverse == false)
				{
					i->legrotate1 += -80 * dt;
					i->legrotate2 = -i->legrotate1;
					if (i->legrotate1 <= -40)
					{
						i->frontorreverse = true;
					}
				}
			}
			else
			{
				for (auto &j : walls)
				{
					if (((i->min_x) >= j.min_x && (i->min_x) <= j.max_x) &&
						((i->min_z) >= j.min_z && (i->min_z) <= j.max_z))
					{
						blocked = true;
						break;
					}
				}
				i->yrotate = Math::RadianToDegree(acos(Vector3(1, 0, 0).Dot(forwhat)));
				if (!blocked)
				{
					i->goatspos.z -= 10 * dt * cos(Math::DegreeToRadian(i->yrotate));
					i->goatspos.x -= 10 * dt * sin(Math::DegreeToRadian(i->yrotate));
					i->max_x = i->goatspos.x + 5;
					i->max_z = i->goatspos.z + 5;
					i->min_x = i->goatspos.x - 5;
					i->min_z = i->goatspos.z - 5;
					i->outermax_x = i->goatspos.x + 10;
					i->outermax_z = i->goatspos.z + 10;
					i->outermin_x = i->goatspos.x - 10;
					i->outermin_z = i->goatspos.z - 10;
				}
				if (i->frontorreverse == true)
				{
					i->legrotate1 += 80 * dt;
					i->legrotate2 = -i->legrotate1;
					if (i->legrotate1 >= 40)
					{
						i->frontorreverse = false;
					}
				}
				else if (i->frontorreverse == false)
				{
					i->legrotate1 += -80 * dt;
					i->legrotate2 = -i->legrotate1;
					if (i->legrotate1 <= -40)
					{
						i->frontorreverse = true;
					}
				}
			}
		}
	}
}

void SceneModel::plantVege(int vegeno)
{
	if (allvegetables.size())
	{
		for (auto &i : allvegetables)
		{
			if (((charpos.x) >= i->min_x && (charpos.x) <= i->max_x) &&
				((charpos.z) >= i->min_z && (charpos.z) <= i->max_z) && i)
			{
				continue;
			}
			if (vegeno == 1 && potatoseeds)
			{
				vegegrowth* newvege = new vegegrowth;
				newvege->numtype = 14;
				potatoseeds--;
				newvege->growpotato = 0.1;
				newvege->maxsize = 3;
				newvege->vegepos = charpos;
				newvege->vegepos.y = charpos.y - 10;
				newvege->picked = false;
				newvege->onhotbar = false;
				newvege->max_x = charpos.x + newvege->growpotato;
				newvege->max_z = charpos.z + newvege->growpotato;
				newvege->min_x = charpos.x - newvege->growpotato;
				newvege->min_x = charpos.z - newvege->growpotato;
				allvegetables.push_back(newvege);
				break;
			}
			else if (vegeno == 2 && carrotseeds)
			{
				vegegrowth* newvege = new vegegrowth;
				newvege->numtype = 15;
				carrotseeds--;
				newvege->growpotato = 0.1;
				newvege->maxsize = 3;
				newvege->vegepos = charpos;
				newvege->vegepos.y = charpos.y - 10;
				newvege->picked = false;
				newvege->onhotbar = false;
				newvege->max_x = charpos.x + newvege->growpotato;
				newvege->max_z = charpos.z + newvege->growpotato;
				newvege->min_x = charpos.x - newvege->growpotato;
				newvege->min_x = charpos.z - newvege->growpotato;
				allvegetables.push_back(newvege);
				break;
			}
			else if (vegeno == 3 && cabbageseeds)
			{
				vegegrowth* newvege = new vegegrowth;
				newvege->numtype = 16;
				cabbageseeds--;
				newvege->growpotato = 0.1;
				newvege->maxsize = 3;
				newvege->vegepos = charpos;
				newvege->vegepos.y = charpos.y - 10;
				newvege->picked = false;
				newvege->onhotbar = false;
				newvege->max_x = charpos.x + newvege->growpotato;
				newvege->max_z = charpos.z + newvege->growpotato;
				newvege->min_x = charpos.x - newvege->growpotato;
				newvege->min_x = charpos.z - newvege->growpotato;
				allvegetables.push_back(newvege);
				break;
			}
		}
	}
	else
	{
		if (vegeno == 1 && potatoseeds)
		{
			vegegrowth* newvege = new vegegrowth;
			newvege->numtype = 14;
			potatoseeds--;
			newvege->growpotato = 0.1;
			newvege->maxsize = 3;
			newvege->vegepos = charpos;
			newvege->vegepos.y = charpos.y - 10;
			newvege->picked = false;
			newvege->onhotbar = false;
			newvege->max_x = charpos.x + newvege->growpotato;
			newvege->max_z = charpos.z + newvege->growpotato;
			newvege->min_x = charpos.x - newvege->growpotato;
			newvege->min_x = charpos.z - newvege->growpotato;
			allvegetables.push_back(newvege);
		}
		else if (vegeno == 2 && carrotseeds)
		{
			vegegrowth* newvege = new vegegrowth;
			newvege->numtype = 15;
			carrotseeds--;
			newvege->growpotato = 0.1;
			newvege->maxsize = 3;
			newvege->vegepos = charpos;
			newvege->vegepos.y = charpos.y - 10;
			newvege->picked = false;
			newvege->onhotbar = false;
			newvege->max_x = charpos.x + newvege->growpotato;
			newvege->max_z = charpos.z + newvege->growpotato;
			newvege->min_x = charpos.x - newvege->growpotato;
			newvege->min_x = charpos.z - newvege->growpotato;
			allvegetables.push_back(newvege);
		}
		else if (vegeno == 3 && cabbageseeds)
		{
			vegegrowth* newvege = new vegegrowth;
			newvege->numtype = 16;
			cabbageseeds--;
			newvege->growpotato = 0.1;
			newvege->maxsize = 3;
			newvege->vegepos = charpos;
			newvege->vegepos.y = charpos.y - 10;
			newvege->picked = false;
			newvege->onhotbar = false;
			newvege->max_x = charpos.x + newvege->growpotato;
			newvege->max_z = charpos.z + newvege->growpotato;
			newvege->min_x = charpos.x - newvege->growpotato;
			newvege->min_x = charpos.z - newvege->growpotato;
			allvegetables.push_back(newvege);
		}
	}
}

void SceneModel::vegepicked(Vector3 forwhat)
{
	for (auto &i : allvegetables)
	{
		if (i->growpotato > 1)
		{
			if (((charpos.x) >= i->min_x && (charpos.x) <= i->max_x) &&
				((charpos.z) >= i->min_z && (charpos.z) <= i->max_z))
			{
				i->picked = true;
				i->onhotbar = true;
				i->vegepos.x = charpos.x - 10 + forward.x;
				i->vegepos.y = charpos.y - 10 + forward.y;
				i->vegepos.z = charpos.z - 10 + forward.z;
				i->max_x = NULL;
				i->max_z = NULL;
				i->min_x = NULL;
				i->min_z = NULL;
				holdingvege = true;
				if (i->numtype == 14)
					potato++;
				else if (i->numtype == 15)
					carrot++;
				else
					cabbage++;
			}
		}
	}
}

void SceneModel::feedgoat(int no)
{
	int counter = 0;
	for (auto &i : allvegetables)
	{
		auto *j = i;
		if (i->numtype == no && i->picked)
		{
			if (i->numtype == 14)
			{
				potatoseeds += i->growpotato;
				potato--;
			}
			else if (i->numtype == 15)
			{
				carrotseeds += i->growpotato;
				carrot--;
			}
			else
			{
				cabbageseeds += i->growpotato;
				cabbage--;
			}
			allvegetables.erase(allvegetables.begin() + counter);
			break;
		}
		counter++;
	}
}