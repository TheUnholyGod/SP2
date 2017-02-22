#include "PowerGenerator.h"

PowerGenerator::PowerGenerator(Vector3 position) : Building(106, "PowerGenerator", "OBJ//PowerGenerator.obj", "Image//PowerGenerator_Texture.tga", 100, DEFENCE, false)
{
	gameobjrenderer_ = new Renderer(position, Vector3(1, 0, 0));
	gameobjrenderer_->setScaling(5);
	size.push_back(Vector3(20, 10, 11) * gameobjrenderer_->getScaling());
	for (auto &i : size)
	{
		AABB* temp = new AABB(i, gameobjrenderer_->getPosition());
		allAABB.push_back(temp);
	}
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());
} 

PowerGenerator::~PowerGenerator(){}

int PowerGenerator::get_Health(){ return health_; }