#include "SceneMainMenu.h"
#include "GL\glew.h"
#include "shader.hpp"
#include "Mtx44.h"
#include "Application.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"
#include "SceneManager.h"
#include "Menu.h"
#include "Camera3.h"
#include "SaveLoad.h"
#include "Player.h"

extern POINT cursorPoint;

SceneMainMenu::SceneMainMenu()
{
}

SceneMainMenu::~SceneMainMenu()
{
}

void SceneMainMenu::Init()
{
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

	// Make sure you pass uniform parameters after glUseProgram()
	//Initialize camera settings

	Mtx44 projection;
	projection.SetToPerspective(45.f, 16.f / 9.f, 0.1f, 10000.f);
	projectionStack.LoadMatrix(projection);

	// Make sure you pass uniform parameters after glUseProgram()

	//Cursor
	meshList[GEO_CURSOR] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_CURSOR]->textureID = LoadTGA("Image//cursorPointer.tga");
	meshList[GEO_CURSORPOS] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_CURSORPOS]->textureID = LoadTGA("Image//calibri.tga");

	//Main Menu
	meshList[GEO_MAINMENU] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 1.f);
	meshList[GEO_MAINMENU]->textureID = LoadTGA("Image//Main Menu.tga");

	meshList[GEO_PLAY] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_PLAY]->textureID = LoadTGA("Image//Main Menu Play.tga");

	meshList[GEO_OPTIONS] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_OPTIONS]->textureID = LoadTGA("Image//Main Menu Options.tga");

	meshList[GEO_EXIT] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_EXIT]->textureID = LoadTGA("Image//Main Menu Exit.tga");

	//Options Menu
	meshList[GEO_OPTIONSMENU] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_OPTIONSMENU]->textureID = LoadTGA("Image//optionsMenu 2.tga");

	meshList[GEO_MOUSE] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_MOUSE]->textureID = LoadTGA("Image//optionsMenu - Mouse.tga");

	meshList[GEO_VOLUME] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_VOLUME]->textureID = LoadTGA("Image//optionsMenu - Volume.tga");

	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//optionsMenu - Back.tga");

	//SaveGame Menu
	meshList[GEO_SAVELOADMENU] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_SAVELOADMENU]->textureID = LoadTGA("Image//SaveGame - Main.tga");

	meshList[GEO_LOAD] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_LOAD]->textureID = LoadTGA("Image//SaveGame - Load Game.tga");

	meshList[GEO_SAVE] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_SAVE]->textureID = LoadTGA("Image//SaveGame - New Game.tga");

	meshList[GEO_1SAVE] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_1SAVE]->textureID = LoadTGA("Image//SaveGame - Load Game - 1.tga");

	meshList[GEO_2SAVE] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_2SAVE]->textureID = LoadTGA("Image//SaveGame - Load Game - 2.tga");

	meshList[GEO_3SAVE] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_3SAVE]->textureID = LoadTGA("Image//SaveGame - Load Game - 3.tga");

	meshList[GEO_4SAVE] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_4SAVE]->textureID = LoadTGA("Image//SaveGame - Load Game - 4.tga");

	meshList[GEO_5SAVE] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_5SAVE]->textureID = LoadTGA("Image//SaveGame - Load Game - 5.tga");

	meshList[GEO_CURSOR] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_CURSOR]->textureID = LoadTGA("Image//cursorPointer.tga");
	meshList[GEO_CURSOR1] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_CURSOR1]->textureID = LoadTGA("Image//cursorPointer - 2.tga");
	meshList[GEO_CURSOR2] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_CURSOR2]->textureID = LoadTGA("Image//cursorPointer - 3.tga");
	meshList[GEO_CURSOR3] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_CURSOR3]->textureID = LoadTGA("Image//cursorPointer - 4.tga");

	meshList[GEO_MOUSEMENU] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_MOUSEMENU]->textureID = LoadTGA("Image//MouseSelect.tga");

	cursorX = 0;
	cursorY = 0;

	windowX = windowY = 0;
	cursorPoint.x = cursorPoint.y = 0;

	//glfwGetWindowSize(Application::m_window, &windowX, &windowY);
	glfwSetCursorPos(Application::m_window, windowX / 2, windowY / 2);

	options = false;
	optionHighlight = 0;
	mouseMenu = false;
	mouse = 0;
	mouseSelection = 0;

	loadEmpty[5] = { false };

	play = 1;
	back = false;
	isPlay = 0;
	load = 0;
}

