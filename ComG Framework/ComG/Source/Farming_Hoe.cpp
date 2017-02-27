#include "Farming_Hoe.h"

Farming_Hoe::Farming_Hoe() : Weapon(303, "Farming Hoe", "OBJ//FarmingHoe.obj", "", MELEE, 20.f, 20.f)
{
	defRecipe[202] = 5; //Iron
	defRecipe[206] = 2; //Wood
}

Farming_Hoe::~Farming_Hoe()
{

}