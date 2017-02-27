#include "M200_CheyTac_Intervention.h"

M200_CheyTac_Intervention::M200_CheyTac_Intervention() : Weapon(306, "M200 CheyTac Intervention", "OBJ//CheyTac.obj", "", MELEE, 75.f, 25.f)
{
	defRecipe[202] = 5; //Iron
	defRecipe[210] = 5; //Copper
	defRecipe[208] = 3; //Adhesive
	defRecipe[211] = 1; //Circuit Board
}

M200_CheyTac_Intervention::~M200_CheyTac_Intervention()
{

}