void SceneMainMenu::Update(double dt)
{
	glfwGetWindowSize(Application::m_window, &windowX, &windowY);
	glfwGetCursorPos(Application::m_window, &cursorX, &cursorY);
	cursorY = -cursorY + windowY;

	if (cursorX > 800)
	{
		cursorX = 800;
		glfwSetCursorPos(Application::m_window, cursorX, -cursorY + windowY);
	}
	if (cursorY > 600)
	{
		cursorY = 600;
		glfwSetCursorPos(Application::m_window, cursorX, -cursorY + windowY);
	}


	elapsedTime = (std::clock() - start) / (int)CLOCKS_PER_SEC;
	DebugMode(dt);

	if (!options && !mouseMenu)
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
				start = std::clock();
				if (play == 0)
				{
					Application::IsExit = true;
				}
				if (play == 1)
				{
					options = false;
					isPlay = true;
				}
				if (play == 2)
				{
					options = true;
				}
			}
			if (Application::IsKeyPressed(VK_LBUTTON))
			{
				if ((cursorX >= 150 && cursorX <= 240) && (cursorY >= 260 && cursorY <= 300)) //Click on Left Arrows '<<'
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
				else if ((cursorX >= 560 && cursorX <= 650) && (cursorY >= 260 && cursorY <= 300)) //Click on Right Arrows '>>'
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
				else if ((cursorX >= 240 && cursorX <= 560) && (cursorY >= 260 && cursorY <= 300)) //Click on Word 'Play' 'Options' 'Exit'
				{
					if (play == 0)
					{
						Application::IsExit = true;
					}
					if (play == 1)
					{
						options = false;
						isPlay = true;
					}
					if (play == 2)
					{
						options = true;
						mouseMenu = false;
					}
					start = std::clock();
				}
				start = std::clock();
			}
		}
	}
	if (options && !mouseMenu)
	{
		if (elapsedTime > 0.05)
		{
			if (Application::IsKeyPressed(VK_UP))
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
			if (Application::IsKeyPressed(VK_DOWN))
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
			if (cursorY >= 340 && cursorY <= 390)
			{
				optionHighlight = 0;
			}
			if (cursorY >= 190 && cursorY <= 230)
			{
				optionHighlight = 1;
			}
			if (cursorY >= 40 && cursorY <= 80)
			{
				optionHighlight = 2;
			}
			if (Application::IsKeyPressed(VK_RETURN))
			{
				if (optionHighlight == 0) //Mouse
				{
					options = false;
					mouseMenu = true;
					start = std::clock();
				}
				if (optionHighlight == 1) //Volume - WIP
				{
					//No time to implement.
					start = std::clock();
				}
				if (optionHighlight == 2) //Back to Main Menu
				{
					play = 1;
					optionHighlight = 0;
					options = false;
					start = std::clock();
				}
				start = std::clock();
			}
			if (Application::IsKeyPressed(VK_LBUTTON))
			{
				if (cursorY >= 340 && cursorY <= 390)
				{
					options = false;
					mouseMenu = true;
					start = std::clock();
				}
				if (cursorY >= 190 && cursorY <= 230)
				{
					//No time to implement.
					start = std::clock();
				}
				if (cursorY >= 40 && cursorY <= 80)
				{
					play = 1;
					optionHighlight = 0;
					options = false;
					start = std::clock();
				}
			}
		}
	}

	if (isPlay)
	{
		for (int i = 0; i < 5; i++)
		{
			loadEmpty[i] = SaveLoad::is_empty(i + 1);
		}

		if (Application::IsKeyPressed(VK_LBUTTON) && elapsedTime > 0.001)
		{
			if ((cursorX >= 690 && cursorX <= 770) && (cursorY >= 50 && cursorY <= 110)) //Back Button
			{
				if (load == 0)
				{
					isPlay = false;
				}
				else
				{
					load = 0;
				}
				start = std::clock();
			}

			else if (load == 0) //Continue / New Game menu
			{
				if ((cursorY >= 330 && cursorY <= 390) && (cursorX >= 170 && cursorX <= 640))
				{
					load = 2;
				}
				if ((cursorY >= 180 && cursorY <= 240) && (cursorX >= 160 && cursorX <= 650))
				{
					load = 1;
				}
			}
			else if (load == 1) //Load Game menu
			{
				if (((cursorY >= 370 && cursorY <= 425) && (cursorX >= 600 && cursorX <= 670)) && !loadEmpty[0]) //Save 1
				{
					Application::saveno = 1;
					SceneManager::currScene = 4;
				}
				if (((cursorY >= 290 && cursorY <= 350) && (cursorX >= 600 && cursorX <= 670)) && !loadEmpty[1]) //Save 2
				{
					Application::saveno = 2;
					SceneManager::currScene = 4;
				}
				if (((cursorY >= 210 && cursorY <= 260) && (cursorX >= 600 && cursorX <= 670)) && !loadEmpty[2]) //Save 3
				{
					Application::saveno = 3;
					SceneManager::currScene = 4;
				}
				if (((cursorY >= 130 && cursorY <= 190) && (cursorX >= 600 && cursorX <= 670)) && !loadEmpty[3]) //Save 4
				{
					Application::saveno = 4;
					SceneManager::currScene = 4;
				}
				if (((cursorY >= 40 && cursorY <= 100) && (cursorX >= 600 && cursorX <= 670)) && !loadEmpty[4]) //Save 5
				{
					Application::saveno = 5;
					SceneManager::currScene = 4;
				}
			}
			else if(load == 2) //New Game menu
			{
				if (((cursorY >= 370 && cursorY <= 425) && (cursorX >= 600 && cursorX <= 670)) && loadEmpty[0]) //Save 1
				{
					Application::saveno = 1;
					SaveLoad::NewGame(Application::saveno);
					SceneManager::currScene = 4;
				}
				if (((cursorY >= 290 && cursorY <= 350) && (cursorX >= 600 && cursorX <= 670)) && loadEmpty[1]) //Save 2
				{
					Application::saveno = 2;
					SaveLoad::NewGame(Application::saveno);
					SceneManager::currScene = 4;
				}
				if (((cursorY >= 210 && cursorY <= 260) && (cursorX >= 600 && cursorX <= 670)) && loadEmpty[2]) //Save 3
				{
					Application::saveno = 3;
					SaveLoad::NewGame(Application::saveno);
					SceneManager::currScene = 4;
				}
				if (((cursorY >= 130 && cursorY <= 190) && (cursorX >= 600 && cursorX <= 670)) && loadEmpty[3]) //Save 4
				{
					Application::saveno = 4;
					SaveLoad::NewGame(Application::saveno);
					SceneManager::currScene = 4;
				}
				if (((cursorY >= 40 && cursorY <= 100) && (cursorX >= 600 && cursorX <= 670)) && loadEmpty[4]) //Save 5
				{
					Application::saveno = 5;
					SaveLoad::NewGame(Application::saveno);
					SceneManager::currScene = 4;
				}
			}
		}
	}
	if (mouseMenu)
	{
		if (elapsedTime > 0.01)
		{
			if (Application::IsKeyPressed(VK_LEFT))
			{
				if (mouseSelection >= 0)
				{
					mouseSelection--;
				}
				if (mouseSelection < 0)
				{
					mouseSelection = 3;
				}
				start = std::clock();
			}
			if (Application::IsKeyPressed(VK_RIGHT))
			{
				if (mouseSelection < 4)
				{
					mouseSelection++;
				}
				if (mouseSelection > 3)
				{
					mouseSelection = 0;
				}
				start = std::clock();
			}

			if (Application::IsKeyPressed(VK_RETURN))
			{
				Player::getplayer()->setMouse(mouseSelection);
				mouseMenu = false;
				start = std::clock();
			}
			if (Application::IsKeyPressed(VK_LBUTTON))
			{
				if ((cursorX >= 120 && cursorX <= 170) && (cursorY >= 220 && cursorY <= 270))
				{
					if (mouseSelection >= 0)
					{
						mouseSelection--;
					}
					if (mouseSelection < 0)
					{
						mouseSelection = 3;
					}
					start = std::clock();
				}
				if ((cursorX >= 630 && cursorX <= 670) && (cursorY >= 220 && cursorY <= 270))
				{
					if (mouseSelection < 4)
					{
						mouseSelection++;
					}
					if (mouseSelection > 3)
					{
						mouseSelection = 0;
					}
					start = std::clock();
				}
				if ((cursorX >= 195 && cursorX <= 600) && (cursorY >= 70 && cursorY <= 130))
				{
					Player::getplayer()->setMouse(mouseSelection);
					mouseMenu = false;
					start = std::clock();
				}
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

	if (!options && !mouseMenu)
	{
		RenderMeshOnScreen(meshList[GEO_MAINMENU], 40, 30, 80, 60);

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
	else if (options && !mouseMenu)
	{
		RenderMeshOnScreen(meshList[GEO_OPTIONSMENU], 40, 30, 16, 12);

		if (optionHighlight == 0)
		{
			RenderMeshOnScreen(meshList[GEO_MOUSE], 40, 30, 16, 12);
		}
		if (optionHighlight == 1)
		{
			RenderMeshOnScreen(meshList[GEO_VOLUME], 40, 30, 16, 12);
		}
		if (optionHighlight == 2)
		{
			RenderMeshOnScreen(meshList[GEO_BACK], 40, 30, 16, 12);
		}
	}
	
	if (isPlay)
	{
		if (load == 0)
		{
			RenderMeshOnScreen(meshList[GEO_SAVELOADMENU], 40, 30, 16, 12);
		}
		else if (load == 1)
		{
			RenderMeshOnScreen(meshList[GEO_LOAD], 40, 30, 16, 12);

			if (!loadEmpty[0])
			{
				RenderMeshOnScreen(meshList[GEO_1SAVE], 40, 30, 16, 12);

				if ((cursorY >= 310 && cursorY <= 360) && (cursorX >= 410 && cursorX <= 480)) //Mouse Over Save 1
				{

				}
			}
			if (!loadEmpty[1])
			{
				RenderMeshOnScreen(meshList[GEO_2SAVE], 40, 30, 16, 12);

				if ((cursorY >= 250 && cursorY <= 290) && (cursorX >= 410 && cursorX <= 480)) //Mouse Over Save 2
				{

				}
			}
			if (!loadEmpty[2])
			{
				RenderMeshOnScreen(meshList[GEO_3SAVE], 40, 30, 16, 12);

				if ((cursorY >= 180 && cursorY <= 220) && (cursorX >= 410 && cursorX <= 480)) //Mouse Over Save 3
				{

				}
			}
			if (!loadEmpty[3])
			{
				RenderMeshOnScreen(meshList[GEO_4SAVE], 40, 30, 16, 12);

				if ((cursorY >= 110 && cursorY <= 150) && (cursorX >= 410 && cursorX <= 480)) //Mouse Over Save 4
				{

				}
			}
			if (!loadEmpty[4])
			{
				RenderMeshOnScreen(meshList[GEO_5SAVE], 40, 30, 16, 12);

				if ((cursorY >= 50 && cursorY <= 90) && (cursorX >= 410 && cursorX <= 480)) //Mouse Over Save 5
				{

				}
			}
		}
		else if (load == 2)
		{
			RenderMeshOnScreen(meshList[GEO_SAVE], 40, 30, 16, 12);

			if (loadEmpty[0])
			{
				RenderMeshOnScreen(meshList[GEO_1SAVE], 40, 30, 16, 12);

				if ((cursorY >= 310 && cursorY <= 360) && (cursorX >= 410 && cursorX <= 480)) //Mouse Over Save 1
				{

				}
			}
			if (loadEmpty[1])
			{
				RenderMeshOnScreen(meshList[GEO_2SAVE], 40, 30, 16, 12);

				if ((cursorY >= 250 && cursorY <= 290) && (cursorX >= 410 && cursorX <= 480)) //Mouse Over Save 2
				{

				}
			}
			if (loadEmpty[2])
			{
				RenderMeshOnScreen(meshList[GEO_3SAVE], 40, 30, 16, 12);

				if ((cursorY >= 180 && cursorY <= 220) && (cursorX >= 410 && cursorX <= 480)) //Mouse Over Save 3
				{

				}
			}
			if (loadEmpty[3])
			{
				RenderMeshOnScreen(meshList[GEO_4SAVE], 40, 30, 16, 12);

				if ((cursorY >= 110 && cursorY <= 150) && (cursorX >= 410 && cursorX <= 480)) //Mouse Over Save 4
				{

				}
			}
			if (loadEmpty[4])
			{
				RenderMeshOnScreen(meshList[GEO_5SAVE], 40, 30, 16, 12);

				if ((cursorY >= 50 && cursorY <= 90) && (cursorX >= 410 && cursorX <= 480)) //Mouse Over Save 5
				{

				}
			}
		}
	}
	if (mouseMenu) //Mouse
	{
		RenderMeshOnScreen(meshList[GEO_MOUSEMENU], 40, 30, 16, 12);

		if (mouseSelection == 0)
		{
			RenderMeshOnScreen(meshList[GEO_CURSOR], 40, 25, 8, 10);
			RenderMeshOnScreen(meshList[GEO_CURSOR], cursorX / 10, cursorY / 10, 10, 12);
		}
		if (mouseSelection == 1)
		{
			RenderMeshOnScreen(meshList[GEO_CURSOR1], 40, 25, 8, 10);
			RenderMeshOnScreen(meshList[GEO_CURSOR1], cursorX / 10, cursorY / 10, 10, 12);
		}
		if (mouseSelection == 2)
		{
			RenderMeshOnScreen(meshList[GEO_CURSOR2], 40, 25, 8, 10);
			RenderMeshOnScreen(meshList[GEO_CURSOR2], cursorX / 10, cursorY / 10, 10, 12);
		}
		if (mouseSelection == 3)
		{
			RenderMeshOnScreen(meshList[GEO_CURSOR3], 40, 25, 8, 10);
			RenderMeshOnScreen(meshList[GEO_CURSOR3], cursorX / 10, cursorY / 10, 10, 12);
		}
	}
	else if (!mouseMenu)
	{
		if (Player::getplayer()->getMouse() == 0)
		{
			RenderMeshOnScreen(meshList[GEO_CURSOR], cursorX / 10, cursorY / 10, 8, 10);
		}
		if (Player::getplayer()->getMouse() == 1)
		{
			RenderMeshOnScreen(meshList[GEO_CURSOR1], cursorX / 10, cursorY / 10, 8, 10);
		}
		if (Player::getplayer()->getMouse() == 2)
		{
			RenderMeshOnScreen(meshList[GEO_CURSOR2], cursorX / 10, cursorY / 10, 8, 10);
		}
		if (Player::getplayer()->getMouse() == 3)
		{
			RenderMeshOnScreen(meshList[GEO_CURSOR3], cursorX / 10, cursorY / 10, 8, 10);
		}
	}

	if (Application::IsKeyPressed(VK_NUMPAD0))
	{
		std::ostringstream oss;
		oss << cursorX << " : " << cursorY;
		RenderTextOnScreen(meshList[GEO_CURSORPOS], oss.str(), 2, 2, 8, 10);
		oss.str("");
	}
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