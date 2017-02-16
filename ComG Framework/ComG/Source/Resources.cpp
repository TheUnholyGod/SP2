#include "Resources.h"

Resources::Resources(int no, std::string name, std::string source, RESOURCETYPE type, int rarity) : Item(no, name, source), kTYPE_(type), krarity_(rarity)
{

}

Resources::~Resources()
{

}