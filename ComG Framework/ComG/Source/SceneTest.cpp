
#include "SceneTest.h"
#include "GL\glew.h"
#include "shader.hpp"
#include "Mtx44.h"
#include "Application.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"
#include "SceneManager.h"
#include "EnemyFactory.h"
#include "BuildingFactory.h"
#include "Player.h"
#include "EnemyDataBase.h"
#include "ItemDataBase.h"
#include "BuildingDataBase.h"
#include "SaveLoad.h"
#include <sstream>

POINT cursorPoint;

SceneTest::SceneTest() : buildingID(101)
{
	cursorX = 0;
	cursorY = 0;

	windowX = windowY = 0;
	cursorPoint.x = cursorPoint.y = 0;

	glfwGetWindowSize(Application::m_window, &windowX, &windowY);
	glfwSetCursorPos(Application::m_window, windowX / 2, windowY / 2);
}

SceneTest::~SceneTest()
{
}

void SceneTest::Init()
{
	//sunup = 1;
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
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
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
	forward.z = 1;
	lighting.y = 1.f;
	reset = false;
	sunup = true;
	sunrotate = 100;
	Day = 0;

	pause = false;
	options = false;
	pauseHighlight = 0;
	optionHighlight = 0;

	start = std::clock();

	// Make sure you pass uniform parameters after glUseProgram()
	//Initialize camera settings
	Player::getplayer();
	fp_camera.Init(Player::getplayer()->getRenderer().getPosition() + Vector3(25, 50, 25), Player::getplayer()->getRenderer().getForward(), Vector3(0, 1, 0));

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 10000.f);
	projectionStack.LoadMatrix(projection);

	// Make sure you pass uniform parameters after glUseProgram()
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
	//meshList[Player::getplayer()->getID()] = MeshBuilder::GenerateOBJ("player", "OBJ//player.obj");

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad1("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//ground.tga");

	meshList[GEO_SUN] = MeshBuilder::GenerateSphere("sun", Color(1, 1, 0), 5.f);

	meshList[GEO_CURSOR] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_CURSOR]->textureID = LoadTGA("Image//cursorPointer.tga");

	meshList[GEO_PAUSEMENU] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_PAUSEMENU]->textureID = LoadTGA("Image//Pause Menu.tga");

	meshList[GEO_OPTIONS] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_OPTIONS]->textureID = LoadTGA("Image//pauseMenu - Options.tga");

	meshList[GEO_BACKTOGAME] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_BACKTOGAME]->textureID = LoadTGA("Image//pauseMenu - BackToGame.tga");

	meshList[GEO_BACKTOMAIN] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_BACKTOMAIN]->textureID = LoadTGA("Image//pauseMenu - BackToMainMenu.tga");

	meshList[GEO_OPTIONSMENU] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_OPTIONSMENU]->textureID = LoadTGA("Image//Options Menu.tga");

	meshList[GEO_MOUSE] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_MOUSE]->textureID = LoadTGA("Image//Options Menu Mouse.tga");

	meshList[GEO_VOLUME] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_VOLUME]->textureID = LoadTGA("Image//Options Menu Volume.tga");

	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//Options Menu Back.tga");

	for (int i = 0; i<enemyMeshList.size(); i++)
	{
		enemyMeshList[i] = MeshBuilder::GenerateOBJ(EnemyDataBase::getEnemyDB()->getEnemy(i + 1)->getName(), EnemyDataBase::getEnemyDB()->getEnemy(i + 1)->getSourceLocation());
		enemyMeshList[i]->textureID = LoadTGA(EnemyDataBase::getEnemyDB()->getEnemy(i + 1)->getTextureLocation());
	}
	for (int i = 0; i<buildingMeshList.size(); i++)
	{
		buildingMeshList[i] = MeshBuilder::GenerateOBJ(BuildingDataBase::getBuildingDB()->getBuilding(100 + i + 1)->getName(), BuildingDataBase::getBuildingDB()->getBuilding(100 + i + 1)->getSourceLocation());
		buildingMeshList[i]->textureID = LoadTGA(BuildingDataBase::getBuildingDB()->getBuilding(100 + i + 1)->getTextureLocation());
	}
	for (int i = 0; i < weaponmesh.size(); i++)
	{
		weaponmesh[i] = MeshBuilder::GenerateOBJ(ItemDataBase::getItemDB()->getItem(300 + i + 7)->getName(), ItemDataBase::getItemDB()->getItem(300 + i + 7)->getSourceLocation());
		weaponmesh[i]->textureID = LoadTGA(ItemDataBase::getItemDB()->getItem(300 + i + 7)->getTextureLocation());
	}
	suntimer = 1;
	LoadSkybox();
	Player::getplayer()->setWeapon(307);
	fp_camera.Update(0, Player::getplayer()->getRenderer().getPosition() + Vector3(0, 2, 0), Player::getplayer()->getRenderer().getRight(), Player::getplayer()->getRenderer().getForward(), &camForward, &camRight);
	SaveLoad::Load(1, "Base", BaseBuildings, BaseEnemy);
}

