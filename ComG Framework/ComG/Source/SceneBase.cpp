#include "SceneBase.h"
#include "GL\glew.h"
#include "shader.hpp"
#include "Mtx44.h"
#include "Application.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"
#include "SceneManager.h"
#include "EnemyFactory.h"
#include "Player.h"
#include "EnemyDataBase.h"
#include "ItemDataBase.h"

#include <sstream>

SceneBase::SceneBase()
{
}

SceneBase::~SceneBase()
{
}

void SceneBase::Init()
{
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
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	light[0].LightInit(m_programID);
	//glUseProgram(m_programID);
	forward.z = 1;
	reset = false;
	// Make sure you pass uniform parameters after glUseProgram()
	//Initialize camera settings
	Player::getplayer();
	fp_camera.Init(Player::getplayer()->getRenderer().getPosition() + Vector3(25,50,25) , Player::getplayer()->getRenderer().getForward(), Vector3(0, 1, 0));

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 10000.f);
	projectionStack.LoadMatrix(projection);

	// Make sure you pass uniform parameters after glUseProgram()

	meshList[Player::getplayer()->getID()] = MeshBuilder::GenerateOBJ("player", "OBJ//player.obj");

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad1("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//ground.tga");

	meshList[GEO_SUN] = MeshBuilder::GenerateSphere("sun", Color(1, 1, 0), 5.f);

	for (int i = 0;i<enemyMeshList.size();i++)
	{
		enemyMeshList[i] = MeshBuilder::GenerateOBJ(EnemyDataBase::getEnemyDB()->getEnemy(i+1)->getName(),EnemyDataBase::getEnemyDB()->getEnemy(i+1)->getSourceLocation());
	}

	for (int i = 0; i < weaponmesh.size(); i++)
	{
		weaponmesh[i] = MeshBuilder::GenerateOBJ(ItemDataBase::getItemDB()->getItem(i + 1)->getName(), ItemDataBase::getItemDB()->getItem(i + 1)->getSourceLocation());
	}
	suntimer = 1;
	LoadSkybox();
	Player::getplayer()->gethealth();
}

void SceneBase::Update(double dt)
{
	DebugMode(dt);
	if (Application::IsKeyPressed('E'))
	{
		SceneManager::currScene = 2;
	}
	fp_camera.Update(dt, Player::getplayer()->getRenderer().getPosition() + Vector3(5,5,5), Player::getplayer()->getRenderer().getRight(), Player::getplayer()->getRenderer().getForward(), &camForward, &camRight);
	SpawnEnemy();
	Player::getplayer()->Update(camForward, camRight, dt);
	light[0].LightUpdate(dt);
}

void SceneBase::Render()
{
	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	viewStack.LoadIdentity();
	
	viewStack.LookAt(fp_camera.position.x, fp_camera.position.y,
		fp_camera.position.z, fp_camera.target.x, fp_camera.target.y,
		fp_camera.target.z, fp_camera.up.x, fp_camera.up.y, fp_camera.up.z);

	modelStack.LoadIdentity();

	light[0].LightRender(viewStack);

	RenderMesh(meshList[GEO_AXES], false);

	RenderSkybox();

	modelStack.PushMatrix();
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_QUAD], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.LoadMatrix(Player::getplayer()->getRenderer().getMatrix());
	RenderMesh(meshList[0], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.LoadMatrix(Player::getplayer()->getWeapon()->getRenderer().getMatrix());
	RenderMesh(weaponmesh[0], true);
	modelStack.PopMatrix();

	RenderEnemy();
}

void SceneBase::Exit()
{
	glDeleteProgram(m_programID);
	glDeleteVertexArrays(1, &m_vertexArrayID);
}

void SceneBase::RenderMesh(Mesh *mesh, bool enableLight)
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

void SceneBase::LoadSkybox()
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

void SceneBase::RenderSkybox()
{
	modelStack.PushMatrix();
	modelStack.Translate(10, 0, 10);
	modelStack.PushMatrix();
	modelStack.Scale(1000, 1000, 1000);
	modelStack.PushMatrix();
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Rotate(270, 1, 0, 0);
	modelStack.Translate(0, 0.5, 0);

	if (light[0].Lightgetsunup() == 1)
		RenderMesh(meshList[GEO_LEFT], false);

	else if(light[0].Lightgetsunup() == 2)
		RenderMesh(meshList[GEO_LEFT1], false);

	else if (light[0].Lightgetsunup() == 3)
		RenderMesh(meshList[GEO_LEFT2], false);

	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Translate(0, -0.5, 0);
	modelStack.Scale(1, 1, -1);

	if (light[0].Lightgetsunup() == 1)
		RenderMesh(meshList[GEO_BOTTOM], false);

	else if (light[0].Lightgetsunup() == 2)
		RenderMesh(meshList[GEO_BOTTOM1], false);

	else if (light[0].Lightgetsunup() == 3)
		RenderMesh(meshList[GEO_BOTTOM2], false);

	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Translate(0, 0.5, 0);

	if (light[0].Lightgetsunup() == 1)
		RenderMesh(meshList[GEO_RIGHT], false);

	else if (light[0].Lightgetsunup() == 2)
		RenderMesh(meshList[GEO_RIGHT1], false);

	else if (light[0].Lightgetsunup() == 3)
		RenderMesh(meshList[GEO_RIGHT2], false);

	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(0.5, 0, 0);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Rotate(180, 1, 0, 0);

	if (light[0].Lightgetsunup() == 1)
		RenderMesh(meshList[GEO_BACK], false);

	else if (light[0].Lightgetsunup() == 2)
		RenderMesh(meshList[GEO_BACK1], false);

	else if (light[0].Lightgetsunup() == 3)
		RenderMesh(meshList[GEO_BACK2], false);

	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Translate(0, 0.5, 0);

	if (light[0].Lightgetsunup() == 1)
		RenderMesh(meshList[GEO_TOP], false);

	else if (light[0].Lightgetsunup() == 2)
		RenderMesh(meshList[GEO_TOP1], false);

	else if (light[0].Lightgetsunup() == 3)
		RenderMesh(meshList[GEO_TOP2], false);

	modelStack.PopMatrix();
	modelStack.Translate(-0.5, 0, 0);
	modelStack.Rotate(90, 0, 0, 1);

	if (light[0].Lightgetsunup() == 1)
		RenderMesh(meshList[GEO_FRONT], false);

	else if (light[0].Lightgetsunup() == 2)
		RenderMesh(meshList[GEO_FRONT1], false);

	else if (light[0].Lightgetsunup() == 3)
		RenderMesh(meshList[GEO_FRONT2], false);

	modelStack.PopMatrix();
	modelStack.PopMatrix();
}

void SceneBase::DebugMode(double dt)
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

void SceneBase::RenderText(Mesh* mesh, std::string text, Color color)
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

void SceneBase::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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

void SceneBase::SpawnEnemy()
{
	if (BaseEnemy.size() < 5)
		BaseEnemy.push_back(EnemyFactory::getEnemyFactory()->generateEnemy(1));
}

void SceneBase::RenderEnemy()
{
	int y = 0;
	for (auto &i : BaseEnemy)
	{
		modelStack.PushMatrix();
		modelStack.Translate(0, y, 0);
		RenderMesh(enemyMeshList[i->getID()], true);
		modelStack.PopMatrix();
		y++;
	}
}