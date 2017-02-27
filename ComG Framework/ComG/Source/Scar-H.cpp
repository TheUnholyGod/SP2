#include "Scar-H.h"

Scar_H::Scar_H() : Weapon(305, "Scar-H", "OBJ//Scar-H.obj", "Image//ScarUV.tga", FIREARMS, 25.f, 100.f)
{
	defRecipe[202] = 10; //Iron
	defRecipe[210] = 2; //Copper
	defRecipe[208] = 1; //Adhesive
	defRecipe[211] = 2; //Circuit Board
}

Scar_H::~Scar_H()
{

}