void SceneTest::Update(double dt)
{
	DebugMode(dt);

	glfwGetCursorPos(Application::m_window, &cursorX, &cursorY);
	cursorY = -cursorY + 600;

	elapsedTime = (std::clock() - start) / (int)CLOCKS_PER_SEC;

	if (Application::IsKeyPressed('E'))
	{
		SceneManager::currScene = 3;
	}
	
	if (Application::IsKeyPressed(VK_ESCAPE) && elapsedTime > 0.01)
	{
		if (!pause)
		{
			fp_camera.is_menu = true;
			pause = true;
		}
		else if (pause)
		{
			pauseHighlight = 0;
			optionHighlight = 0;

			glfwSetCursorPos(Application::m_window, windowX / 2, windowY / 2);
			fp_camera.is_menu = false;
			pause = false;
		}
		start = std::clock();
	}

	if (pause)
	{
		if (elapsedTime > 0.01)
		{
			if (Application::IsKeyPressed(VK_UP))
			{
				if (pauseHighlight >= 0)
				{
					pauseHighlight--;
				}
				if (pauseHighlight < 0)
				{
					pauseHighlight = 2;
				}
				start = std::clock();
			}
			if (Application::IsKeyPressed(VK_DOWN))
			{
				if (pauseHighlight < 3)
				{
					pauseHighlight++;
				}
				if (pauseHighlight > 2)
				{
					pauseHighlight = 0;
				}
				start = std::clock();
			}
			if (cursorY >= 285 && cursorY <= 325)
			{
				pauseHighlight = 0;
			}
			if (cursorY >= 180 && cursorY <= 225)
			{
				pauseHighlight = 1;
			}
			if (cursorY >= 75 && cursorY <= 120)
			{
				pauseHighlight = 2;
			}
			if (Application::IsKeyPressed(VK_RETURN) || Application::IsKeyPressed(VK_LBUTTON))
			{
				if (pauseHighlight == 0)
				{

				}
				if (pauseHighlight == 1)
				{
					pauseHighlight = 0;
					optionHighlight = 0;

					glfwSetCursorPos(Application::m_window, windowX / 2, windowY / 2);
					fp_camera.is_menu = false;
					pause = false;
				}
				if (pauseHighlight == 2)
				{
					pauseHighlight = 0;
					optionHighlight = 0;

					glfwSetCursorPos(Application::m_window, windowX / 2, windowY / 2);
					fp_camera.is_menu = false;
					pause = false;

					SceneManager::currScene = 2;
				}
			}
		}
	}

	fp_camera.Update(dt, Player::getplayer()->getRenderer().getPosition() + Vector3(0, 2, 0), Player::getplayer()->getRenderer().getRight(), Player::getplayer()->getRenderer().getForward(), &camForward, &camRight);
	//	if (allbuildingcollision(Player::getplayer()))
	{
		Player::getplayer()->Update(camForward, camRight, dt);
	}

	SpawnEnemy(dt);
	LightUpdate(dt);
	SpawnBuilding(dt);
}

