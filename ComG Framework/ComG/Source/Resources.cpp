#include "Resources.h"

Resources::Resources(std::string name, RESOURCETYPE type, int rarity) : Item(name), kTYPE_(type), krarity_(rarity)
{

}

Resources::~Resources()
{

}