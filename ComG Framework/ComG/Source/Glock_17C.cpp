#include "Glock_17C.h"

Glock_17C::Glock_17C() : Weapon(304, "Glock 17C", "OBJ//Glock17.obj", "", FIREARMS, 20.f, 20.f)
{
	defRecipe[202] = 5; //Iron
	defRecipe[203] = 3; //Copper
	defRecipe[208] = 2; //Adhesive
}

Glock_17C::~Glock_17C()
{

}