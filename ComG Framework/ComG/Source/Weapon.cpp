#include "Weapon.h"

<<<<<<< HEAD
Weapon::Weapon(int id, std::string source_location, std::string name, WEAPONTYPE type, float atk, float dura) : Item(id, source_location, name), kType_(type), kattack_(atk), kdurability_(dura)
=======
Weapon::Weapon(int id, std::string name, std::string source, WEAPONTYPE type, float atk, float dura) : Item(id,name,source), kType_(type), kattack_(atk), kdurability_(dura)
>>>>>>> df0b89ed37dcdc725ae0ed602e193209e647493d
{

}

Weapon::~Weapon()
{

}