void SceneTest::Render()
{
	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	viewStack.LoadIdentity();

	viewStack.LookAt(fp_camera.position.x, fp_camera.position.y,
		fp_camera.position.z, fp_camera.target.x, fp_camera.target.y,
		fp_camera.target.z, fp_camera.up.x, fp_camera.up.y, fp_camera.up.z);

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
	RenderMesh(meshList[GEO_QUAD], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.LoadMatrix(Player::getplayer()->getWeapon()->getRenderer().getMatrix());
	RenderMesh(weaponmesh[0], true);
	modelStack.PopMatrix();

	RenderEnemy();
	RenderBuilding();

	if (pause)
	{
		RenderMeshOnScreen(meshList[GEO_PAUSEMENU], 40, 30, 16, 12);

		if (pauseHighlight == 0)
		{
			RenderMeshOnScreen(meshList[GEO_OPTIONS], 40, 30, 16, 12);
		}
		if (pauseHighlight == 1)
		{
			RenderMeshOnScreen(meshList[GEO_BACKTOGAME], 40, 30, 16, 12);
		}
		if (pauseHighlight == 2)
		{
			RenderMeshOnScreen(meshList[GEO_BACKTOMAIN], 40, 30, 16, 12);
		}

		RenderMeshOnScreen(meshList[GEO_CURSOR], cursorX / 10, cursorY / 10, 8, 10);
	}
}

void SceneTest::Exit()
{
	glDeleteProgram(m_programID);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	SaveLoad::Save(1, "Base", BaseBuildings, BaseEnemy);
}

void SceneTest::RenderMesh(Mesh *mesh, bool enableLight)
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

void SceneTest::LoadSkybox()
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

void SceneTest::RenderSkybox()
{
	modelStack.PushMatrix();
	modelStack.Translate(10, 0, 10);
	modelStack.PushMatrix();
	modelStack.Scale(1000, 1000, 1000);
	modelStack.PushMatrix();
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Rotate(270, 1, 0, 0);
	modelStack.Translate(0, 0.5, 0);

	if (sunup == 1)
		RenderMesh(meshList[GEO_LEFT], false);

	else if (sunup == 2)
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

void SceneTest::DebugMode(double dt)
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

void SceneTest::RenderText(Mesh* mesh, std::string text, Color color)
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

void SceneTest::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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

void SceneTest::SpawnEnemy(double dt)
{
	if (BaseEnemy.size() < 5)
		BaseEnemy.push_back(EnemyFactory::getEnemyFactory()->generateEnemy(1));

	for (auto &i : BaseEnemy)
	{
		i->Update(dt);
	}
}

void SceneTest::RenderEnemy()
{
	int y = 0;
	for (auto &i : BaseEnemy)
	{
		modelStack.PushMatrix();
		modelStack.LoadMatrix((i->getRenderer().getMatrix()));
		RenderMesh(enemyMeshList[i->getID() - 1], true);
		modelStack.PopMatrix();
		y++;
	}
}

void SceneTest::SpawnBuilding(double dt)
{
	for (int u = 0; u < NUM_GEOMETRY; u++){
		if (BaseBuildings.size() < NUM_BUILDINGGEOMETRY)
		{
			BaseBuildings.push_back(BuildingFactory::getBuildingFactory()->generateBuilding(u + buildingID));
		}
	}

	for (auto &i : BaseBuildings)
	{
		i->update(dt);
	}
}

void SceneTest::RenderBuilding()
{
	int y = 0;
	for (auto &i : BaseBuildings)
	{
		modelStack.PushMatrix();
		modelStack.LoadMatrix((i->getRenderer().getMatrix()));
		RenderMesh(buildingMeshList[i->getID() - buildingID], true);
		modelStack.PopMatrix();
		y++;
	}
}

void SceneTest::RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey)
{
	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Translate(x, y, 0);
	modelStack.Scale(sizex, sizey, 1);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(mesh, false);
	modelStack.PopMatrix();
	viewStack.PopMatrix();
	projectionStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

bool SceneTest::allbuildingcollision(GameObject* test)
{
	if (!BaseBuildings.size())
		return 1;
	for (auto &i : BaseBuildings)
	{
		if (i->getAABB(0)->pointtoAABB(test->getRenderer().getPosition()))
		{
			return false;
		}

	}
}

void SceneTest::LightUpdate(double dt)
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
		light[0].power = 0.25;
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

	if (sunrotate >= 360)
	{
		sunrotate -= 360;
		Day++;
	}

	//std::cout << "Lighting Level: " << lighting.y << std::endl;
	std::cout << "Day: " << Day << std::endl;
	std::cout << "sunrotate: " << sunrotate << std::endl;
}

void SceneTest::LightReset(double dt)
{
	suntimer = 20;
	reset = true;
}