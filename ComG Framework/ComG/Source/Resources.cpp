#include "Resources.h"

<<<<<<< HEAD
Resources::Resources(int no,std::string name, RESOURCETYPE type, int rarity) : Item(no,"",name), kTYPE_(type), krarity_(rarity)
=======
Resources::Resources(int no, std::string name, std::string source, RESOURCETYPE type, int rarity) : Item(no, name, source), kTYPE_(type), krarity_(rarity)
>>>>>>> df0b89ed37dcdc725ae0ed602e193209e647493d
{

}

Resources::~Resources()
{

}