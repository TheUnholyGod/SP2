#include "Kitchen_Knife.h"

Kitchen_Knife::Kitchen_Knife() : Weapon(301, "Kitchen Knife", "OBJ//KitchenKnife.obj", "", MELEE, 10.f, 15.f)
{
	defRecipe[202] = 2; //Iron
	defRecipe[206] = 1; //Wood
	defRecipe[208] = 1; //Adhesive
}

Kitchen_Knife::~Kitchen_Knife()
{

}