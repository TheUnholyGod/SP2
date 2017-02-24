#include "Tree.h"
#include "ItemFactory.h"
#include "Randomizer.h"
#include "Player.h"

Tree::Tree(Vector3 position):Building(201,"Tree","OBJ//Tree.obj","Image//Tree.tga",10,NORMAL,false)
{
	gameobjrenderer_ = new Renderer(position,Vector3(1,0,0));
	size.push_back(Vector3(1, 1, 1));
	size.push_back(Vector3(5, 5, 5));
	for (auto &i : size)
	{
		AABB* temp = new AABB(gameobjrenderer_->getPosition(), i);
	}
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