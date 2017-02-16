#include "Barn.h"

Barn::Barn() : Building(101, "Barn", "", 100, NORMAL, true) 
{
	size.push_back(Vector3(1, 1, 1));
} // Change the ID
Barn::~Barn(){}
int Barn::get_Health(){ return health_; }