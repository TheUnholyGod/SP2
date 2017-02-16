#include "Weapon.h"

Weapon::Weapon(int id, std::string source_location, std::string name, WEAPONTYPE type, float atk, float dura) : Item(id, source_location, name), kType_(type), kattack_(atk), kdurability_(dura)
{

}

Weapon::~Weapon()
{

}