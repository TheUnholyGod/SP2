#include "Ant.h"

Ant::Ant() : Enemy(11, "OBJ//Ant.obj", "Image//Ant_Texture.tga", "AntHill", BOSS, "Base", 150, 20, 10)
{

	//gameobjrenderer_->setPosition(Vector3(temp1, temp2, temp3));
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());
	allAABB[1]->setMinMax(gameobjrenderer_->getPosition());
}

Ant::~Ant()
{
}