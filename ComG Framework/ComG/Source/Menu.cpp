#include "Menu.h"
#include "SceneSplashScreen.h"
#include "SaveLoad.h"

POINT cursorPoint;

bool Menu::tpZone = false;
int Menu::menuType = 0;

Menu::Menu() : buildingID(101), itemID(105)
{
	pause = false;
	rendered = false;
	isMenu = false;

	craft = 0;
	pauseSelection = 0;
	optionSelection = 0;
	buildSelection = 0;
	craftSelection = 0;
	inventorySelection = 0;
	craftingSelection = 0;
	
	glfwGetWindowSize(Application::m_window, &windowX, &windowY);
	glfwGetCursorPos(Application::m_window, &cursorX, &cursorY);
	glfwSetCursorPos(Application::m_window, windowX / 2, windowY / 2);

	start = std::clock();

	Inventory::getinventory();
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

	//Inventory Menu
	meshList[GEO_INVENTORYMENU] = MeshBuilder::GenerateQuad("Inventory", Color(0, 1, 0), 5.f);
	meshList[GEO_INVENTORYMENU]->textureID = LoadTGA("Image//inventoryMenu.tga");

	meshList[GEO_ITEMS] = MeshBuilder::GenerateText("ItemNames", 16, 16);
	meshList[GEO_ITEMS]->textureID = LoadTGA("Image//calibri.tga");
	
	meshList[GEO_QUANTITY] = MeshBuilder::GenerateText("Quantity", 16, 16);
	meshList[GEO_QUANTITY]->textureID = LoadTGA("Image//calibri.tga");
	
	meshList[GEO_IMAGE] = MeshBuilder::GenerateQuad("Image", Color(0, 1, 0), 2.f);
	meshList[GEO_IMAGE]->textureID = LoadTGA("Image//Resource_Adhesive.tga");

	meshList[GEO_POTATO] = MeshBuilder::GenerateQuad("potato", Color(0, 1, 0), 2.f);
	meshList[GEO_POTATO]->textureID = LoadTGA("Image//Food_Potato.tga");
	meshList[GEO_CARROT] = MeshBuilder::GenerateQuad("carrot", Color(0, 1, 0), 2.f);
	meshList[GEO_CARROT]->textureID = LoadTGA("Image//Food_Carrot.tga");
	meshList[GEO_CABBAGE] = MeshBuilder::GenerateQuad("cabbage", Color(0, 1, 0), 2.f);
	meshList[GEO_CABBAGE]->textureID = LoadTGA("Image//Food_Cabbage.tga");
	meshList[GEO_WHEAT] = MeshBuilder::GenerateQuad("wheat", Color(0, 1, 0), 2.f);
	meshList[GEO_WHEAT]->textureID = LoadTGA("Image//Food_Wheat.tga");
	meshList[GEO_STONE] = MeshBuilder::GenerateQuad("stone", Color(0, 1, 0), 2.f);
	meshList[GEO_STONE]->textureID = LoadTGA("Image//Resource_Stone.tga");
	meshList[GEO_IRON] = MeshBuilder::GenerateQuad("Iron", Color(0, 1, 0), 2.f);
	meshList[GEO_IRON]->textureID = LoadTGA("Image//Resource_Iron.tga");
	meshList[GEO_COPPER] = MeshBuilder::GenerateQuad("copper", Color(0, 1, 0), 2.f);
	meshList[GEO_COPPER]->textureID = LoadTGA("Image//Resource_Copper.tga");
	meshList[GEO_GOLD] = MeshBuilder::GenerateQuad("gold", Color(0, 1, 0), 2.f);
	meshList[GEO_GOLD]->textureID = LoadTGA("Image//Resource_Gold.tga");
	meshList[GEO_WATER] = MeshBuilder::GenerateQuad("water", Color(0, 1, 0), 2.f);
	meshList[GEO_WATER]->textureID = LoadTGA("Image//Resource_Water.tga");
	meshList[GEO_WOOD] = MeshBuilder::GenerateQuad("wood", Color(0, 1, 0), 2.f);
	meshList[GEO_WOOD]->textureID = LoadTGA("Image//Resource_Wood.tga");
	meshList[GEO_BIOMASS] = MeshBuilder::GenerateQuad("biomass", Color(0, 1, 0), 2.f);
	meshList[GEO_BIOMASS]->textureID = LoadTGA("Image//Resource_Biomass.tga");
	meshList[GEO_ADHESIVES] = MeshBuilder::GenerateQuad("adhesives", Color(0, 1, 0), 2.f);
	meshList[GEO_ADHESIVES]->textureID = LoadTGA("Image//Resource_Adhesive.tga");
	meshList[GEO_METALSCRAPS] = MeshBuilder::GenerateQuad("metalscrap", Color(0, 1, 0), 2.f);
	meshList[GEO_METALSCRAPS]->textureID = LoadTGA("Image//Resource_MetalScrap.tga");
	meshList[GEO_CLOTH] = MeshBuilder::GenerateQuad("cloth", Color(0, 1, 0), 2.f);
	meshList[GEO_CLOTH]->textureID = LoadTGA("Image//Resource_Cloth.tga");
	meshList[GEO_CIRCUITBOARDS] = MeshBuilder::GenerateQuad("circuitboard", Color(0, 1, 0), 2.f);
	meshList[GEO_CIRCUITBOARDS]->textureID = LoadTGA("Image//Resource_CircuitBoards.tga");

	meshList[ITEM_BREAD] = MeshBuilder::GenerateQuad("bread", Color(0, 1, 0), 2.f);
	meshList[ITEM_BREAD]->textureID = LoadTGA("Image//Food_Bread.tga");
	meshList[ITEM_VEGETABLESTEW] = MeshBuilder::GenerateQuad("vegetablestew", Color(0, 1, 0), 2.f);
	meshList[ITEM_VEGETABLESTEW]->textureID = LoadTGA("Image//Food_VegetableStew.tga");
	meshList[ITEM_DRINKINGWATER] = MeshBuilder::GenerateQuad("drinkingwater", Color(0, 1, 0), 2.f);
	meshList[ITEM_DRINKINGWATER]->textureID = LoadTGA("Image//Food_PurifiedWater.tga");
	meshList[ITEM_CARROTJUICE] = MeshBuilder::GenerateQuad("carrotjuice", Color(0, 1, 0), 2.f);
	meshList[ITEM_CARROTJUICE]->textureID = LoadTGA("Image//Food_CarrotJuice.tga");
	meshList[ITEM_SALAD] = MeshBuilder::GenerateQuad("salad", Color(0, 1, 0), 2.f);
	meshList[ITEM_SALAD]->textureID = LoadTGA("Image//Food_Salad.tga");
	meshList[ITEM_GLOCK] = MeshBuilder::GenerateQuad("glock", Color(0, 1, 0), 2.f);
	meshList[ITEM_GLOCK]->textureID = LoadTGA("Image//Glock.tga");
	meshList[ITEM_SCAR_H] = MeshBuilder::GenerateQuad("scar", Color(0, 1, 0), 2.f);
	meshList[ITEM_SCAR_H]->textureID = LoadTGA("Image//Scar.tga");
	meshList[ITEM_M200] = MeshBuilder::GenerateQuad("m200", Color(0, 1, 0), 2.f);
	meshList[ITEM_M200]->textureID = LoadTGA("Image//CheyTac.tga");
	meshList[ITEM_BOW] = MeshBuilder::GenerateQuad("bow", Color(0, 1, 0), 2.f);
	meshList[ITEM_BOW]->textureID = LoadTGA("Image//CompoundBow.tga");
	meshList[ITEM_FARMINGHOE] = MeshBuilder::GenerateQuad("farminghoe", Color(0, 1, 0), 2.f);
	meshList[ITEM_FARMINGHOE]->textureID = LoadTGA("Image//FarmingHoe.tga");
	meshList[ITEM_KATANA] = MeshBuilder::GenerateQuad("katana", Color(0, 1, 0), 2.f);
	meshList[ITEM_KATANA]->textureID = LoadTGA("Image//Katana.tga");
	meshList[ITEM_KNIFE] = MeshBuilder::GenerateQuad("knife", Color(0, 1, 0), 2.f);
	meshList[ITEM_KNIFE]->textureID = LoadTGA("Image//KitchenKnife.tga");

	menuType = 0;
	y1 = 45.f;
	count = 0;
	travelTo = SceneManager::currScene;

	//Text
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_ARROW_L] = MeshBuilder::GenerateQuad("arrowL", Color(0, 1, 0), 5.f);
	meshList[GEO_ARROW_L]->textureID = LoadTGA("Image//buildMenu - Arrows - L.tga");

	meshList[GEO_ARROW_R] = MeshBuilder::GenerateQuad("arrowR", Color(0, 1, 0), 5.f);
	meshList[GEO_ARROW_R]->textureID = LoadTGA("Image//buildMenu - Arrows - R.tga");

	meshList[GEO_CURSOR] = MeshBuilder::GenerateQuad("cursor", Color(0, 1, 0), 5.f);
	meshList[GEO_CURSOR]->textureID = LoadTGA("Image//cursorPointer.tga");

	meshList[GEO_PAUSEMENU] = MeshBuilder::GenerateQuad("pause", Color(0, 1, 0), 5.f);
	meshList[GEO_PAUSEMENU]->textureID = LoadTGA("Image//pauseMenu.tga");

	meshList[GEO_OPTIONS] = MeshBuilder::GenerateQuad("option", Color(0, 1, 0), 5.f);
	meshList[GEO_OPTIONS]->textureID = LoadTGA("Image//pauseMenu - Options.tga");

	meshList[GEO_BACKTOGAME] = MeshBuilder::GenerateQuad("backG", Color(0, 1, 0), 5.f);
	meshList[GEO_BACKTOGAME]->textureID = LoadTGA("Image//pauseMenu - BackToGame.tga");

	meshList[GEO_BACKTOMAIN] = MeshBuilder::GenerateQuad("backM", Color(0, 1, 0), 5.f);
	meshList[GEO_BACKTOMAIN]->textureID = LoadTGA("Image//pauseMenu - BackToMenu.tga");

	//Options Menu
	meshList[GEO_OPTIONSMENU] = MeshBuilder::GenerateQuad("optionmenu", Color(0, 1, 0), 5.f);
	meshList[GEO_OPTIONSMENU]->textureID = LoadTGA("Image//optionsMenu 2.tga");

	meshList[GEO_MOUSE] = MeshBuilder::GenerateQuad("mouse", Color(0, 1, 0), 5.f);
	meshList[GEO_MOUSE]->textureID = LoadTGA("Image//optionsMenu - Mouse.tga");

	meshList[GEO_VOLUME] = MeshBuilder::GenerateQuad("volume", Color(0, 1, 0), 5.f);
	meshList[GEO_VOLUME]->textureID = LoadTGA("Image//optionsMenu - Volume.tga");

	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(0, 1, 0), 5.f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//optionsMenu - Back.tga");

	//Crafting Menu
	meshList[GEO_CRAFTMENU] = MeshBuilder::GenerateQuad("craftmenu", Color(0, 1, 0), 5.f);
	meshList[GEO_CRAFTMENU]->textureID = LoadTGA("Image//craftMenu.tga");

	//Building Menu
	meshList[GEO_BUILDMENU] = MeshBuilder::GenerateQuad("buildmenu", Color(0, 1, 0), 5.f);
	meshList[GEO_BUILDMENU]->textureID = LoadTGA("Image//buildMenu.tga");

	meshList[GEO_CRAFTBUTTON] = MeshBuilder::GenerateQuad("craftmenu", Color(0, 1, 0), 5.f);
	meshList[GEO_CRAFTBUTTON]->textureID = LoadTGA("Image//buildcraftMenu - Craft.tga");

	meshList[GEO_FASTTRAVEL] = MeshBuilder::GenerateQuad("Fasttravel", Color(0, 1, 0), 5.f);
	meshList[GEO_FASTTRAVEL]->textureID = LoadTGA("Image//FAstTravel.tga");

	for (int i = 0; i<buildingMeshList.size(); i++)
	{
		buildingName.push_back(BuildingDataBase::getBuildingDB()->getBuilding(buildingID + i)->getName());
	}
	for (int i = 0; i<itemMeshList.size(); i++)
	{
		if ((itemID + i) > 109)
		{
			itemID = 301;
			break;
		}
		else if ((itemID + i) <= 109)
		{
			foodName.push_back(ItemDataBase::getItemDB()->getItem(itemID + i)->getName());
		}
	}
	for (int i = 0; i<itemMeshList.size(); i++)
	{
		if ((itemID + i) > 307)
		{
			itemID = 105;
			break;
		}
		else if ((itemID + i) <= 307)
		{
			weaponName.push_back(ItemDataBase::getItemDB()->getItem(itemID + i)->getName());
		}	
	}
	itemID = 105;

	width = (windowX / 50);
	height = (windowY / 18.5);
}

