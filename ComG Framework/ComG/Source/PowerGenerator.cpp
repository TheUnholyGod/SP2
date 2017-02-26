#include "PowerGenerator.h"
#include "ItemFactory.h"

PowerGenerator::PowerGenerator(Vector3 position, Vector3 forward) : Building(106, "Power Generator", "OBJ//PowerGenerator.obj", "Image//PowerGenerator_Texture.tga", 100, DEFENCE, false)
{
	gameobjrenderer_ = new Renderer(position, Vector3(1, 0, 0)/*, forward*/);
	gameobjrenderer_->setScaling(5);
	size.push_back(Vector3(10, 10, 10) * gameobjrenderer_->getScaling());
	for (auto &i : size)
	{
		AABB* temp = new AABB(i, gameobjrenderer_->getPosition());
		allAABB.push_back(temp);
	}
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());

	defaultrecipe[ItemFactory::getItemFactory()->generateItem(202)] = 15; //Iron
	defaultrecipe[ItemFactory::getItemFactory()->generateItem(203)] = 15; //Copper
	defaultrecipe[ItemFactory::getItemFactory()->generateItem(211)] = 1; //Circuit Board
	defaultrecipe[ItemFactory::getItemFactory()->generateItem(101)] = 15; //Potato
} 

PowerGenerator::~PowerGenerator(){}

int PowerGenerator::get_Health(){ return health_; }