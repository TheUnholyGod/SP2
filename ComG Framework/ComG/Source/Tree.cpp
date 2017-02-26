#include "Tree.h"
#include "ItemFactory.h"
#include "Randomizer.h"
#include "Player.h"

Tree::Tree():Building(201, "Tree", "OBJ//Tree01.obj", "Image//Tree.tga", 10, NORMAL, false)
{
	gameobjrenderer_ = new Renderer((0,0,0), Vector3(1, 0, 0));
	size.push_back(Vector3(10, 10, 10));
	size.push_back(Vector3(10, 10, 10));
	for (auto &i : size)
	{
		AABB* temp = new AABB(i, gameobjrenderer_->getPosition());
		allAABB.push_back(temp);
	}
	gameobjrenderer_->setScaling(10);
	defaultrecipe[ItemFactory::getItemFactory()->generateItem(206)] = Randomizer::generate_range(1, 20); //Wood
}

Tree::Tree(Vector3 position):Building(201,"Tree","OBJ//Tree01.obj","Image//Tree.tga",10,NORMAL,false)
{
	gameobjrenderer_ = new Renderer(position,Vector3(1,0,0));
	size.push_back(Vector3(12, 12, 12));
	size.push_back(Vector3(15, 15, 15));
	for (auto &i : size)
	{
		AABB* temp = new AABB(i, gameobjrenderer_->getPosition());
		allAABB.push_back(temp);
	}
	gameobjrenderer_->setScaling(10);

	defaultrecipe[ItemFactory::getItemFactory()->generateItem(206)] = Randomizer::generate_range(1, 20); //Wood
}

Tree::~Tree()
{

}

void Tree::Update()
{
	if (allAABB[1]->pointtoAABB(Player::getplayer()->getRenderer().getPosition(), Player::getplayer()->getRenderer().getForward()) && Application::IsKeyPressed('E'))
	{
		for (auto &i : defaultrecipe)
		{
			while (i.second)
			{
				Inventory::getinventory()->Additem(i.first->getID());
				i.second--;
			}
		}
	}
}