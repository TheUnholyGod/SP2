#include "Menu.h"

POINT cursorPoint;

Menu::Menu()
{
	pause = false;

	menuType = 0;
	pauseSelection = 0;
	optionSelection = 0;
	buildSelection = 0;
	craftSelection = 0;
	inventorySelection = 0;
	
	glfwGetWindowSize(Application::m_window, &windowX, &windowY);
	glfwGetCursorPos(Application::m_window, &cursorX, &cursorY);
	glfwSetCursorPos(Application::m_window, windowX / 2, windowY / 2);

	start = std::clock();
}

Menu::~Menu()
{

}

void Menu::init()
{
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

	meshList[GEO_CURSOR] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_CURSOR]->textureID = LoadTGA("Image//cursorPointer.tga");

	meshList[GEO_PAUSEMENU] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_PAUSEMENU]->textureID = LoadTGA("Image//pauseMenu.tga");

	meshList[GEO_OPTIONS] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_OPTIONS]->textureID = LoadTGA("Image//pauseMenu - Options.tga");

	meshList[GEO_BACKTOGAME] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_BACKTOGAME]->textureID = LoadTGA("Image//pauseMenu - BackToGame.tga");

	meshList[GEO_BACKTOMAIN] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_BACKTOMAIN]->textureID = LoadTGA("Image//pauseMenu - BackToMenu.tga");

	//Options Menu
	meshList[GEO_OPTIONSMENU] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_OPTIONSMENU]->textureID = LoadTGA("Image//optionsMenu 2.tga");

	meshList[GEO_MOUSE] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_MOUSE]->textureID = LoadTGA("Image//optionsMenu - Mouse.tga");

	meshList[GEO_VOLUME] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_VOLUME]->textureID = LoadTGA("Image//optionsMenu - Volume.tga");

	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//optionsMenu - Back.tga");

	//Crafting Menu
	meshList[GEO_CRAFTMENU] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_CRAFTMENU]->textureID = LoadTGA("Image//craftMenu.tga");

	//Building Menu
	meshList[GEO_BUILDMENU] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_BUILDMENU]->textureID = LoadTGA("Image//buildMenu.tga");

	//Inventory Menu
	meshList[GEO_INVENTORYMENU] = MeshBuilder::GenerateQuad("quad", Color(0, 1, 0), 5.f);
	meshList[GEO_INVENTORYMENU]->textureID = LoadTGA("Image//inventoryMenu.tga");
	
	meshList[GEO_ITEMS] = MeshBuilder::GenerateText("ItemNames", 16, 16);
	meshList[GEO_ITEMS]->textureID = LoadTGA("Image//calibri.tga");
	count = 0;
}

