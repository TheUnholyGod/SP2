#include "SceneMainMenu.h"
#include "GL\glew.h"
#include "shader.hpp"
#include "Mtx44.h"
#include "Application.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"
#include "SceneManager.h"
#include "Camera3.h"

#include <sstream>

POINT cursorPoint;

SceneMainMenu::SceneMainMenu()
{
}

SceneMainMenu::~SceneMainMenu()
{
}

void SceneMainMenu::Init()
{
	cursorX = 0;
	cursorY = 0;

	windowX = windowY = 0;
	cursorPoint.x = cursorPoint.y = 0;

	glfwGetWindowSize(Application::m_window, &windowX, &windowY);
	glfwSetCursorPos(Application::m_window,windowX / 2, windowY / 2);

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

	//glUseProgram(m_programID);
	forward.z = 1;

	options = false;

	play = 1;
	back = false;

	start = std::clock();

	// Make sure you pass uniform parameters after glUseProgram()
	//Initialize camera settings

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 10000.f);
	projectionStack.LoadMatrix(projection);

	// Make sure you pass uniform parameters after glUseProgram()

	//Cursor
	meshList[GEO_CURSOR] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_CURSOR]->textureID = LoadTGA("Image//cursorPointer.tga");

	//Main Menu
	meshList[GEO_MAINMENU] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_MAINMENU]->textureID = LoadTGA("Image//Main Menu.tga");

	meshList[GEO_PLAY] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_PLAY]->textureID = LoadTGA("Image//Main Menu Play.tga");

	meshList[GEO_OPTIONS] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_OPTIONS]->textureID = LoadTGA("Image//Main Menu Options.tga");

	meshList[GEO_EXIT] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_EXIT]->textureID = LoadTGA("Image//Main Menu Exit.tga");

	//Options Menu
	meshList[GEO_OPTIONSMENU] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_OPTIONSMENU]->textureID = LoadTGA("Image//Options Menu.tga");
}

void SceneMainMenu::Update(double dt)
{
	glfwGetCursorPos(Application::m_window, &cursorX, &cursorY);
	cursorY = -cursorY + 600;

	elapsedTime = (std::clock() - start) / (int)CLOCKS_PER_SEC;
	DebugMode(dt);

	if (!options)
	{
		if (elapsedTime > 0.01)
		{
			if (Application::IsKeyPressed(VK_RIGHT))
			{
				if (play < 3)
				{
					play++;
				}
				if (play > 2)
				{
					play = 0;
				}
				start = std::clock();
			}
			if (Application::IsKeyPressed(VK_LEFT))
			{
				if (play >= 0)
				{
					play--;
				}
				if (play < 0)
				{
					play = 2;
				}
				start = std::clock();
			}

			if (Application::IsKeyPressed(VK_RETURN))
			{

				if (play == 0)
				{
					Application::IsExit = true;

				}
				if (play == 1)
				{
					options = false;
					SceneManager::currScene = 4;
				}
				if (play == 2)
				{
					options = true;
				}
				start = std::clock();
			}
		}
	}
	if (options)
	{
		if (elapsedTime > 0.01)
		{
			if (Application::IsKeyPressed(VK_UP))
			{
				if (optionHighlight < 3)
				{
					optionHighlight++;
				}
				if (optionHighlight > 2)
				{
					optionHighlight = 0;
				}
				start = std::clock();
			}
			if (Application::IsKeyPressed(VK_DOWN))
			{
				if (optionHighlight >= 0)
				{
					optionHighlight--;
				}
				if (optionHighlight < 0)
				{
					optionHighlight = 2;
				}
				start = std::clock();
			}

			if (Application::IsKeyPressed(VK_RETURN))
			{

				if (optionHighlight == 0)
				{


				}
				if (optionHighlight == 1)
				{

				}
				if (optionHighlight == 2)
				{

				}
				start = std::clock();
			}
		}
	}
}

void SceneMainMenu::Render()
{
	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	viewStack.LoadIdentity();

	viewStack.LookAt(fp_camera.position.x, fp_camera.position.y,
		fp_camera.position.z, fp_camera.target.x, fp_camera.target.y,
		fp_camera.target.z, fp_camera.up.x, fp_camera.up.y, fp_camera.up.z);

	modelStack.LoadIdentity();

	if (!options)
	{
		RenderMeshOnScreen(meshList[GEO_MAINMENU], 40, 30, 16, 12);

		if (play == 0)
		{
			RenderMeshOnScreen(meshList[GEO_EXIT], 40, 30, 16, 12);
		}
		if (play == 1)
		{
			RenderMeshOnScreen(meshList[GEO_PLAY], 40, 30, 16, 12);
		}
		if (play == 2)
		{
			RenderMeshOnScreen(meshList[GEO_OPTIONS], 40, 30, 16, 12);
		}
	}
	else if (options)
	{
		RenderMeshOnScreen(meshList[GEO_OPTIONSMENU], 40, 30, 16, 12);

		if (play == 0)
		{

		}
		if (play == 1)
		{
			//RenderMeshOnScreen(meshList[GEO_VOLUME], 40, 30, 16, 12);
		}
		if (play == 2)
		{
			//RenderMeshOnScreen(meshList[GEO_BACK], 40, 30, 16, 12);
		}
	}

	RenderMeshOnScreen(meshList[GEO_CURSOR], cursorX / 10, cursorY / 10, 10, 10);
}

void SceneMainMenu::Exit()
{
	glDeleteProgram(m_programID);
	glDeleteVertexArrays(1, &m_vertexArrayID);
}

void SceneMainMenu::RenderMesh(Mesh *mesh, bool enableLight)
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

void SceneMainMenu::DebugMode(double dt)
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

void SceneMainMenu::RenderText(Mesh* mesh, std::string text, Color color)
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

void SceneMainMenu::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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

void SceneMainMenu::RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey)
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