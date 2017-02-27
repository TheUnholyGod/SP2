#include "Acrid_Plant.h"

Acrid_Plant::Acrid_Plant() : Enemy(12, "OBJ//AcidPlant.obj", "Image//AcidPlant_Texture.tga", "AcridPlant",  BOSS, "Base", 150, 15, 20)
{
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());
}

Acrid_Plant::~Acrid_Plant()
{
}