void Menu::update()
{
	elapsedTime = (std::clock() - start) / (int)CLOCKS_PER_SEC;

	glfwGetWindowSize(Application::m_window, &windowX, &windowY);
	glfwGetCursorPos(Application::m_window, &cursorX, &cursorY);
	cursorY = -cursorY + windowY;

	if (Application::IsKeyPressed(VK_ESCAPE) && elapsedTime > 0.01)
	{
		if (!pause)//Go to Pause menu
		{
			menuType = 1;
			pause = true;
		}
		else if (pause && menuType == 1)//Reset all variables and exit Pause menu
		{
			SetCursorPos(windowX / 2, windowY / 2);
			menuType = 0;
			pauseSelection = 0;
			optionSelection = 0;
			buildSelection = 0;
			craftSelection = 0;
			pause = false;
		}
		start = std::clock();
	}
	if (Application::IsKeyPressed('V') && elapsedTime > 0.01)
	{
		if (!pause)//Go to Build menu
		{
			menuType = 2;
			pause = true;
		}
		else if (pause && menuType == 2)//Reset all variables and exit Build menu
		{
			SetCursorPos(windowX / 2, windowY / 2);
			menuType = 0;
			pauseSelection = 0;
			optionSelection = 0;
			buildSelection = 0;
			craftSelection = 0;
			pause = false;
		}
		start = std::clock();
	}
	if (Application::IsKeyPressed('C') && elapsedTime > 0.01)
	{
		if (!pause)//Go to Craft menu
		{
			menuType = 3;
			pause = true;
		}
		else if (pause && menuType == 3)//Reset all variables and exit Craft menu
		{
			SetCursorPos(windowX / 2, windowY / 2);
			menuType = 0;
			pauseSelection = 0;
			optionSelection = 0;
			buildSelection = 0;
			craftSelection = 0;
			pause = false;
		}
		start = std::clock();
	}
	if (Application::IsKeyPressed('I') && elapsedTime > 0.01)
	{
		if (!pause)//Go to Inventory menu
		{
			menuType = 4;
			pause = true;
		}
		else if (pause && menuType == 4)//Reset all variables and exit Inventory menu
		{
			SetCursorPos(windowX / 2, windowY / 2);
			menuType = 0;
			pauseSelection = 0;
			optionSelection = 0;
			buildSelection = 0;
			craftSelection = 0;
			pause = false;
		}
		start = std::clock();
	}

	if (menuType == 0) //Options Menu
	{
		if (pause)
		{
			if (elapsedTime > 0.01)
			{
				if (Application::IsKeyPressed(VK_UP))
				{
					if (optionSelection >= 0)
					{
						optionSelection--;
					}
					if (optionSelection < 0)
					{
						optionSelection = 2;
					}
					start = std::clock();
				}
				if (Application::IsKeyPressed(VK_DOWN))
				{
					if (optionSelection < 3)
					{
						optionSelection++;
					}
					if (optionSelection > 2)
					{
						optionSelection = 0;
					}
					start = std::clock();
				}
				if (cursorY >= 340 && cursorY <= 390)
				{
					optionSelection = 0;
				}
				if (cursorY >= 190 && cursorY <= 230)
				{
					optionSelection = 1;
				}
				if (cursorY >= 40 && cursorY <= 80)
				{
					optionSelection = 2;
				}
			}

			if (optionSelection == 0) //Mouse
			{
				if ((Application::IsKeyPressed(VK_LBUTTON) && (cursorY >= 340 && cursorY <= 390)) || (Application::IsKeyPressed(VK_RETURN)))
				{

				}
			}
			if (optionSelection == 1) //Volume
			{
				if ((Application::IsKeyPressed(VK_LBUTTON) && (cursorY >= 190 && cursorY <= 230)) || (Application::IsKeyPressed(VK_RETURN)))
				{

				}
			}
			if (optionSelection == 2) //Back
			{
				if ((Application::IsKeyPressed(VK_LBUTTON) && (cursorY >= 40 && cursorY <= 80)) || (Application::IsKeyPressed(VK_RETURN)))
				{
					optionSelection = 0;
					menuType = 1;
				}
			}
		}
	}
	if (menuType == 1) //Pause Menu
	{
		if (pause)
		{
			if (elapsedTime > 0.01)
			{
				if (Application::IsKeyPressed(VK_UP))
				{
					if (pauseSelection >= 0)
					{
						pauseSelection--;
					}
					if (pauseSelection < 0)
					{
						pauseSelection = 2;
					}
					start = std::clock();
				}
				if (Application::IsKeyPressed(VK_DOWN))
				{
					if (pauseSelection < 3)
					{
						pauseSelection++;
					}
					if (pauseSelection > 2)
					{
						pauseSelection = 0;
					}
					start = std::clock();
				}
			}
			if (cursorY >= 285 && cursorY <= 325)
			{
				pauseSelection = 0;
			}
			if (cursorY >= 180 && cursorY <= 225)
			{
				pauseSelection = 1;
			}
			if (cursorY >= 75 && cursorY <= 120)
			{
				pauseSelection = 2;
			}

			if (pauseSelection == 0) //Back to Options Screen
			{
				if ((Application::IsKeyPressed(VK_LBUTTON) && (cursorY >= 285 && cursorY <= 325)) || (Application::IsKeyPressed(VK_RETURN)))
				{
					menuType = 0;
				}
			}
			if (pauseSelection == 1) //Back to Game
			{
				if ((Application::IsKeyPressed(VK_LBUTTON) && (cursorY >= 180 && cursorY <= 225)) || (Application::IsKeyPressed(VK_RETURN)))
				{
					SetCursorPos(windowX / 2, windowY / 2);
					menuType = 1;
					pauseSelection = 0;
					optionSelection = 0;
					pause = false;
				}
			}
			if (pauseSelection == 2) //Back to Main Menu
			{
				if ((Application::IsKeyPressed(VK_LBUTTON) && (cursorY >= 75 && cursorY <= 120)) || (Application::IsKeyPressed(VK_RETURN)))
				{
					SceneManager::currScene = 2;
					pause = false;
				}
			}
		}
	}
	if (menuType == 2) //Build Menu
	{
		if (pause)
		{
			if (elapsedTime > 0.01)
			{

			}
		}
	}
	if (menuType == 3) //Craft Menu
	{
		if (pause)
		{
			if (elapsedTime > 0.01)
			{

			}
		}
	}
	if (menuType == 4) //Inventory Menu
	{
		if (pause)
		{
			if (elapsedTime > 0.01)
			{
				count = Inventory::getinventory()->getsize();
			}
		}
	}
}

