#include "Ant_Hill.h"
#include "Randomizer.h"

std::vector<Enemy*> Ant_Hill::hills;
Ant_Hill::Ant_Hill() : Enemy(11,"OBJ//AntHill.obj" ,"Image//AntHill_Texture.tga", "AntHill", BOSS, "Base", 150, 20, 10)
{
	float ah_X = Randomizer::generate_range(1, 100);
	float ah_Z = Randomizer::generate_range(1, 100);
	gameobjrenderer_->setPosition(Vector3(ah_X, 0, ah_Z));
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());
	allAABB[1]->setMinMax(gameobjrenderer_->getPosition());
	hills.push_back(this);
}

Ant_Hill::~Ant_Hill()
{
}