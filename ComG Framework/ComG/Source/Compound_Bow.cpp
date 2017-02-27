#include "Compound_Bow.h"

Compound_Bow::Compound_Bow() : Weapon(307, "Compound Bow", "OBJ//CompoundBow.obj", "Image//CompoundBowUV.tga", FIREARMS, 30.f, 100.f)
{
	defRecipe[202] = 2; //Iron
	defRecipe[210] = 3; //Cloth
	defRecipe[208] = 1; //Adhesive
}

Compound_Bow::~Compound_Bow()
{

}