void Menu::Render()
{
	if (pause)
	{
		if (menuType == 0)
		{
			RenderMeshOnScreen(meshList[GEO_OPTIONSMENU], 40, 30, 16, 12);

			if (optionSelection == 0)
			{
				RenderMeshOnScreen(meshList[GEO_MOUSE], 40, 30, 16, 12);
			}
			if (optionSelection == 1)
			{
				RenderMeshOnScreen(meshList[GEO_VOLUME], 40, 30, 16, 12);
			}
			if (optionSelection == 2)
			{
				RenderMeshOnScreen(meshList[GEO_BACK], 40, 30, 16, 12);
			}
		}
		if (menuType == 1)
		{
			RenderMeshOnScreen(meshList[GEO_PAUSEMENU], 40, 30, 16, 12);

			if (pauseSelection == 0)
			{
				RenderMeshOnScreen(meshList[GEO_OPTIONS], 40, 30, 16, 12);
			}
			if (pauseSelection == 1)
			{
				RenderMeshOnScreen(meshList[GEO_BACKTOGAME], 40, 30, 16, 12);
			}
			if (pauseSelection == 2)
			{
				RenderMeshOnScreen(meshList[GEO_BACKTOMAIN], 40, 30, 16, 12);
			}
		}
		if (menuType == 2)
		{
			RenderMeshOnScreen(meshList[GEO_BUILDMENU], 40, 30, 16, 12);
		}
		if (menuType == 3)
		{
			RenderMeshOnScreen(meshList[GEO_CRAFTMENU], 40, 30, 16, 12);
		}
		if (menuType == 4)
		{
			RenderMeshOnScreen(meshList[GEO_INVENTORYMENU], 40, 30, 16, 12);

			float y = 15.f;
			for (std::list<std::string>::iterator i = Inventory::getinventory()->name.begin(); i != Inventory::getinventory()->name.end(); i++)
			{
				RenderTextOnScreen(meshList[GEO_ITEMS], *i, Color(0, 0, 1), 3.f, 5.f, y);
				y-=2;
			}
		}
		RenderMeshOnScreen(meshList[GEO_CURSOR], cursorX / 10, cursorY / 10, 8, 10);		
	}

		
}

void Menu::RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey)
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

void Menu::RenderMesh(Mesh *mesh, bool enableLight)
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

void Menu::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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