void Menu::update()
{
	elapsedTime = (std::clock() - start) / (int)CLOCKS_PER_SEC;

	glfwGetWindowSize(Application::m_window, &windowX, &windowY);
	glfwGetCursorPos(Application::m_window, &cursorX, &cursorY);
	cursorY = -cursorY + windowY;

	int HP = Player::getplayer()->gethealth();
	
	craft = 0;

	if (HP <= 0)
	{
		Player::getplayer()->isDead();
		SceneManager::currScene = 8;
	}

	if (isMenu)
	{
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
	}
	if (Application::IsKeyPressed(VK_ESCAPE) && elapsedTime > 0.01)
	{
		if (!pause)//Go to Pause menu
		{
			menuType = 1;
			pause = true;
			isMenu = true;
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
			isMenu = false;
		}
		start = std::clock();
	}
	if (Application::IsKeyPressed('V') && elapsedTime > 0.01)
	{
		if (!pause)//Go to Build menu
		{
			menuType = 2;
			pause = true;
			isMenu = true;
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
			isMenu = false;
		}
		start = std::clock();
	}
	if (Application::IsKeyPressed('C') && elapsedTime > 0.01)
	{
		if (!pause)//Go to Craft menu
		{
			menuType = 3;
			pause = true;
			isMenu = true;
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
			isMenu = false;
		}
		start = std::clock();
	}
	if (Application::IsKeyPressed('I') && elapsedTime > 0.01)
	{
		if (!pause)//Go to Inventory menu
		{
			menuType = 4;
			pause = true;
			isMenu = true;
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
			isMenu = false;
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

				if ((Application::IsKeyPressed(VK_RETURN)) || (Application::IsKeyPressed(VK_LBUTTON)))
				{
					if (optionSelection == 0)
					{

					}
					if (optionSelection == 1)
					{

					}
					if (optionSelection == 2)
					{
						optionSelection = 0;
						menuType = 1;
					}

					start = std::clock();
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
					isMenu = false;
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
				if (Application::IsKeyPressed(VK_LEFT))
				{
					if (buildSelection >= 0)
					{
						buildSelection--;
					}
					if (buildSelection < 0)
					{
						buildSelection = 11;
					}
					start = std::clock();
				}
				if (Application::IsKeyPressed(VK_RIGHT))
				{
					if (buildSelection < 12)
					{
						buildSelection++;
					}
					if (buildSelection > 11)
					{
						buildSelection = 0;
					}
					start = std::clock();
				}
				if (Application::IsKeyPressed(VK_LBUTTON))
				{
					if ((cursorX >= 110 && cursorX <= 150) && (cursorY >= 400 && cursorY <= 450))
					{
						if (buildSelection >= 0)
						{
							buildSelection--;
						}
						if (buildSelection < 0)
						{
							buildSelection = 11;
						}
						start = std::clock();
					}
					if ((cursorX >= 650 && cursorX <= 690) && (cursorY >= 400 && cursorY <= 450))
					{
						if (buildSelection < 12)
						{
							buildSelection++;
						}
						if (buildSelection > 11)
						{
							buildSelection = 0;
						}
						start = std::clock();
					}
					if ((cursorX >= 440 && cursorX <= 735) && (cursorY >= 10 && cursorY <= 60))
					{
						craft = 1;
						craftSelection = buildingID + buildSelection;
						bRecipe = BuildingDataBase::getBuildingDB()->getBuilding(craftSelection)->getRecipe();
						check = false;
						check = checkbuild();
						if(check)
							Removal();
						SetCursorPos(windowX / 2, windowY / 2);
						isMenu = false;
						pause = false;
					}
				}
			}
		}
	}
	if (menuType == 3) //Craft Menu
	{
		if (pause)
		{
			if (elapsedTime > 0.01)
			{
				if (Application::IsKeyPressed(VK_LEFT))
				{
					if (craftingSelection >= 0)
					{
						craftingSelection--;
					}
					if (craftingSelection < 0)
					{
						craftingSelection = 11;
					}
					start = std::clock();
				}
				if (Application::IsKeyPressed(VK_RIGHT))
				{
					if (craftingSelection < 12)
					{
						craftingSelection++;
					}
					if (craftingSelection > 11)
					{
						craftingSelection = 0;
					}
					start = std::clock();
				}
				if (Application::IsKeyPressed(VK_LBUTTON))
				{
					if ((cursorX >= 110 && cursorX <= 150) && (cursorY >= 400 && cursorY <= 450))
					{
						if (craftingSelection >= 0)
						{
							craftingSelection--;
						}
						if (craftingSelection < 0)
						{
							craftingSelection = 11;
						}
						start = std::clock();
					}
					if ((cursorX >= 650 && cursorX <= 690) && (cursorY >= 400 && cursorY <= 450))
					{
						if (craftingSelection < 12)
						{
							craftingSelection++;
						}
						if (craftingSelection > 11)
						{
							craftingSelection = 0;
						}
						start = std::clock();
					}
					if ((cursorX >= 440 && cursorX <= 735) && (cursorY >= 10 && cursorY <= 60))//
					{
						craft = 2;
						craftSelection = itemID + craftingSelection;
						iRecipe = ItemFactory::getItemFactory()->generateItem(craftSelection)->getRecipe();
						check1 = false;
						check1 = checkcraft();
						if (check1)
							crafting();
						SetCursorPos(windowX / 2, windowY / 2);
						isMenu = false;
						pause = false;
					}
				}
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
	if (menuType == 5)
	{
		if (elapsedTime > 0.01)
		{
			if (Application::IsKeyPressed(VK_RIGHT))
			{
				if (travelTo < 7)
				{
					travelTo += 1;
				}
				else
				{
					travelTo = 4;
				}
				start = std::clock();
			}
			else if (Application::IsKeyPressed(VK_LEFT))
			{
				if (travelTo > 4)
				{
					travelTo -= 1;
				}
				else
				{
					travelTo = 7;
				}
				start = std::clock();
			}
			if (tpZone)
			{
				if (Application::IsKeyPressed(VK_RETURN))
				{
					SetCursorPos(windowX / 2, windowY / 2);
					menuType = 0;
					isMenu = false;
					pause = false;
					SceneManager::currScene = travelTo;
				}
			}

			std::cout << "Travelling to: " << travelTo << std::endl;
		}
	}
}

void Menu::Render()
{
	if (pause)
	{
		if (menuType == 0) //Options
		{
			RenderMeshOnScreen(meshList[GEO_OPTIONSMENU], 40, 30, 16, 12);

			if (optionSelection == 0)
			{
				RenderMeshOnScreen(meshList[GEO_MOUSE], 40, 30, 16, 12);
			}
			else if (optionSelection == 1)
			{
				RenderMeshOnScreen(meshList[GEO_VOLUME], 40, 30, 16, 12);
			}
			else if(optionSelection == 2)
			{
				RenderMeshOnScreen(meshList[GEO_BACK], 40, 30, 16, 12);
			}
		}
		if (menuType == 1) //Pause
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
		if (menuType == 2) //Building
		{
			RenderMeshOnScreen(meshList[GEO_BUILDMENU], 40, 30, 16, 12);

			for (int i = 0; i < buildingName.size(); i++)
			{
				if (i == buildSelection)
				{
					width = 16;
					height = 40;

					RenderTextOnScreen(meshList[GEO_TEXT], buildingName[i], Color(1, 0, 0), 3.0f, width + 2.5, height + 5);
					bRecipe = BuildingDataBase::getBuildingDB()->getBuilding(buildingID + i)->getRecipe();
					height = 30;

					for (bit = bRecipe.begin(); bit != bRecipe.end(); bit++)
					{
						resourceName.push_back(bit->first->getName());
						resourceQuantity.push_back(bit->second);
					}	
					for (int i = 0; i <= resourceName.size(); i++)
					{
						std::ostringstream oss;

						if (i != resourceName.size())
						{
							oss << resourceQuantity[i];
							RenderTextOnScreen(meshList[GEO_TEXT], resourceName[i], Color(1, 0, 0), 2.5f, width / 2, height);
							RenderTextOnScreen(meshList[GEO_TEXT], oss.str(), Color(0, 1, 0), 2.5f, width * 2.5, height);

							height -= 2.5;
						}

						oss.str("");
					}
				}

				resourceName.clear();
				resourceQuantity.clear();
			}

			if ((cursorX >= 110 && cursorX <= 150) && (cursorY >= 400 && cursorY <= 450))
			{
				RenderMeshOnScreen(meshList[GEO_ARROW_L], 40, 30, 16, 12);
			}
			if ((cursorX >= 650 && cursorX <= 690) && (cursorY >= 400 && cursorY <= 450))
			{
				RenderMeshOnScreen(meshList[GEO_ARROW_R], 40, 30, 16, 12);
			}
			if ((cursorX >= 440 && cursorX <= 735) && (cursorY >= 10 && cursorY <= 60))
			{
				RenderMeshOnScreen(meshList[GEO_CRAFTBUTTON], 40, 30, 16, 12);
			}
		}
		if (menuType == 3) //Crafting
		{
			RenderMeshOnScreen(meshList[GEO_CRAFTMENU], 40, 30, 16, 12);

			if (craftingSelection < 5)
			{
				itemID = 105;

				for (int i = 0; i < itemMeshList.size(); i++)
				{
					if (i == craftingSelection)
					{
						width = 16;
						height = 40;

						RenderTextOnScreen(meshList[GEO_TEXT], foodName[i], Color(1, 0, 0), 3.0f, width + 2.5, height + 5);
						iRecipe = ItemFactory::getItemFactory()->generateItem(itemID + i)->getRecipe();
						height = 30;

						for (iit = iRecipe.begin(); iit != iRecipe.end(); iit++)
						{
							std::string tempName = ItemFactory::getItemFactory()->generateItem(iit->first)->getName();
							resourceName.push_back(tempName);
							resourceQuantity.push_back(iit->second);
						}
						for (int i = 0; i <= resourceName.size(); i++)
						{
							std::ostringstream oss;

							if (i != resourceName.size())
							{
								oss << resourceQuantity[i];
								RenderTextOnScreen(meshList[GEO_TEXT], resourceName[i], Color(1, 0, 0), 2.5f, width / 2, height);
								RenderTextOnScreen(meshList[GEO_TEXT], oss.str(), Color(0, 1, 0), 2.5f, width * 2.5, height);

								height -= 2.5;
							}
							oss.str("");
						}
					}

					resourceName.clear();
					resourceQuantity.clear();
				}
			}
			if (craftingSelection > 4)
			{
				itemID = 301;
				int offset = craftingSelection - 5;

				for (int i = 0; i < itemMeshList.size(); i++)
				{
					if (i == offset)
					{
						width = 16;
						height = 40;

						RenderTextOnScreen(meshList[GEO_TEXT], weaponName[i], Color(1, 0, 0), 3.0f, width + 2.5, height + 5);
						iRecipe = ItemFactory::getItemFactory()->generateItem(itemID + i)->getRecipe();
						height = 30;

						for (iit = iRecipe.begin(); iit != iRecipe.end(); iit++)
						{
							std::string tempName = ItemFactory::getItemFactory()->generateItem(iit->first)->getName();
							resourceName.push_back(tempName);
							resourceQuantity.push_back(iit->second);
						}
						for (int i = 0; i <= resourceName.size(); i++)
						{
							std::ostringstream oss;

							if (i != resourceName.size())
							{
								oss << resourceQuantity[i];
								RenderTextOnScreen(meshList[GEO_TEXT], resourceName[i], Color(1, 0, 0), 2.5f, width / 2, height);
								RenderTextOnScreen(meshList[GEO_TEXT], oss.str(), Color(0, 1, 0), 2.5f, width * 2.5, height);

								height -= 2.5;
							}
							oss.str("");
						}
					}

					resourceName.clear();
					resourceQuantity.clear();
				}
			}

			if ((cursorX >= 110 && cursorX <= 150) && (cursorY >= 400 && cursorY <= 450))
			{
				RenderMeshOnScreen(meshList[GEO_ARROW_L], 40, 30, 16, 12);
			}
			if ((cursorX >= 650 && cursorX <= 690) && (cursorY >= 400 && cursorY <= 450))
			{
				RenderMeshOnScreen(meshList[GEO_ARROW_R], 40, 30, 16, 12);
			}
			if ((cursorX >= 440 && cursorX <= 735) && (cursorY >= 10 && cursorY <= 60))
			{
				RenderMeshOnScreen(meshList[GEO_CRAFTBUTTON], 40, 30, 16, 12);
			}
		}
		if (menuType == 4) //Inventory
		{
			RenderMeshOnScreen(meshList[GEO_INVENTORYMENU], 40, 30, 16, 12);
			float y = 45.f;
			y1 = 45.f;
			float y2 = 45.f;

			for (auto &i : Inventory::getinventory()->getInventoryContents())
			{
				std::string quantity = std::to_string(i.second);
				int key = i.first;
				checkItem(key);
				Item* temp = new Item(*ItemFactory::getItemFactory()->generateItem(key));
				std::string name = temp->getName();
				RenderTextOnScreen(meshList[GEO_ITEMS], name, Color(0, 0, 1), 3.f, 15.f, y1);
				RenderTextOnScreen(meshList[GEO_QUANTITY], quantity, Color(0, 0, 1), 3.f, 60.f, y1);
				y1 -= 5.f;
			}
		}
		RenderMeshOnScreen(meshList[GEO_CURSOR], cursorX / 10, cursorY / 10, 8, 10);		
	}
	if (menuType==5 && tpZone)
	{
		RenderMeshOnScreen(meshList[GEO_FASTTRAVEL], 40, 30, 10, 10);
		switch (travelTo){
		case 4:
			RenderTextOnScreen(meshList[GEO_TEXT], "Sandbox", Color(0, 1, 0), 3.f, 28.f, 27.f);
			break;
		case 5:
			RenderTextOnScreen(meshList[GEO_TEXT], "Barn", Color(0, 1, 0), 3.f, 28.f, 27.f);
			break;
		case 6:
			RenderTextOnScreen(meshList[GEO_TEXT], "Wild Life", Color(0, 1, 0), 3.f, 28.f, 27.f);
			break;
		case 7:
			RenderTextOnScreen(meshList[GEO_TEXT], "City", Color(0, 1, 0), 3.f, 28.f, 27.f);
			break;

		}
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
	modelStack.Translate(x, y, 0);
	modelStack.Scale(size, size, size);

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

void Menu::checkItem(int key)
{
	std::vector<int> tempID(ItemDataBase::getItemDB()->getIDList());

	if (key == tempID[0])
		RenderMeshOnScreen(meshList[GEO_POTATO], 8.f, y1, 3.f, 3.f);
	else if (key == tempID[1])
		RenderMeshOnScreen(meshList[GEO_CABBAGE], 8.f, y1, 3.f, 3.f);
	else if (key == tempID[2])
		RenderMeshOnScreen(meshList[GEO_CARROT], 8.f, y1, 3.f, 3.f);
	else if (key == tempID[3])
		RenderMeshOnScreen(meshList[GEO_WHEAT], 8.f, y1, 3.f, 3.f);
	else if (key == tempID[4])
		RenderMeshOnScreen(meshList[ITEM_BREAD], 8.f, y1, 3.f, 3.f);
	else if (key == tempID[5])
		RenderMeshOnScreen(meshList[ITEM_VEGETABLESTEW], 8.f, y1, 3.f, 3.f);
	else if (key == tempID[6])
		RenderMeshOnScreen(meshList[ITEM_DRINKINGWATER], 8.f, y1, 3.f, 3.f);
	else if (key == tempID[7])
		RenderMeshOnScreen(meshList[ITEM_CARROTJUICE], 8.f, y1, 3.f, 3.f);
	else if (key == tempID[8])
		RenderMeshOnScreen(meshList[ITEM_SALAD], 8.f, y1, 3.f, 3.f);
	else if (key == tempID[9])
		RenderMeshOnScreen(meshList[GEO_STONE], 8.f, y1, 3.f, 3.f);
	else if (key == tempID[10])
		RenderMeshOnScreen(meshList[GEO_IRON], 8.f, y1, 3.f, 3.f);
	else if (key == tempID[11])
		RenderMeshOnScreen(meshList[GEO_COPPER], 8.f, y1, 3.f, 3.f);
	else if (key == tempID[12])
		RenderMeshOnScreen(meshList[GEO_GOLD], 8.f, y1, 3.f, 3.f);
	else if (key == tempID[13])
		RenderMeshOnScreen(meshList[GEO_WATER], 8.f, y1, 3.f, 3.f);
	else if (key == tempID[14])
		RenderMeshOnScreen(meshList[GEO_BIOMASS], 8.f, y1, 3.f, 3.f);
	else if (key == tempID[15])
		RenderMeshOnScreen(meshList[GEO_ADHESIVES], 8.f, y1, 3.f, 3.f);
	else if (key == tempID[16])
		RenderMeshOnScreen(meshList[GEO_METALSCRAPS], 8.f, y1, 3.f, 3.f);
	else if (key == tempID[17])
		RenderMeshOnScreen(meshList[GEO_CLOTH], 8.f, y1, 3.f, 3.f);
	else if (key == tempID[18])
		RenderMeshOnScreen(meshList[GEO_CIRCUITBOARDS], 8.f, y1, 3.f, 3.f);

	tempID.erase(tempID.begin(), tempID.end());
}

//====================================================check Inventory=====================================================================
bool Menu::checkbuild()
{
	bool checking = false;
	for (bit = bRecipe.begin(); bit != bRecipe.end(); bit++)
	{
		int i = bit->first->getID();
		int i_no = bit->second;

		std::map <int, int> checkInv;
		for (auto &c : Inventory::getinventory()->getInventoryContents())
		{
			checkInv = Inventory::getinventory()->getInventoryContents();
		}
		std::map <int, int> ::iterator checkmapping = checkInv.find(i);

		for (std::map<int, int>::iterator c = checkInv.begin(); c != checkInv.end(); c++)
		{
			if (checkmapping != checkInv.end());
			{
				int checkno = c->second;
				if (checkno >= i_no)
				{
					checking = true;
				}
				else
				{
					checking = false;
				}
			}
			
			if(checkmapping == checkInv.end())
			{
				return false;
			}
		}
		if (checking == false)
		{
			return false;
		}
	}
	if (checking == true)
	{
		return true;
	}
	else
		return false;
}

void Menu::Removal()
{
	for (bit = bRecipe.begin(); bit != bRecipe.end(); bit++)
	{
		int i = bit->first->getID();
		int rid = bit->first->getID();
		int r_no = bit->second;

		std::map <int, int> checkInv1;
		for (auto &c : Inventory::getinventory()->getInventoryContents())
		{
			checkInv1 = Inventory::getinventory()->getInventoryContents();
		}

		std::map <int, int> ::iterator checkmapping1 = checkInv1.find(rid);
			if (checkmapping1 == checkInv1.end())
			{
				continue;
			}
			else
				Inventory::getinventory()->Removeitem(rid, r_no);
	}
}

bool Menu::checkcraft()
{
	bool checking = false;
	for (iit = iRecipe.begin(); iit != iRecipe.end(); iit++)
	{
		int i = iit->first;
		int i_no = iit->second;

		std::map <int, int> checkInv;
		for (auto &c : Inventory::getinventory()->getInventoryContents())
		{
			checkInv = Inventory::getinventory()->getInventoryContents();
		}
		std::map <int, int> ::iterator checkmapping = checkInv.find(i);

		for (std::map<int, int>::iterator c = checkInv.begin(); c != checkInv.end(); c++)
		{
			if (checkmapping != checkInv.end());
			{
				int checkno = c->second;
				if (checkno >= i_no)
				{
					checking = true;
				}
				else
				{
					checking = false;
				}
			}

			if (checkmapping == checkInv.end())
			{
				return false;
			}
		}
		if (checking == false)
		{
			return false;
		}
	}
	if (checking == true)
	{
		return true;
	}
	else
		return false;
}

int Menu::crafting()
{
	for (iit = iRecipe.begin(); iit != iRecipe.end(); iit++)
	{
		int rid = iit->first;
		int r_no = iit->second;

		std::map <int, int> checkInv1;
		for (auto &c : Inventory::getinventory()->getInventoryContents())
		{
			checkInv1 = Inventory::getinventory()->getInventoryContents();
		}
		std::map <int, int> ::iterator checkmapping1 = checkInv1.find(rid);
		if (checkmapping1 == checkInv1.end())
		{
			continue;
		}
		else
			Inventory::getinventory()->Removeitem(rid, r_no);
	}
	return 0;
}
//=========================================================================================================================================