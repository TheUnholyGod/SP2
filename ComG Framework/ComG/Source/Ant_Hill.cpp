#include "Ant_Hill.h"

Ant_Hill::Ant_Hill() : Enemy(11,"OBJ//AntHill.obj" ,"Image//AntHill_Texture.tga", "AntHill", BOSS, "Base", 150, 20, 10)
{
	/*float ah_X = 
		float ah_Y =
		float ah_Z =*/
	gameobjrenderer_->setPosition(Vector3(temp1, temp2, temp3));
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());
	allAABB[1]->setMinMax(gameobjrenderer_->getPosition());
}

Ant_Hill::~Ant_Hill()
{
}